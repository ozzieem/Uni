using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Client.Forms
{
    public partial class AddNewRefereeForm : Form
    {
        public event EventHandler<EventArgs> AddNewRefereeToDatabase;

        // Felcheckning krävs fortfarande att tas hand om.

        public AddNewRefereeForm()
        {
            InitializeComponent();
        }

        public void LoadForm()
        {
            ShowDialog();
        }

        private void FirstnameBox_TextChanged(object sender, EventArgs e)
        {
        }

        private void LastnameBox_TextChanged(object sender, EventArgs e)
        {
        }

        private void CountryBox_TextChanged(object sender, EventArgs e)
        {
        }

        private void UsernameBox_TextChanged(object sender, EventArgs e)
        {
        }

        private void PasswordBox_TextChanged(object sender, EventArgs e)
        {
        }

        private void CheckPasswordBox_TextChanged(object sender, EventArgs e)
        {
        }

        private void DoneButton_Click(object sender, EventArgs e)
        {
            OnAddNewRefereeToDatabase();
        }

        private void CancelingButton_Click(object sender, EventArgs e)
        {
            var dialogResult = MessageBox.Show(
                "Vill du verkligen Avsluta?",
                "Avsluta", MessageBoxButtons.YesNo);
            if (dialogResult == DialogResult.Yes)
            {
                Close();
            }
        }

        protected virtual void OnAddNewRefereeToDatabase()
        {
            if (AddNewRefereeToDatabase != null)
                AddNewRefereeToDatabase(this, EventArgs.Empty);
        }
    }
}