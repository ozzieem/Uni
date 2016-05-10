namespace Client.Forms.ActivateCompetition
{
    partial class RunningCompetitionForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.divesListBox = new System.Windows.Forms.ListBox();
            this.Judge1 = new System.Windows.Forms.Label();
            this.Judge2 = new System.Windows.Forms.Label();
            this.Judge3 = new System.Windows.Forms.Label();
            this.Judge4 = new System.Windows.Forms.Label();
            this.Judge5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label10 = new System.Windows.Forms.Label();
            this.label11 = new System.Windows.Forms.Label();
            this.label12 = new System.Windows.Forms.Label();
            this.label13 = new System.Windows.Forms.Label();
            this.TotalPoints = new System.Windows.Forms.Label();
            this.DiveTitle = new System.Windows.Forms.Label();
            this.NextAssignmentButton = new System.Windows.Forms.Button();
            this.waitForAssessmentsProgressBar = new System.Windows.Forms.ProgressBar();
            this.backgroundWorker1 = new System.ComponentModel.BackgroundWorker();
            this.scoreBoardListBox = new System.Windows.Forms.ListBox();
            this.label1 = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // divesListBox
            // 
            this.divesListBox.FormattingEnabled = true;
            this.divesListBox.Location = new System.Drawing.Point(12, 12);
            this.divesListBox.Name = "divesListBox";
            this.divesListBox.Size = new System.Drawing.Size(174, 433);
            this.divesListBox.TabIndex = 0;
            this.divesListBox.SelectedIndexChanged += new System.EventHandler(this.listBox1_SelectedIndexChanged);
            // 
            // Judge1
            // 
            this.Judge1.AutoSize = true;
            this.Judge1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Judge1.Location = new System.Drawing.Point(299, 107);
            this.Judge1.Name = "Judge1";
            this.Judge1.Size = new System.Drawing.Size(66, 20);
            this.Judge1.TabIndex = 1;
            this.Judge1.Text = "Judge 1";
            // 
            // Judge2
            // 
            this.Judge2.AutoSize = true;
            this.Judge2.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Judge2.Location = new System.Drawing.Point(428, 107);
            this.Judge2.Name = "Judge2";
            this.Judge2.Size = new System.Drawing.Size(66, 20);
            this.Judge2.TabIndex = 2;
            this.Judge2.Text = "Judge 2";
            // 
            // Judge3
            // 
            this.Judge3.AutoSize = true;
            this.Judge3.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Judge3.Location = new System.Drawing.Point(558, 107);
            this.Judge3.Name = "Judge3";
            this.Judge3.Size = new System.Drawing.Size(66, 20);
            this.Judge3.TabIndex = 3;
            this.Judge3.Text = "Judge 3";
            // 
            // Judge4
            // 
            this.Judge4.AutoSize = true;
            this.Judge4.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Judge4.Location = new System.Drawing.Point(691, 107);
            this.Judge4.Name = "Judge4";
            this.Judge4.Size = new System.Drawing.Size(66, 20);
            this.Judge4.TabIndex = 4;
            this.Judge4.Text = "Judge 4";
            this.Judge4.Visible = false;
            // 
            // Judge5
            // 
            this.Judge5.AutoSize = true;
            this.Judge5.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Judge5.Location = new System.Drawing.Point(811, 107);
            this.Judge5.Name = "Judge5";
            this.Judge5.Size = new System.Drawing.Size(66, 20);
            this.Judge5.TabIndex = 5;
            this.Judge5.Text = "Judge 5";
            this.Judge5.Visible = false;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label6.Location = new System.Drawing.Point(314, 152);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(51, 20);
            this.label6.TabIndex = 6;
            this.label6.Text = "label6";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label7.Location = new System.Drawing.Point(443, 152);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(51, 20);
            this.label7.TabIndex = 7;
            this.label7.Text = "label7";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label8.Location = new System.Drawing.Point(573, 152);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(51, 20);
            this.label8.TabIndex = 8;
            this.label8.Text = "label8";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label9.Location = new System.Drawing.Point(706, 152);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(51, 20);
            this.label9.TabIndex = 9;
            this.label9.Text = "label9";
            this.label9.Visible = false;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label10.Location = new System.Drawing.Point(817, 152);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(60, 20);
            this.label10.TabIndex = 10;
            this.label10.Text = "label10";
            this.label10.Visible = false;
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label11.Location = new System.Drawing.Point(204, 107);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(77, 20);
            this.label11.TabIndex = 11;
            this.label11.Text = "Domare:";
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Cursor = System.Windows.Forms.Cursors.Default;
            this.label12.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label12.Location = new System.Drawing.Point(207, 148);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(65, 20);
            this.label12.TabIndex = 12;
            this.label12.Text = "Poäng:";
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label13.Location = new System.Drawing.Point(207, 228);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(148, 25);
            this.label13.TabIndex = 13;
            this.label13.Text = "Totala Poäng:";
            // 
            // TotalPoints
            // 
            this.TotalPoints.AutoSize = true;
            this.TotalPoints.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.TotalPoints.Location = new System.Drawing.Point(397, 228);
            this.TotalPoints.Name = "TotalPoints";
            this.TotalPoints.Size = new System.Drawing.Size(82, 25);
            this.TotalPoints.TabIndex = 14;
            this.TotalPoints.Text = "label14";
            // 
            // DiveTitle
            // 
            this.DiveTitle.AutoSize = true;
            this.DiveTitle.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.DiveTitle.Location = new System.Drawing.Point(475, 44);
            this.DiveTitle.Name = "DiveTitle";
            this.DiveTitle.Size = new System.Drawing.Size(70, 25);
            this.DiveTitle.TabIndex = 15;
            this.DiveTitle.Text = "Hopp:";
            // 
            // NextAssignmentButton
            // 
            this.NextAssignmentButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.NextAssignmentButton.Location = new System.Drawing.Point(440, 367);
            this.NextAssignmentButton.Name = "NextAssignmentButton";
            this.NextAssignmentButton.Size = new System.Drawing.Size(169, 46);
            this.NextAssignmentButton.TabIndex = 16;
            this.NextAssignmentButton.Text = "Nästa Hopp";
            this.NextAssignmentButton.UseVisualStyleBackColor = true;
            this.NextAssignmentButton.Click += new System.EventHandler(this.NextAssignmentButton_Click);
            // 
            // waitForAssessmentsProgressBar
            // 
            this.waitForAssessmentsProgressBar.Location = new System.Drawing.Point(440, 323);
            this.waitForAssessmentsProgressBar.Name = "waitForAssessmentsProgressBar";
            this.waitForAssessmentsProgressBar.Size = new System.Drawing.Size(169, 23);
            this.waitForAssessmentsProgressBar.Style = System.Windows.Forms.ProgressBarStyle.Marquee;
            this.waitForAssessmentsProgressBar.TabIndex = 17;
            // 
            // backgroundWorker1
            // 
            this.backgroundWorker1.DoWork += new System.ComponentModel.DoWorkEventHandler(this.backgroundWorker1_DoWork);
            // 
            // scoreBoardListBox
            // 
            this.scoreBoardListBox.FormattingEnabled = true;
            this.scoreBoardListBox.Location = new System.Drawing.Point(784, 233);
            this.scoreBoardListBox.Name = "scoreBoardListBox";
            this.scoreBoardListBox.Size = new System.Drawing.Size(196, 212);
            this.scoreBoardListBox.TabIndex = 18;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(780, 198);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(127, 20);
            this.label1.TabIndex = 19;
            this.label1.Text = "Poängställning";
            // 
            // RunningCompetitionForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(992, 462);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.scoreBoardListBox);
            this.Controls.Add(this.waitForAssessmentsProgressBar);
            this.Controls.Add(this.NextAssignmentButton);
            this.Controls.Add(this.DiveTitle);
            this.Controls.Add(this.TotalPoints);
            this.Controls.Add(this.label13);
            this.Controls.Add(this.label12);
            this.Controls.Add(this.label11);
            this.Controls.Add(this.label10);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.label6);
            this.Controls.Add(this.Judge5);
            this.Controls.Add(this.Judge4);
            this.Controls.Add(this.Judge3);
            this.Controls.Add(this.Judge2);
            this.Controls.Add(this.Judge1);
            this.Controls.Add(this.divesListBox);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Name = "RunningCompetitionForm";
            this.Text = "Tävling";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.Label label12;
        private System.Windows.Forms.Label label13;
        public System.Windows.Forms.Label DiveTitle;
        public System.Windows.Forms.ListBox divesListBox;
        public System.Windows.Forms.Label Judge4;
        public System.Windows.Forms.Label Judge5;
        public System.Windows.Forms.Label label6;
        public System.Windows.Forms.Label label7;
        public System.Windows.Forms.Label label8;
        public System.Windows.Forms.Label label9;
        public System.Windows.Forms.Label label10;
        public System.Windows.Forms.Label TotalPoints;
        public System.Windows.Forms.Label Judge1;
        public System.Windows.Forms.Label Judge2;
        public System.Windows.Forms.Label Judge3;
        public System.Windows.Forms.ProgressBar waitForAssessmentsProgressBar;
        private System.ComponentModel.BackgroundWorker backgroundWorker1;
        public System.Windows.Forms.Button NextAssignmentButton;
        public System.Windows.Forms.ListBox scoreBoardListBox;
        private System.Windows.Forms.Label label1;
    }
}