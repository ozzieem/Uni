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
    public partial class ActivateCompetitionForm : Form
    {
        public event EventHandler<EventArgs> EventActivateCompetitionButton;

        public event EventHandler<EventArgs> EventChangeIndexOfChoosenCompetition;

        public ActivateCompetitionForm()
        {
            InitializeComponent();
        }

        public void LoadForm()
        {
            ShowDialog();
        }

        private void ActivateCompetitionButton_Click(object sender, EventArgs e)
        {
            OnEventActivateCompetitionButton();
        }

        private void CancelButton_Click(object sender, EventArgs e)
        {
            var dialogResult =
                MessageBox.Show(
                "Are you sure?",
                "Cancel Activation",
                MessageBoxButtons.YesNo);
            if (dialogResult == DialogResult.Yes)
            {
                Close();
            }
        }

        protected void OnEventActivateCompetitionButton()
        {
            if (EventActivateCompetitionButton != null)
                EventActivateCompetitionButton(this, EventArgs.Empty);
        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            OnEventChangeIndexOfChoosenCompetition();
        }

        protected virtual void OnEventChangeIndexOfChoosenCompetition()
        {
            EventChangeIndexOfChoosenCompetition?.Invoke(this, EventArgs.Empty);
        }
    }
}