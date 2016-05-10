using ClassLibrary;
using System;
using System.Diagnostics.Eventing.Reader;
using System.Windows.Forms;

namespace Client
{
    public partial class AddDiverForm : Form
    {
        public event EventHandler<EventArgs> AddDiverToDatabase;

        public event EventHandler<EventArgs> EventQuitOnClickButton;

        public AddDiverForm()
        {
            InitializeComponent();
        }

        public void LoadForm()
        {
            ShowDialog();
        }

        private void textBox4_TextChanged(object sender, EventArgs e)
        {
        }

        private void Create_Click(object sender, EventArgs e)
        {
            OnAddDiverToDatabase();
        }

        protected virtual void OnAddDiverToDatabase()
        {
            if (AddDiverToDatabase != null)
                AddDiverToDatabase(this, EventArgs.Empty);
        }

        private void QuitButton_Click(object sender, EventArgs e)
        {
            OnEventQuitOnClickButton();
        }

        protected virtual void OnEventQuitOnClickButton()
        {
            EventQuitOnClickButton?.Invoke(this, EventArgs.Empty);
        }
    }
}