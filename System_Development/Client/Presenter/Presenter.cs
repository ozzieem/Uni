using ClassLibrary;
using Client.Forms;
using Client.Forms.ActivateCompetition;
using Client.Forms.Create_Competition;
using Client.Forms.RefereeClient;
using System;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.Media;
using System.Net.Http;
using System.Runtime.CompilerServices;
using System.Threading;
using System.Windows.Forms;
using static System.String;

namespace Client.Presenter
{
    public class Presenter
    {
        public MainAdminForm AdminForm = new MainAdminForm();

        public List<Diver> AllDivers = new List<Diver>();
        public List<DiveType> AllDiveTypes = new List<DiveType>();
        public List<Referee> AllReferees = new List<Referee>();
        public List<Dive> CompetitionDiveList = new List<Dive>();
        public List<TextBox> RefereeFormTextBoxes = new List<TextBox>();

        public Competition NewCompetition;

        //Forms aka Views
        public Login Login = new Login();

        public Admin Admin = new Admin();
        public AddDiverForm AddDiver;
        public AddNewRefereeForm NewReferee;
        public CreateRefereeList RefereeForm = new CreateRefereeList();
        public RefereeMenu RefereeMenu = new RefereeMenu();
        public RefereeAssessmentForm RefereeAssessment = new RefereeAssessmentForm();
        public CreateCompetitionForm CompetitionForm;
        public CreateCompetitionInfo CompetitionFormInfo;
        public RunningCompetitionForm RunCompetition = new RunningCompetitionForm();

        public ActivateCompetitionForm ActivateCompetition = new ActivateCompetitionForm();

        public int ActiveCompetitionDiveIndex;

        public event EventHandler<EventArgs> EventChangeStateOfButton;

        public event EventHandler<EventArgs> EventUpdateJudgeScores;

        public void Initialize()
        {
            AdminForm.EventClickActivateButton += OnClickActivateCompetitionButton;
            CompetitionForm = new CreateCompetitionForm();
            CompetitionFormInfo = new CreateCompetitionInfo();

            AdminForm.EventCreateCompetitionButton += OnCreateCompetitionButton;
            AdminForm.EventCreateNewDiverButton += OnCreateNewDiverButton;
            AdminForm.EventCreateNewReferee += OnCreateNewReferee;

            CompetitionForm.AddDiverToList += OnAddedDiverToList;
            CompetitionForm.AddReferees += OnAddReferees;
            CompetitionForm.CreateCompleteCompetition += OnCreateCompleteCompetition;
            CompetitionForm.FormClosing += OnUserClosing;
            CompetitionForm.RemoveDiverFromList += OnRemoveDiverFromList;
            CompetitionForm.ShowAddedDiverCodes += OnShowAddedDiverCodes;
            CompetitionFormInfo.EventNextStepInCreatingButton += OnNextStepInCreating;

            ActivateCompetition.EventActivateCompetitionButton += OnActivateCompetitionButton;
            ActivateCompetition.EventChangeIndexOfChoosenCompetition += OnChangeIndexOfChoosenCompetition;

            RefereeForm.AddRefereeToList += OnAddRefereeToList;
            RefereeMenu.EventJudgeCompetition += OnJudgeCompetition;
            RefereeMenu.EventJudgeClientStart += OnJudgeClientStart;
            RefereeMenu.EventUpdateRefereeClient += OnRefereeClientUpdate;
            RefereeMenu.EventStartJudging += OnRefereeStartJudging;
            RefereeMenu.EventChangeIndexOfDiver += OnChangeIndexOfChossenDiver;

            RefereeAssessment.EventClickSendButton += OnEventClickSendButton;

            RunCompetition.EventClickNextAssignment += OnClickNextAssignment;
            RunCompetition.EventShowJudgeScores += OnShowJudgeScores;

            EventChangeStateOfButton += OnChangeStateOfButton;
            EventUpdateJudgeScores += OnUpdateJudgeScores;
        }

        private void OnChangeIndexOfChossenDiver(object sender, EventArgs e)
        {
            if (RefereeMenu.ActiveCompetitionDivers.SelectedItem == null) return;
            RefereeMenu.ActiveDiverDivesListBox.DataSource = NewCompetition.ListDiver[RefereeMenu.ActiveCompetitionDivers.SelectedIndex].ListDive;
            RefereeMenu.ActiveDiverDivesListBox.DisplayMember = "DiveCode";
        }

        private void OnUpdateJudgeScores(object sender, EventArgs e)
        {
            RunCompetition.BeginInvoke((MethodInvoker)ShowJudgeScores);
        }

        private void OnChangeIndexOfChoosenCompetition(object sender, EventArgs e)
        {
            if (ActivateCompetition.listBox1.SelectedItem != null)
            {
                var tempComp = (Competition)ActivateCompetition.listBox1.SelectedItem;
                ActivateCompetition.SelectedCompetitionField.Text = tempComp.Id.ToString();
                ActivateCompetition.CompetitionNameLabel.Text = tempComp.Name;
                ActivateCompetition.CompetitionLocationLabel.Text = tempComp.Location;
                ActivateCompetition.CompetitionTypeLabel.Text = tempComp.Type;
                ActivateCompetition.CompetitionNumberOfJudgesLabel.Text = tempComp.ListReferee.Count.ToString();
            }
        }

        public void OnChangeStateOfButton(object sender, EventArgs e)
        {
            RunCompetition.NextAssignmentButton.BeginInvoke((MethodInvoker)delegate ()
           {
               if (ActiveCompetitionDiveIndex < CompetitionDiveList.Count)
                   RunCompetition.NextAssignmentButton.Enabled = true;
               RunCompetition.waitForAssessmentsProgressBar.MarqueeAnimationSpeed = 0;
               RunCompetition.waitForAssessmentsProgressBar.Value = 0;
               RunCompetition.waitForAssessmentsProgressBar.Refresh();
           });
        }

        public void RunApplication()
        {
            Login.LoginButton += OnLoginButton;
            Application.EnableVisualStyles();
            Application.Run(Login);
        }

        public void ErrorMessageBox(string title, string text)
        {
            MessageBox.Show(text, title, MessageBoxButtons.OK, MessageBoxIcon.Error);
        }

        private void OnEventClickSendButton(object sender, EventArgs e)
        {
            try
            {
                if (RefereeAssessment.refScoreTextBox.Text.Length == 0)
                    throw new FormatException();
                var dialogResult = MessageBox.Show(
                    $"Skicka {RefereeAssessment.refScoreTextBox.Text} poäng?",
                        "Skicka poäng", MessageBoxButtons.YesNo);
                if (dialogResult == DialogResult.Yes)
                {
                    var refScore = RefereeAssessment.refScoreTextBox.Text;
                    var judgeScore = float.Parse(refScore, CultureInfo.InvariantCulture.NumberFormat);
                    var score = new Score(judgeScore);
                    var dive = new Dive();
                    var assessment = new Assessment(score, dive, LoggedInUser);
                    var str = ClientNetworkHandler.SendAndReceive(assessment);
                    MessageBox.Show($"{judgeScore} poäng skickad", "Meddelande");
                }
            }
            catch (FormatException)
            {
                ErrorMessageBox("Ogiltig inmatning", "Ange poäng!");
            }
            RefereeAssessment.RefSendScoreButton.Enabled = false;
            var tDive = WaitForDiveToJudge();
            RefereeAssessment.RefereeCurrentDiveInfoLabel.Text = tDive.ToString();
            SystemSounds.Beep.Play();
            RefereeAssessment.RefSendScoreButton.Enabled = true;
        }

        public void InitializeRunCompetitionForm()
        {
            var tempCompetition = ActivateCompetition.listBox1.SelectedItem;
            NewCompetition = (Competition)tempCompetition;
            ActiveCompetitionDiveIndex = 0;

            RunCompetition.waitForAssessmentsProgressBar.MarqueeAnimationSpeed = 0;
            var tDives = ClientNetworkHandler.SendAndReceive($"SC;{NewCompetition.Id}");

            var diveList = tDives as List<Dive>;
            diveList?.Sort((x, y) => x.Order.CompareTo(y.Order));
            CompetitionDiveList = diveList;
            if (CompetitionDiveList != null)
                foreach (var dive in CompetitionDiveList)
                {
                    if (dive.TotalPoints.Value != -1)
                        ActiveCompetitionDiveIndex++;
                }

            RunCompetition.scoreBoardListBox.DataSource = Admin.GetActiveCompetitionDivers();
            RunCompetition.divesListBox.DataSource = diveList;
            //RunCompetition.listBox1.DisplayMember = "Order";
            if (NewCompetition.ListReferee.Count > 3)
            {
                RunCompetition.Judge4.Text = NewCompetition.ListReferee[3].Name;
                RunCompetition.Judge4.Show();
                RunCompetition.label9.Show();
            }
            if (NewCompetition.ListReferee.Count > 4)
            {
                RunCompetition.Judge5.Text = NewCompetition.ListReferee[4].Name;
                RunCompetition.Judge5.Show();
                RunCompetition.label10.Show();
            }
            RunCompetition.Judge1.Text = NewCompetition.ListReferee[0].Name;
            RunCompetition.Judge2.Text = NewCompetition.ListReferee[1].Name;
            RunCompetition.Judge3.Text = NewCompetition.ListReferee[2].Name;
            RunCompetition.NextAssignmentButton.Enabled = true;
            RunCompetition.LoadForm();
        }

        #region Referee Events

        private void OnRefereeStartJudging(object sender, EventArgs e)
        {
            var dive = WaitForDiveToJudge();
            ErrorMessageBox("Hopp tillgängligt", "Hopp tillgängligt");
            RefereeAssessment.RefSendScoreButton.Enabled = true;
            RefereeAssessment.RefereeCurrentDiveInfoLabel.Text = dive.ToString();
            RefereeAssessment.LoadForm();
            //var assessmentThread = new Thread(RefereeAssessment.LoadForm);
            //assessmentThread.Start();
        }

        private Dive WaitForDiveToJudge()
        {
            var dive = LoggedInUser.ReceiveDive();
            return dive;
        }

        private void OnShowJudgeScores(object sender, EventArgs e)
        {
            ShowJudgeScores();
        }

        public void ShowJudgeScores()
        {
            RunCompetition.scoreBoardListBox.DataSource = null;
            RunCompetition.scoreBoardListBox.DataSource = Admin.GetActiveCompetitionDivers();
            var selectedIndex = RunCompetition.divesListBox.SelectedIndex;
            RunCompetition.DiveTitle.Text =
                                    "Hopp: " + CompetitionDiveList[selectedIndex].Order.ToString() +
                                    "   Hoppkod: " + CompetitionDiveList[selectedIndex].DiveCode;

            RunCompetition.label6.Text = "-";
            RunCompetition.label7.Text = "-";
            RunCompetition.label8.Text = "-";
            RunCompetition.label9.Text = "-";
            RunCompetition.label10.Text = "-";

            foreach (var asses in CompetitionDiveList[selectedIndex].Assessments)
            {
                if (NewCompetition.ListReferee[0].Id == asses.RefereeId)
                    RunCompetition.label6.Text = asses.Point.Value.ToString();
                if (NewCompetition.ListReferee[1].Id == asses.RefereeId)
                    RunCompetition.label7.Text = asses.Point.Value.ToString();
                if (NewCompetition.ListReferee[2].Id == asses.RefereeId)
                    RunCompetition.label8.Text = asses.Point.Value.ToString();
                if (NewCompetition.ListReferee.Count > 3)
                {
                    if (NewCompetition.ListReferee[3].Id == asses.RefereeId)
                        RunCompetition.label9.Text = asses.Point.Value.ToString();
                }
                if (NewCompetition.ListReferee.Count > 4)
                {
                    if (NewCompetition.ListReferee[4].Id == asses.RefereeId)
                        RunCompetition.label10.Text = asses.Point.Value.ToString();
                }
            }
            if (CompetitionDiveList[selectedIndex].TotalPoints.Value != -1)
                RunCompetition.TotalPoints.Text = CompetitionDiveList[selectedIndex].TotalPoints.Value.ToString();
            else
                RunCompetition.TotalPoints.Text = "Inväntar domare...";
        }

        private void OnClickNextAssignment(object sender, EventArgs e)
        {
            RunCompetition.NextAssignmentButton.Enabled = false;
            RunCompetition.waitForAssessmentsProgressBar.MarqueeAnimationSpeed = 30;

            var getAssignmentsFromServer = new Thread(ClickNextAssignmentFunction);
            getAssignmentsFromServer.Start();
        }

        private void ClickNextAssignmentFunction()
        {
            var dive = CompetitionDiveList[ActiveCompetitionDiveIndex];
            ClientNetworkHandler.SendAndReceive(dive);
            while (true)
            {
                var assessmentCounter = 0;
                var currentDive = (Dive)ClientNetworkHandler.SendAndReceive("IsCurrentDiveDone");
                foreach (var assessment in currentDive.Assessments)
                {
                    if (assessment.Point.Value != -1)
                        assessmentCounter++;
                }
                CompetitionDiveList[ActiveCompetitionDiveIndex] = currentDive;
                if (assessmentCounter == NewCompetition.ListReferee.Count)
                {
                    ActiveCompetitionDiveIndex++;
                    OnEventChangeStateOfButton();
                    OnUpdateJudgeScores();
                    if (ActiveCompetitionDiveIndex == CompetitionDiveList.Count - 1)
                        RunCompetition.NextAssignmentButton.Enabled = false;
                    return;
                }
                Thread.Sleep(2000);
                OnUpdateJudgeScores();
            }
        }

        private void OnRefereeClientUpdate(object sender, EventArgs e)
        {
            var activeCompetition =
                (Competition)ClientNetworkHandler.SendAndReceive($"GCC;{LoggedInUser.Id}");
            NewCompetition = activeCompetition;
            RefereeMenu.ActiveCompetitionInfo.Text = activeCompetition.ToString();
            RefereeMenu.ActiveCompetitionDivers.DataSource = activeCompetition.ListDiver;
        }

        public Referee LoggedInUser { get; set; }

        private void OnJudgeClientStart(object sender, EventArgs e)
        {
            OnRefereeClientUpdate(sender, e);
        }

        private void OnJudgeCompetition(object sender, EventArgs e)
        {
            RefereeMenu.Close();    //TEMP DEBUG
        }

        #endregion Referee Events

        public void OnActivateCompetitionButton(object source, EventArgs args)
        {
            var dialogResult = MessageBox.Show(
                "Aktivera tävling:" +
                ActivateCompetition.listBox1.SelectedItem + "?",
                "Aktivera tävling", MessageBoxButtons.YesNo);

            if (dialogResult != DialogResult.Yes) return;
            ActivateCompetition.Hide();
            InitializeRunCompetitionForm();
        }

        public void OnAddDiverToDatabase(object source, EventArgs args)
        {
            if (IsNullOrEmpty(AddDiver.nameBox.Text) ||
                IsNullOrEmpty(AddDiver.CountryBox.Text) ||
                IsNullOrEmpty(AddDiver.AgeBox.Text) ||
                IsNullOrEmpty(AddDiver.diverIDBox.Text))
            {
                ErrorMessageBox("Fyll i samtliga fält", "Vänligen fyll i alla fält");
                return;
            }
            var admin = new Admin();
            var genderChoice = "";
            if (AddDiver.radioMan.Checked)
                genderChoice = "M";
            else if (AddDiver.radioWoman.Checked)
                genderChoice = "F";

            var diver = new Diver(
                AddDiver.nameBox.Text, AddDiver.CountryBox.Text,
                int.Parse(AddDiver.AgeBox.Text), genderChoice,
                int.Parse(AddDiver.diverIDBox.Text));
            admin.AddDiver(diver);
            MessageBox.Show(
                "Hoppare tillagd till databasen!",
                "Hoppare tillagd", MessageBoxButtons.OK);
            AddDiver.Close();
        }

        public void OnClickActivateCompetitionButton(object source, EventArgs args)
        {
            ActivateCompetition.listBox1.DataSource =
                (List<Competition>)ClientNetworkHandler.SendAndReceive("GetCompetitions");
            //var activateCompetitionThread = new Thread(ActivateCompetition.LoadForm);
            //activateCompetitionThread.Start();
            ActivateCompetition.LoadForm();
        }

        public void OnLoginButton(object source, MyEventArgs args)
        {
            try
            {
                ClientNetworkHandler.Connect();
                var loginString = "LI;" + args.MyObject;
                var obj = ClientNetworkHandler.SendAndReceive(loginString);
                if (obj is Admin)
                {
                    //var adminThread = new Thread(AdminForm.LoadForm);
                    //adminThread.Start();
                    Login.Hide();
                    AdminForm.LoadForm();
                }
                else if (obj is Referee)
                {
                    //var refereeThread = new Thread(RefereeMenu.LoadForm);
                    //refereeThread.Start();
                    LoggedInUser = (Referee)obj;
                    Login.Hide();
                    RefereeMenu.LoadForm();
                }
                else if (obj is string)
                {
                    throw new FormatException((string)obj);
                }
                Login.Close();
            }
            catch (FormatException formatException)
            {
                ErrorMessageBox("Inloggningsfel", formatException.Message);
            }
        }

        #region AdminMenu - Events

        public void OnCreateCompetitionButton(object source, EventArgs args)
        {
            InitializeCompInfoForm();
            //var createCompeThread = new Thread(CompetitionFormInfo.LoadForm);
            //createCompeThread.Start();
            CompetitionFormInfo.LoadForm();
        }

        public void OnCreateNewDiverButton(object source, EventArgs args)
        {
            AddDiver = new AddDiverForm();
            AddDiver.radioWoman.Checked = true;
            AddDiver.AddDiverToDatabase += OnAddDiverToDatabase;
            AddDiver.EventQuitOnClickButton += OnQuitClickButton;
            //var addDiverThread = new Thread(AddDiver.LoadForm);
            //addDiverThread.Start();
            AddDiver.LoadForm();
        }

        private void OnQuitClickButton(object sender, EventArgs e)
        {
            var dialogResult = MessageBox.Show(
                    "Vill du verkligen Avsluta?",
                    "Avsluta", MessageBoxButtons.YesNo);
            if (dialogResult == DialogResult.Yes)
            {
                AddDiver.AddDiverToDatabase -= OnAddDiverToDatabase;
                AddDiver.EventQuitOnClickButton -= OnQuitClickButton;
                AddDiver.Close();
            }
        }

        public void OnCreateNewReferee(object source, EventArgs args)
        {
            NewReferee = new AddNewRefereeForm();
            InitializeCreateRefereeForm();
            NewReferee.AddNewRefereeToDatabase += OnAddNewRefereeToDatabase;
            //var addRefereeThread = new Thread(NewReferee.LoadForm);
            //addRefereeThread.Start();
            NewReferee.LoadForm();
        }

        #endregion AdminMenu - Events

        #region CreateNewReferee - Events samt initialisering

        public void InitializeCreateRefereeForm()
        {
            RefereeFormTextBoxes.Add(NewReferee.FirstnameBox);
            RefereeFormTextBoxes.Add(NewReferee.CountryBox);
            RefereeFormTextBoxes.Add(NewReferee.UsernameBox);
            RefereeFormTextBoxes.Add(NewReferee.PasswordBox);
            RefereeFormTextBoxes.Add(NewReferee.CheckPasswordBox);
        }

        public void OnAddNewRefereeToDatabase(object source, EventArgs args)
        {
            var admin = new Admin();
            foreach (var box in RefereeFormTextBoxes)
            {
                if (!IsNullOrEmpty(box.Text)) continue;
                ErrorMessageBox("Tomt Fält", "Det finns 1 eller flera tomma fält");
                return;
            }
            if (NewReferee.PasswordBox.Text != NewReferee.CheckPasswordBox.Text)
            {
                ErrorMessageBox("Fel lösenord", "Lösenorden stämmer inte överrens!");
                return;
            }
            var referee = new Referee(NewReferee.FirstnameBox.Text, NewReferee.CountryBox.Text, NewReferee.PasswordBox.Text, NewReferee.UsernameBox.Text);
            admin.AddReferee(referee);
            MessageBox.Show(
                "Domare tillagd till databasen!",
                "Domare tillagd", MessageBoxButtons.OK);
            NewReferee.Close();
        }

        #endregion CreateNewReferee - Events samt initialisering

        #region CreateCompetitionInfoForm - Events samt initialisering

        public void InitializeCompInfoForm()
        {
            CompetitionFormInfo.nameBox.Text = "Default";
            CompetitionFormInfo.dateBox.Text = "Default";
            CompetitionFormInfo.locationBox.Text = "Default";
            CompetitionFormInfo.typeBox.Text = "Default";
        }

        public void OnNextStepInCreating(object source, EventArgs args)
        {
            if (IsNullOrEmpty(CompetitionFormInfo.nameBox.Text) ||
                IsNullOrEmpty(CompetitionFormInfo.dateBox.Text) ||
                IsNullOrEmpty(CompetitionFormInfo.locationBox.Text) ||
                IsNullOrEmpty(CompetitionFormInfo.typeBox.Text))
            {
                ErrorMessageBox("Ej komplett information", "Vänligen fyll i samtliga fält");
                return;
            }
            var rounds = 0;
            if (CompetitionFormInfo.radio5Button.Checked)
                rounds = 5;
            else if (CompetitionFormInfo.radio6Button.Checked)
                rounds = 6;

            NewCompetition = new Competition(CompetitionFormInfo.nameBox.Text, CompetitionFormInfo.dateBox.Text, CompetitionFormInfo.locationBox.Text, CompetitionFormInfo.typeBox.Text, rounds);
            InitializeCompForm();
            InitializeRefereeForm();
            //var nextThread = new Thread(CompetitionForm.LoadForm);
            //nextThread.Start();
            CompetitionFormInfo.Close();
            CompetitionForm.LoadForm();
        }

        #endregion CreateCompetitionInfoForm - Events samt initialisering

        #region CreateCompetitionForm - Events samt initialisering

        public void InitializeCompForm()
        {
            AllDivers = (List<Diver>)ClientNetworkHandler.SendAndReceive("GetDivers");
            AllDiveTypes = (List<DiveType>)ClientNetworkHandler.SendAndReceive("GetDiveTypes");
            AllDivers.Sort((x, y) => x.DiverId.CompareTo(y.DiverId));
            CompetitionForm.listBox1.DataSource = AllDivers;
            CompetitionForm.textboxes.Add(CompetitionForm.textBox2);
            CompetitionForm.textboxes.Add(CompetitionForm.textBox3);
            CompetitionForm.textboxes.Add(CompetitionForm.textBox4);
            CompetitionForm.textboxes.Add(CompetitionForm.textBox5);
            CompetitionForm.textboxes.Add(CompetitionForm.textBox6);
            if (NewCompetition.Rounds == 5)
            {
                CompetitionForm.textBox7.Hide();
                CompetitionForm.label9.Hide();
            }
            else
            {
                CompetitionForm.textBox7.Show();
                CompetitionForm.label9.Show();
                CompetitionForm.textboxes.Add(CompetitionForm.textBox7);
            }
            CompetitionForm.label10.Text = "Tävlande: 0";
            CompetitionForm.listBox2.DataSource = NewCompetition.ListDiver;
        }

        public void OnAddedDiverToList(object source, EventArgs args)
        {
            var tempIndex = CompetitionForm.listBox1.SelectedIndex;
            var diver = (Diver)CompetitionForm.listBox1.SelectedItem;

            if (tempIndex >= 0 & tempIndex < AllDivers.Count)
            {
                foreach (var box in CompetitionForm.textboxes)
                {
                    if (IsNullOrEmpty(box.Text))
                    {
                        ErrorMessageBox("Hoppkod saknas", "En hoppkod saknas");
                        diver.ListDive.Clear();
                        return;
                    }
                    diver.ListDive.Add(new Dive(box.Text, diver.DiverId));
                }
            }
            else
                ErrorMessageBox("Ingen tävlande vald", "Vänligen välj en tävlande");
            var tempDiveList = new List<string>();

            foreach (var diveCode in diver.ListDive)
            {
                tempDiveList.Add(diveCode.Type.Code);
            }
            var i = 1;
            foreach (var diveCode in tempDiveList)
            {
                if (diveCode != null)
                {
                    if (!IsDivecodeAcceptable(diveCode))
                    {
                        ErrorMessageBox("Hoppkod ej funnen", $"Hoppkoden vid fält {i} finns ej. Är koden korrekt?");
                        diver.ListDive.Clear();
                        return;
                    }
                }
                else
                {
                    ErrorMessageBox("Hoppkod ej tillagd", $"Hoppkod vid fält {i} saknas. Vänligen lägg till samtliga hoppkoder");
                    diver.ListDive.Clear();
                    return;
                }
                i++;
            }
            if (!CheckIfAllDifferent(tempDiveList))
            {
                ErrorMessageBox("Dubbel hoppkod", "Det finns multipla inlägg av samma hoppkod. Vänligen ändra!");
                diver.ListDive.Clear();
                return;
            }
            NewCompetition.ListDiver.Add(diver);
            AllDivers.RemoveAt(tempIndex);
            CleanUpUi();
        }

        public void OnAddReferees(object source, EventArgs args)
        {
            RefereeForm.LoadRefereeCreationForm();
        }

        public void OnCreateCompleteCompetition(object source, EventArgs args)
        {
            NewCompetition.SortDiveOrder();
            var message = ClientNetworkHandler.SendAndReceive(NewCompetition);
            MessageBox.Show((string)message, "Tävling", MessageBoxButtons.OK);
            CompetitionForm.Close();
        }

        public void OnRemoveDiverFromList(object source, EventArgs args)
        {
            var tempIndex = CompetitionForm.listBox2.SelectedIndex;
            if (!(tempIndex >= 0 & tempIndex < NewCompetition.ListDiver.Count)) return;
            var dialogResult = MessageBox.Show("Är du säker?", "Radera Tävlande", MessageBoxButtons.YesNo);

            if (dialogResult != DialogResult.Yes) return;
            CompetitionForm.listBox3.DataSource = null;
            NewCompetition.ListDiver[tempIndex].ListDive.Clear();
            AllDivers.Add(NewCompetition.ListDiver[tempIndex]);
            NewCompetition.ListDiver.RemoveAt(tempIndex);
            AllDivers.Sort((x, y) => x.DiverId.CompareTo(y.DiverId));
            CleanUpUi();
        }

        public void OnShowAddedDiverCodes(object source, EventArgs args)
        {
            if (CompetitionForm.listBox2.SelectedItem == null) return;
            CompetitionForm.listBox3.DataSource = NewCompetition.ListDiver[CompetitionForm.listBox2.SelectedIndex].ListDive;
            CompetitionForm.listBox3.DisplayMember = "DiveCode";
        }

        public void OnUserClosing(object source, FormClosingEventArgs args)
        {
            if (args.CloseReason != CloseReason.UserClosing) return;
            var dialogResult = MessageBox.Show("Är du säker?", "Avbryt skapande", MessageBoxButtons.YesNo);
            if (dialogResult != DialogResult.Yes) return;
            NewCompetition.ListReferee.Clear();
            NewCompetition.ListDiver.Clear();
            NewCompetition.Rounds = -1;
            NewCompetition.Name = NewCompetition.Date = NewCompetition.Location = NewCompetition.Type = "";
            CompetitionForm.listBox1.DataSource = null;
            CompetitionForm.listBox2.DataSource = null;
            CompetitionForm.listBox3.DataSource = null;
            CompetitionForm.listBox4.DataSource = null;
        }

        #endregion CreateCompetitionForm - Events samt initialisering

        #region Referees - Events samt initialisering

        public void InitializeRefereeForm()
        {
            AllReferees = (List<Referee>)ClientNetworkHandler.SendAndReceive("GetReferees");
            AllReferees.Sort((x, y) => x.Id.CompareTo(y.Id));
            RefereeForm.listBox1.DataSource = AllReferees;
            RefereeForm.label1.Text = "Domare: 0";
            RefereeForm.listBox2.DataSource = NewCompetition.ListReferee;

            RefereeForm.AddRefereeToList += OnAddRefereeToList;
            RefereeForm.RemoveRefereeFromList += OnRemoveRefereeFromList;
            RefereeForm.PressingDoneButton += OnPressingDoneButton;
        }

        public void OnAddRefereeToList(object source, EventArgs args)
        {
            var tempIndex = RefereeForm.listBox1.SelectedIndex;
            var referee = (Referee)RefereeForm.listBox1.SelectedItem;

            if (!(tempIndex >= 0 & tempIndex < AllReferees.Count)) return;
            if (NewCompetition.ListReferee.Contains(referee))
            {
                ErrorMessageBox("Domare redan tillagd", "Denna domare är redan tillagd i tävlingen!");
                return;
            }
            NewCompetition.ListReferee.Add(referee);
            AllReferees.RemoveAt(tempIndex);
            RefereeForm.listBox1.DataSource = null;
            RefereeForm.listBox1.DataSource = AllReferees;
            RefereeForm.listBox2.DataSource = null;
            RefereeForm.listBox2.DataSource = NewCompetition.ListReferee;

            RefereeForm.SelectNextControl(RefereeForm.listBox1, true, true, true, true);
            RefereeForm.listBox1.SelectedIndex = -1;
            RefereeForm.listBox2.SelectedIndex = -1;
            RefereeForm.label1.Text = $"Domare: {NewCompetition.ListReferee.Count}";
        }

        public void OnPressingDoneButton(object source, EventArgs args)
        {
            CompetitionForm.listBox4.DataSource = null;
            CompetitionForm.listBox4.DataSource = NewCompetition.ListReferee;
        }

        public void OnRemoveRefereeFromList(object source, EventArgs args)
        {
            var tempIndex = RefereeForm.listBox2.SelectedIndex;
            if (!(tempIndex >= 0 & tempIndex < NewCompetition.ListReferee.Count)) return;
            var dialogResult = MessageBox.Show("Är du säker?", "Radera domare", MessageBoxButtons.YesNo);

            if (dialogResult != DialogResult.Yes) return;
            AllReferees.Add(NewCompetition.ListReferee[tempIndex]);
            NewCompetition.ListReferee.RemoveAt(tempIndex);
            AllReferees.Sort((x, y) => Compare(x.Name, y.Name, StringComparison.Ordinal));

            RefereeForm.listBox1.DataSource = null;
            RefereeForm.listBox1.DataSource = AllReferees;
            RefereeForm.listBox2.DataSource = null;
            RefereeForm.listBox2.DataSource = NewCompetition.ListReferee;

            RefereeForm.SelectNextControl(RefereeForm.listBox1, true, true, true, true);
            RefereeForm.listBox1.SelectedIndex = -1;
            RefereeForm.listBox2.SelectedIndex = -1;
            RefereeForm.label1.Text = $"Domare: {NewCompetition.ListReferee.Count}";
        }

        #endregion Referees - Events samt initialisering

        #region Funktionalitet för CreateCompetition

        public void CleanUpUi()
        {
            CompetitionForm.listBox1.DataSource = null;
            CompetitionForm.listBox1.DataSource = AllDivers;
            CompetitionForm.listBox2.DataSource = null;
            CompetitionForm.listBox2.DataSource = NewCompetition.ListDiver;
            foreach (var box in CompetitionForm.textboxes)
            {
                box.Clear();
            }
            CompetitionForm.label7.Text = "";

            CompetitionForm.SelectNextControl(CompetitionForm.listBox1, true, true, true, true);
            CompetitionForm.listBox1.SelectedIndex = -1;
            CompetitionForm.listBox2.SelectedIndex = -1;
            CompetitionForm.listBox3.SelectedIndex = -1;

            CompetitionForm.label10.Text = $"Tävlande: {NewCompetition.ListDiver.Count}";
        }

        public bool CheckIfAllDifferent(IReadOnlyList<string> divecodes)
        {
            var j = 1;
            foreach (var code in divecodes)
            {
                for (var i = j; i < divecodes.Count; i++)
                {
                    if (code == divecodes[i])
                        return false;
                }
                j++;
            }
            return true;
        }

        private bool IsDivecodeAcceptable(string code)
        {
            foreach (var diveCode in AllDiveTypes)
            {
                if (diveCode.Code == code)
                {
                    return true;
                }
            }
            return false;
        }

        #endregion Funktionalitet för CreateCompetition

        protected virtual void OnEventChangeStateOfButton()
        {
            EventChangeStateOfButton?.Invoke(this, EventArgs.Empty);
        }

        protected virtual void OnUpdateJudgeScores()
        {
            EventUpdateJudgeScores?.Invoke(this, EventArgs.Empty);
        }
    }
}