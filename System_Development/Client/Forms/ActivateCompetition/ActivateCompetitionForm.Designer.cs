namespace Client.Forms.ActivateCompetition
{
    partial class ActivateCompetitionForm
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
            this.listBox1 = new System.Windows.Forms.ListBox();
            this.SelectedTextLabel = new System.Windows.Forms.Label();
            this.SelectedCompetitionField = new System.Windows.Forms.Label();
            this.ActivateCompetitionButton = new System.Windows.Forms.Button();
            this.CancelButton = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.CompetitionNameLabel = new System.Windows.Forms.Label();
            this.CompetitionLocationLabel = new System.Windows.Forms.Label();
            this.CompetitionTypeLabel = new System.Windows.Forms.Label();
            this.CompetitionNumberOfJudgesLabel = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // listBox1
            // 
            this.listBox1.FormattingEnabled = true;
            this.listBox1.Location = new System.Drawing.Point(12, 34);
            this.listBox1.Name = "listBox1";
            this.listBox1.Size = new System.Drawing.Size(167, 290);
            this.listBox1.TabIndex = 0;
            this.listBox1.SelectedIndexChanged += new System.EventHandler(this.listBox1_SelectedIndexChanged);
            // 
            // SelectedTextLabel
            // 
            this.SelectedTextLabel.AutoSize = true;
            this.SelectedTextLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 15F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.SelectedTextLabel.Location = new System.Drawing.Point(234, 34);
            this.SelectedTextLabel.Name = "SelectedTextLabel";
            this.SelectedTextLabel.Size = new System.Drawing.Size(133, 25);
            this.SelectedTextLabel.TabIndex = 1;
            this.SelectedTextLabel.Text = "Vald Tävling";
            // 
            // SelectedCompetitionField
            // 
            this.SelectedCompetitionField.AutoSize = true;
            this.SelectedCompetitionField.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.SelectedCompetitionField.Location = new System.Drawing.Point(389, 81);
            this.SelectedCompetitionField.Name = "SelectedCompetitionField";
            this.SelectedCompetitionField.Size = new System.Drawing.Size(51, 20);
            this.SelectedCompetitionField.TabIndex = 2;
            this.SelectedCompetitionField.Text = "label1";
            // 
            // ActivateCompetitionButton
            // 
            this.ActivateCompetitionButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ActivateCompetitionButton.Location = new System.Drawing.Point(393, 320);
            this.ActivateCompetitionButton.Name = "ActivateCompetitionButton";
            this.ActivateCompetitionButton.Size = new System.Drawing.Size(103, 39);
            this.ActivateCompetitionButton.TabIndex = 3;
            this.ActivateCompetitionButton.Text = "Ok";
            this.ActivateCompetitionButton.UseVisualStyleBackColor = true;
            this.ActivateCompetitionButton.Click += new System.EventHandler(this.ActivateCompetitionButton_Click);
            // 
            // CancelButton
            // 
            this.CancelButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.CancelButton.Location = new System.Drawing.Point(239, 320);
            this.CancelButton.Name = "CancelButton";
            this.CancelButton.Size = new System.Drawing.Size(104, 39);
            this.CancelButton.TabIndex = 4;
            this.CancelButton.Text = "Avbryt";
            this.CancelButton.UseVisualStyleBackColor = true;
            this.CancelButton.Click += new System.EventHandler(this.CancelButton_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(235, 81);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(30, 20);
            this.label1.TabIndex = 5;
            this.label1.Text = "ID:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(235, 116);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(55, 20);
            this.label2.TabIndex = 6;
            this.label2.Text = "Namn:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(235, 154);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(48, 20);
            this.label3.TabIndex = 7;
            this.label3.Text = "Plats:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(235, 196);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(38, 20);
            this.label4.TabIndex = 8;
            this.label4.Text = "Typ:";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.Location = new System.Drawing.Point(235, 236);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(108, 20);
            this.label5.TabIndex = 9;
            this.label5.Text = "Antal domare:";
            // 
            // CompetitionNameLabel
            // 
            this.CompetitionNameLabel.AutoSize = true;
            this.CompetitionNameLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.CompetitionNameLabel.Location = new System.Drawing.Point(389, 116);
            this.CompetitionNameLabel.Name = "CompetitionNameLabel";
            this.CompetitionNameLabel.Size = new System.Drawing.Size(51, 20);
            this.CompetitionNameLabel.TabIndex = 10;
            this.CompetitionNameLabel.Text = "label6";
            // 
            // CompetitionLocationLabel
            // 
            this.CompetitionLocationLabel.AutoSize = true;
            this.CompetitionLocationLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.CompetitionLocationLabel.Location = new System.Drawing.Point(389, 154);
            this.CompetitionLocationLabel.Name = "CompetitionLocationLabel";
            this.CompetitionLocationLabel.Size = new System.Drawing.Size(51, 20);
            this.CompetitionLocationLabel.TabIndex = 11;
            this.CompetitionLocationLabel.Text = "label6";
            // 
            // CompetitionTypeLabel
            // 
            this.CompetitionTypeLabel.AutoSize = true;
            this.CompetitionTypeLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.CompetitionTypeLabel.Location = new System.Drawing.Point(389, 196);
            this.CompetitionTypeLabel.Name = "CompetitionTypeLabel";
            this.CompetitionTypeLabel.Size = new System.Drawing.Size(51, 20);
            this.CompetitionTypeLabel.TabIndex = 12;
            this.CompetitionTypeLabel.Text = "label6";
            // 
            // CompetitionNumberOfJudgesLabel
            // 
            this.CompetitionNumberOfJudgesLabel.AutoSize = true;
            this.CompetitionNumberOfJudgesLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.CompetitionNumberOfJudgesLabel.Location = new System.Drawing.Point(389, 236);
            this.CompetitionNumberOfJudgesLabel.Name = "CompetitionNumberOfJudgesLabel";
            this.CompetitionNumberOfJudgesLabel.Size = new System.Drawing.Size(51, 20);
            this.CompetitionNumberOfJudgesLabel.TabIndex = 13;
            this.CompetitionNumberOfJudgesLabel.Text = "label6";
            // 
            // ActivateCompetitionForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(638, 400);
            this.Controls.Add(this.CompetitionNumberOfJudgesLabel);
            this.Controls.Add(this.CompetitionTypeLabel);
            this.Controls.Add(this.CompetitionLocationLabel);
            this.Controls.Add(this.CompetitionNameLabel);
            this.Controls.Add(this.label5);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.CancelButton);
            this.Controls.Add(this.ActivateCompetitionButton);
            this.Controls.Add(this.SelectedCompetitionField);
            this.Controls.Add(this.SelectedTextLabel);
            this.Controls.Add(this.listBox1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Name = "ActivateCompetitionForm";
            this.Text = "Aktivera Tävling";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.Label SelectedTextLabel;
        private System.Windows.Forms.Button ActivateCompetitionButton;
        private System.Windows.Forms.Button CancelButton;
        public System.Windows.Forms.ListBox listBox1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        public System.Windows.Forms.Label CompetitionNameLabel;
        public System.Windows.Forms.Label CompetitionLocationLabel;
        public System.Windows.Forms.Label CompetitionTypeLabel;
        public System.Windows.Forms.Label CompetitionNumberOfJudgesLabel;
        public System.Windows.Forms.Label SelectedCompetitionField;
    }
}