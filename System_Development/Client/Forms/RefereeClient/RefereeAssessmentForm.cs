using ClassLibrary;
using System;
using System.Windows.Forms;

namespace Client.Forms.RefereeClient
{
    public partial class RefereeAssessmentForm : Form
    {
        public event EventHandler<EventArgs> EventClickSendButton;

        public RefereeAssessmentForm()
        {
            InitializeComponent();
        }

        public void LoadForm()
        {
            refButton0.Click += RefButtonClick;
            refButton1.Click += RefButtonClick;
            refButton2.Click += RefButtonClick;
            refButton3.Click += RefButtonClick;
            refButton4.Click += RefButtonClick;
            refButton5.Click += RefButtonClick;
            refButton6.Click += RefButtonClick;
            refButton7.Click += RefButtonClick;
            refButton8.Click += RefButtonClick;
            refButton9.Click += RefButtonClick;
            refButton10.Click += RefButtonClick;
            refButtonDot5.Click += RefButtonClick;

            ShowDialog();
        }

        /// <summary>
        ///     Håller koll på vilka värden som användaren får mata in i poänggivningsrutan
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void RefButtonClick(object sender, EventArgs e)
        {
            try
            {
                var button = sender as Button;

                if (button?.Name != "refButtonDot5")
                    refScoreTextBox.Text = string.Empty;

                switch (button?.Name)
                {
                    case "refButton1":
                        refScoreTextBox.Text = "1";
                        break;

                    case "refButton2":
                        refScoreTextBox.Text = "2";
                        break;

                    case "refButton3":
                        refScoreTextBox.Text = "3";
                        break;

                    case "refButton4":
                        refScoreTextBox.Text = "4";
                        break;

                    case "refButton5":
                        refScoreTextBox.Text = "5";
                        break;

                    case "refButton6":
                        refScoreTextBox.Text = "6";
                        break;

                    case "refButton7":
                        refScoreTextBox.Text = "7";
                        break;

                    case "refButton8":
                        refScoreTextBox.Text = "8";
                        break;

                    case "refButton9":
                        refScoreTextBox.Text = "9";
                        break;

                    case "refButton10":
                        refScoreTextBox.Text = "10";
                        break;

                    case "refButton0":
                        refScoreTextBox.Text = "0";
                        break;

                    case "refButtonDot5":
                        if (!refScoreTextBox.Text.Contains(".") &&
                            !refScoreTextBox.Text.Contains("10"))
                        {
                            refScoreTextBox.Text += ".5";
                        }
                        break;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Exception: " +
                    ex.Message);
            }
        }

        private void refScoreTextBox_KeyPress(object sender, KeyPressEventArgs e)
        {
            switch (e.KeyChar)
            {
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                case '0':
                    break;

                case (char)13:
                    OnEventClickSendButton();
                    break;

                default:
                    e.Handled = true;
                    MessageBox.Show("Ange endast siffror");
                    break;
            }
            refScoreTextBox.Text = string.Empty;
        }

        private void RefSendScoreButton_Click(object sender, EventArgs e)
        {
            OnEventClickSendButton();
        }

        protected virtual void OnEventClickSendButton()
        {
            EventClickSendButton?.Invoke(this, EventArgs.Empty);
        }
    }
}