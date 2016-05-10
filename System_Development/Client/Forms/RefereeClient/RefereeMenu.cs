using System;
using System.Windows.Forms;

namespace Client.Forms.RefereeClient
{
    public partial class RefereeMenu : Form
    {
        public event EventHandler<EventArgs> EventJudgeCompetition;

        public event EventHandler<EventArgs> EventJudgeClientStart;

        public event EventHandler<EventArgs> EventUpdateRefereeClient;

        public event EventHandler<EventArgs> EventStartJudging;

        public event EventHandler<EventArgs> EventChangeIndexOfDiver; 

        public RefereeMenu()
        {
            InitializeComponent();
        }

        public void LoadForm()
        {
            OnEventJudgeClientStart();
            ShowDialog();
        }

        protected virtual void OnEventJudgeCompetition()
        {
            EventJudgeCompetition?.Invoke(this, EventArgs.Empty);
        }

        protected virtual void OnEventJudgeClientStart()
        {
            EventJudgeClientStart?.Invoke(this, EventArgs.Empty);
        }

        private void UpdateRefereeClientInformation_Click(object sender, EventArgs e)
        {
            OnEventUpdateRefereeClient();
        }

        protected virtual void OnEventUpdateRefereeClient()
        {
            EventUpdateRefereeClient?.Invoke(this, EventArgs.Empty);
        }

        private void StartJudgeButton_Click(object sender, EventArgs e)
        {
            OnEventStartJudging();
        }

        protected virtual void OnEventStartJudging()
        {
            EventStartJudging?.Invoke(this, EventArgs.Empty);
        }

        private void ActiveDiverDivesListBox_SelectedIndexChanged(object sender, EventArgs e)
        {
        }

        private void ActiveCompetitionDivers_SelectedIndexChanged(object sender, EventArgs e)
        {
            OnEventChangeIndexOfDiver();
        }

        protected virtual void OnEventChangeIndexOfDiver()
        {
            EventChangeIndexOfDiver?.Invoke(this, EventArgs.Empty);
        }
    }
}