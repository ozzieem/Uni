using System;
using System.Windows.Forms;

namespace Client.Forms.Create_Competition
{
    public partial class CreateRefereeList : Form
    {
        public event EventHandler<EventArgs> AddRefereeToList;
        public event EventHandler<EventArgs> RemoveRefereeFromList;
        public event EventHandler<EventArgs> PressingDoneButton;

        public CreateRefereeList()
        {
            InitializeComponent();
        }

        public void LoadRefereeCreationForm()
        {
            ShowDialog();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            OnAddRefereeToList();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            OnRemoveRefereeFromList();
        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
        }

        private void listBox2_SelectedIndexChanged(object sender, EventArgs e)
        {
        }

        protected void OnAddRefereeToList()
        {
            if (AddRefereeToList != null)
                AddRefereeToList(this, EventArgs.Empty);
        }

        protected void OnRemoveRefereeFromList()
        {
            if (RemoveRefereeFromList != null)
                RemoveRefereeFromList(this, EventArgs.Empty);
        }

        protected void OnPressingDoneButton()
        {
            if (PressingDoneButton != null)
                PressingDoneButton(this, EventArgs.Empty);
        }

        private void Done_Click(object sender, EventArgs e)
        {
            OnPressingDoneButton();
            Close();
        }
    }
}