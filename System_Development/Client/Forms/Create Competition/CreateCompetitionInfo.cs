using ClassLibrary;
using System;
using System.Windows.Forms;

namespace Client.Forms.Create_Competition
{
    public partial class CreateCompetitionInfo : Form
    {
        public event EventHandler<EventArgs> EventNextStepInCreatingButton;

        public event EventHandler<MyErrorEventArgs> EventErrorMessage;

        public CreateCompetitionInfo()
        {
            InitializeComponent();
        }

        public void LoadForm()
        {
            ShowDialog();
        }

        private void NextButton_Click(object sender, EventArgs e)
        {
            OnNextStepInCreatingButton();
        }

        protected virtual void OnNextStepInCreatingButton()
        {
            if (EventNextStepInCreatingButton != null)
                EventNextStepInCreatingButton(this, EventArgs.Empty);
        }

        protected virtual void OnErrorMessage(string title, string text)
        {
            if (EventErrorMessage != null)
                EventErrorMessage(this, new MyErrorEventArgs { MyTitle = title, MyText = text });
        }

        private void button1_Click(object sender, EventArgs e)
        {
            var dialogResult = MessageBox.Show(
                "Vill du verkligen Avsluta?",
                "Avsluta", MessageBoxButtons.YesNo);
            if (dialogResult == DialogResult.Yes)
            {
                Close();
            }
        }
    }
}