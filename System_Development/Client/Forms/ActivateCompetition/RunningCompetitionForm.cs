using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Client.Forms.ActivateCompetition
{
    public partial class RunningCompetitionForm : Form
    {


        public event EventHandler<EventArgs> EventClickNextAssignment;
        public event EventHandler<EventArgs> EventShowJudgeScores; 

        public RunningCompetitionForm()
        {
            InitializeComponent();
        }

        public void LoadForm()
        {
            ShowDialog();
        }

        private void NextAssignmentButton_Click(object sender, EventArgs e)
        {
            OnEventClickNextAssignment();
        }

        protected virtual void OnEventClickNextAssignment()
        {
            EventClickNextAssignment?.Invoke(this, EventArgs.Empty);
        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            OnEventShowJudgeScores();
        }

        protected virtual void OnEventShowJudgeScores()
        {
            EventShowJudgeScores?.Invoke(this, EventArgs.Empty);
        }

        private void backgroundWorker1_DoWork(object sender, DoWorkEventArgs e)
        {

        }
    }
}
