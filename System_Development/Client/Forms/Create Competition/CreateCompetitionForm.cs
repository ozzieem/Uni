using System;
using System.Collections.Generic;
using System.Windows.Forms;

namespace Client
{
    public partial class CreateCompetitionForm : Form
    {
        private DateTime timeStamp;
        public List<TextBox> textboxes = new List<TextBox>();

        public event EventHandler<EventArgs> AddDiverToList;

        public event EventHandler<EventArgs> RemoveDiverFromList;

        public event EventHandler<EventArgs> AddReferees;

        public event EventHandler<EventArgs> ShowAddedDiverCodes;

        public event EventHandler<EventArgs> UserClosing;

        public event EventHandler<EventArgs> CreateCompleteCompetition;

        public CreateCompetitionForm()
        {
            InitializeComponent();
        }

        public void LoadForm()
        {
            ShowDialog();
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            FindAllOfMyString(textBox1.Text);
        }

        private void AddDiverButton_Click(object sender, EventArgs e)
        {
            if ((DateTime.Now - timeStamp).Ticks < 5000000) return;
            timeStamp = DateTime.Now;

            OnAddedDiverToList();
        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (listBox1.SelectedItem != null)
                label7.Text = listBox1.SelectedItem.ToString();
        }

        private void listBox2_SelectedIndexChanged(object sender, EventArgs e)
        {
            OnShowAddedDiverCodes();
        }

        private void button2_Click(object sender, EventArgs e)
        {
            if ((DateTime.Now - timeStamp).Ticks < 5000000) return;
            timeStamp = DateTime.Now;

            OnRemoveDiverFromList();
        }

        private void FindAllOfMyString(string searchString)
        {
            for (int i = 0; i < listBox1.Items.Count; i++)
            {
                if (listBox1.Items[i].ToString().IndexOf(searchString, StringComparison.OrdinalIgnoreCase) >= 0)
                {
                    listBox1.SetSelected(i, true);
                    return;
                }
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            OnAddReferees();
        }

        public virtual void OnAddedDiverToList()
        {
            if (AddDiverToList != null)
                AddDiverToList(this, EventArgs.Empty);
        }

        protected virtual void OnShowAddedDiverCodes()
        {
            if (ShowAddedDiverCodes != null)
                ShowAddedDiverCodes(this, EventArgs.Empty);
        }

        protected virtual void OnAddReferees()
        {
            if (AddReferees != null)
                AddReferees(this, EventArgs.Empty);
        }

        protected virtual void OnRemoveDiverFromList()
        {
            if (RemoveDiverFromList != null)
                RemoveDiverFromList(this, EventArgs.Empty);
        }

        private void CreateCompetition_Click(object sender, EventArgs e)
        {
            OnCreateCompleteCompetition();
        }

        protected void OnCreateCompleteCompetition()
        {
            if (CreateCompleteCompetition != null)
                CreateCompleteCompetition(this, EventArgs.Empty);
        }

        protected virtual void OnUserClosing()
        {
            if (UserClosing != null)
                UserClosing(this, EventArgs.Empty);
        }

        #region Skumma funktioner RÖR EJ!!!

        private void textBox2_TextChanged(object sender, EventArgs e)
        {
        }

        private void label8_Click(object sender, EventArgs e)
        {
        }

        private void label2_Click(object sender, EventArgs e)
        {
        }

        private void listBox4_SelectedIndexChanged(object sender, EventArgs e)
        {
        }

        private void CreateCompetitionForm_Load(object sender, EventArgs e)
        {
        }

        #endregion Skumma funktioner RÖR EJ!!!

        private void CancelCompetitionButton_Click(object sender, EventArgs e)
        {
            OnUserClosing();
        }
    }
}