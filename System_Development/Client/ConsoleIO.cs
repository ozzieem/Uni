using ClassLibrary;
using System;
using System.Collections.Generic;
using System.Threading;
using static System.Console;

namespace Client
{
    /// <summary>
    ///     Konsol-program för simulering av simhopp.
    /// </summary>
    public static class ConsoleIO
    {
        public static List<Competition> AllCompetitions = new List<Competition>();
        public static Competition TempCompetition = new Competition();
        public static List<Diver> AllDivers = new List<Diver>();
        public static List<Referee> AllReferees = new List<Referee>();
        public static int GlobalDiveOrder;

        public static bool Creating = true;

        public static void RunReferee(Referee referee)
        {
            var choice = RefereeMenu();
            switch (choice)
            {
                case 1: // Show all competitions, choose one to start
                    DisplayAvailableCompetitions(referee);
                    var id = ChooseCompetition();

                    Thread.Sleep(1000);
                    Clear();
                    break;

                case 2: // Test receive dive
                    referee.ReceiveDive();
                    break;

                case 0: // Logout user
                    ClientNetworkHandler.SendAndReceive("Logout");
                    LoginHandler.userState = LoginHandler.UserState.None;
                    //LoginHandler.LoginMenu();
                    break;

                default:
                    WriteLine("Try again!");
                    break;
            }
        }

        public static void RunAdmin(Admin admin)
        {
            var choice = AdminMenu();
            switch (choice)
            {
                case 1: //Create new competition
                    CreateCompetition();
                    AddReferees();
                    AddDiversToCompetition(TempCompetition.Rounds);
                    TempCompetition.SortDiveOrder();
                    admin.AddCompetition(TempCompetition);
                    break;

                case 2: // Add new diver to database
                    var diver = CreateDiver();
                    admin.AddDiver(diver);
                    break;

                case 3: // Add new referee to database
                    var referee = CreateReferee();
                    admin.AddReferee(referee);
                    break;

                case 4: // Show all competitions, choose one to start
                    DisplayCompetitions();
                    var id = ChooseCompetition();
                    if (id > 0)
                    {
                        admin.StartCompetition(id);
                        WriteLine($"Competition {id} has started!");
                    }
                    Thread.Sleep(1000);
                    Clear();
                    break;

                case 5:
                    WriteLine("Testsend");
                    ReadLine();
                    ClientNetworkHandler.SendToServer("SendJudge");
                    ReadLine();
                    break;

                case 0: // Logout user
                    ClientNetworkHandler.SendAndReceive("Logout");
                    LoginHandler.userState = LoginHandler.UserState.None;
                    // LoginHandler.LoginMenu();
                    break;

                default:
                    WriteLine("Try again!");
                    break;
            }
        }

        public static void RunReferee()
        {
        }

        public static int ChooseCompetition()
        {
            WriteLine("Choose competition to run by ID or 0 to exit: ");
            var id = Convert.ToInt32(ReadLine());
            return id;
        }

        public static int RefereeMenu()
        {
            Write(
                "1. Display all active competitions\n" +
                "0. Logout\n" +
                "Enter your choice: ");
            var choice = Convert.ToInt32(ReadLine());
            return choice;
        }

        public static int AdminMenu()
        {
            Write(
                "1. Create new competition\n" +
                "2. Insert new diver to database\n" +
                "3. Insert new referee to database\n" +
                "4. Display all competitions\n" +
                "0. Logout\n" +
                "Enter your choice: ");
            var choice = Convert.ToInt32(ReadLine());
            return choice;
        }

        public static void AddDiversToCompetition(int rounds)
        {
            DisplayDivers();
            while (Creating)
            {
                try
                {
                    var listContains = false;
                    var tDiver = new Diver();
                    var choice = ChooseDiver();
                    if (choice == 0)
                    {
                        Creating = false;
                        break;
                    }
                    // Lägga till kontroll för hur många divers som lagts till?
                    foreach (var diver in TempCompetition.ListDiver)
                    {
                        // Kollar om diver redan är tillagd
                        if (choice == diver.DiverId)
                        {
                            listContains = true;
                            break;
                        }
                    }

                    // Lägger till diver om denne inte finns i listan
                    if (!listContains)
                    {
                        foreach (var diver in AllDivers)
                        {
                            if (diver.DiverId == choice)
                            {
                                tDiver = diver;
                                AddDives(tDiver, rounds);
                                break;
                            }
                        }
                        if (tDiver.DiverId == -1)
                            throw new ListObjectNotFoundException("Diver not found!");
                    }
                    else
                    {
                        throw new ListObjectAlreadyExistsException("Diver already added!");
                    }
                }
                catch (ListObjectNotFoundException e)
                {
                    WriteLine(e.Message);
                    Thread.Sleep(1000);
                }
                catch (ListObjectAlreadyExistsException e)
                {
                    WriteLine(e.Message);
                    Thread.Sleep(1000);
                }
                catch (FormatException formatException)
                {
                    WriteLine(formatException.Message);
                    Thread.Sleep(1000);
                }
            }
        }

        private static int ChooseDiver()
        {
            DisplayDivers();
            Write("Choose diver by ID or type 0 to cancel:");
            var choice = Convert.ToInt32(ReadLine());
            WriteLine("\n");
            return choice;
        }

        private static void AddDives(Diver tempDiver, int rounds)
        {
            WriteLine("Enter details of dives for {0}:", tempDiver.Name);
            for (var i = 1; i <= rounds; i++)
            {
                var dive = new Dive();
                WriteLine($"Dive number {i}:");
                WriteLine("Dive code: ");
                dive.Type.Code = ReadLine();
                try
                {
                    if (!tempDiver.ListDive.Contains(dive))
                        tempDiver.AddDive(dive);
                    else
                    {
                        i--;
                        throw new ListObjectAlreadyExistsException("Dive already added!");
                    }
                }
                catch (ListObjectAlreadyExistsException e)
                {
                    WriteLine(e.Message);
                }
            }
            TempCompetition.AddDiver(tempDiver);
            WriteLine("Diver {0} added!", tempDiver.Name);
            Thread.Sleep(2000);
        }

        public static void AddReferees()
        {
            DisplayReferees();
            for (var i = 1; i <= 5; i++)
            {
                try
                {
                    var tempReferee = new Referee();
                    var choice = ChooseReferee(i);
                    foreach (var referee in AllReferees)
                    {
                        if (referee.Id == choice)
                        {
                            tempReferee = referee;
                        }
                    }
                    if (tempReferee.Id == -1 || tempReferee.Id == 0)
                    {
                        i--;
                        throw new ListObjectNotFoundException("Referee not found!");
                    }

                    if (!TempCompetition.ListReferee.Contains(tempReferee))
                        TempCompetition.ListReferee.Add(tempReferee);
                    else
                    {
                        i--;
                        throw new ListObjectAlreadyExistsException("Referee already added!");
                    }
                }
                catch (ListObjectNotFoundException listObjectNotFoundException)
                {
                    WriteLine(listObjectNotFoundException.Message);
                }
                catch (ListObjectAlreadyExistsException e)
                {
                    WriteLine(e.Message);
                }
            }
        }

        private static int ChooseReferee(int count)
        {
            Write($"Add referee {count} by ID:");
            var choice = Convert.ToInt32(ReadLine());
            return choice;
        }

        #region Create Methods

        public static Diver CreateDiver()
        {
            Clear();
            var diver = new Diver();
            WriteLine("Enter diver details:");
            Write("Name: ");
            diver.Name = ReadLine();
            Write("Country: ");
            diver.Country = ReadLine();
            Write("Gender: ");
            diver.Gender = ReadLine();
            Write("Age: ");
            diver.Age = Convert.ToInt32(ReadLine());
            Write("DiverId: ");
            diver.DiverId = Convert.ToInt32(ReadLine());
            WriteLine("\n");
            return diver;
        }

        public static Referee CreateReferee()
        {
            Clear();
            WriteLine("Enter referee details:");
            var referee = new Referee();
            Write("Name: ");
            referee.Name = ReadLine();
            Write("Country: ");
            referee.Country = ReadLine();
            Write("Username: ");
            referee.Username = ReadLine();
            Write("Password: ");
            referee.Password = ReadLine();
            WriteLine("\n");
            return referee;
        }

        public static void CreateCompetition()
        {
            Clear();
            GlobalDiveOrder = 1;
            WriteLine("Enter competition details:");
            var newCompetition = new Competition();
            Write("Name: ");
            newCompetition.Name = ReadLine();
            Write("Date: ");
            newCompetition.Date = ReadLine();
            Write("Location: ");
            newCompetition.Location = ReadLine();
            Write("Type: ");
            newCompetition.Type = ReadLine();
            Write("Rounds: ");
            newCompetition.Rounds = Convert.ToInt32(ReadLine());
            TempCompetition = newCompetition;
            WriteLine("\n");
        }

        #endregion Create Methods

        #region Display Methods

        private static void DisplayDivers()
        {
            Clear();
            WriteLine("---Adding Divers to competition {0}---", TempCompetition.Name);
            WriteLine("DiverID | Name | Country | Age | Gender");
            AllDivers = (List<Diver>)ClientNetworkHandler.SendAndReceive("GetDivers");
            foreach (var diver in AllDivers)
            {
                WriteLine(diver.ToString());
            }
        }

        private static void DisplayReferees()
        {
            Clear();
            WriteLine("---Adding referees(5) to competition {0}---", TempCompetition.Name);
            WriteLine("ID | Name | Country");
            AllReferees = (List<Referee>)ClientNetworkHandler.SendAndReceive("GetReferees");
            foreach (var referee in AllReferees)
            {
                WriteLine(referee.ToString());
            }
        }

        private static void DisplayCompetitions()
        {
            Clear();
            WriteLine("---Available competitions---");
            WriteLine("ID | Name | Location | Date | Type | Rounds ");
            AllCompetitions = (List<Competition>)ClientNetworkHandler.SendAndReceive("GetCompetitions");
            foreach (var competition in AllCompetitions)
            {
                WriteLine(competition.ToString());
            };
        }

        private static void DisplayAvailableCompetitions(Referee referee)
        {
            Clear();
            WriteLine("---Available competitions---");
            WriteLine("ID | Name | Location | Date | Type | Rounds ");
            AllCompetitions = (List<Competition>)ClientNetworkHandler.SendAndReceive($"GAC;{referee.Id}");
            foreach (var competition in AllCompetitions)
            {
                WriteLine(competition.ToString());
            };
        }

        #endregion Display Methods
    }
}