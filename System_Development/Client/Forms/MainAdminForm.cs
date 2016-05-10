using System;
using System.Windows.Forms;

namespace Client
{
    public partial class MainAdminForm : Form
    {
        public event EventHandler<EventArgs> EventCreateNewDiverButton;

        public event EventHandler<EventArgs> EventCreateCompetitionButton;

        public event EventHandler<EventArgs> EventCreateNewReferee;

        public event EventHandler<EventArgs> EventClickActivateButton;

        public MainAdminForm()
        {
            InitializeComponent();
        }

        public void LoadForm()
        {
            ShowDialog();
        }

        private void CreateNewDiverButton_Click(object sender, EventArgs e)
        {
            OnCreateNewDiverButton();
        }

        private void createCompetitionButton_Click(object sender, EventArgs e)
        {
            OnCreateCompetitionButton();
        }

        #region Events

        protected virtual void OnCreateNewDiverButton()
        {
            if (EventCreateNewDiverButton != null)
                EventCreateNewDiverButton(this, EventArgs.Empty);
        }

        protected virtual void OnCreateCompetitionButton()
        {
            if (EventCreateCompetitionButton != null)
                EventCreateCompetitionButton(this, EventArgs.Empty);
        }

        #endregion Events

        private void CreateNewReferee_Click(object sender, EventArgs e)
        {
            OnEventCreateNewReferee();
        }

        protected virtual void OnEventCreateNewReferee()
        {
            if (EventCreateNewReferee != null)
                EventCreateNewReferee(this, EventArgs.Empty);
        }

        private void activate_button_Click(object sender, EventArgs e)
        {
            OnEventClickActivateButton();
        }

        protected virtual void OnEventClickActivateButton()
        {
            if (EventClickActivateButton != null)
                EventClickActivateButton(this, EventArgs.Empty);
        }

        private void QuitButton_Click(object sender, EventArgs e)
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