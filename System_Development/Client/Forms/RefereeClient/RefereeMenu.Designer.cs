namespace Client.Forms.RefereeClient
{
    partial class RefereeMenu
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
            this.ActiveCompetitionInfo = new System.Windows.Forms.Label();
            this.ActiveCompetitionDivers = new System.Windows.Forms.ListBox();
            this.UpdateRefereeClientInformation = new System.Windows.Forms.Button();
            this.StartJudgeButton = new System.Windows.Forms.Button();
            this.ActiveDiverCountLabel = new System.Windows.Forms.Label();
            this.ActiveDiverDivesListBox = new System.Windows.Forms.ListBox();
            this.SuspendLayout();
            // 
            // ActiveCompetitionInfo
            // 
            this.ActiveCompetitionInfo.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom)));
            this.ActiveCompetitionInfo.AutoSize = true;
            this.ActiveCompetitionInfo.BorderStyle = System.Windows.Forms.BorderStyle.Fixed3D;
            this.ActiveCompetitionInfo.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ActiveCompetitionInfo.Location = new System.Drawing.Point(193, 40);
            this.ActiveCompetitionInfo.Name = "ActiveCompetitionInfo";
            this.ActiveCompetitionInfo.Size = new System.Drawing.Size(137, 22);
            this.ActiveCompetitionInfo.TabIndex = 1;
            this.ActiveCompetitionInfo.Text = "Ingen aktiv tävling";
            this.ActiveCompetitionInfo.TextAlign = System.Drawing.ContentAlignment.TopCenter;
            // 
            // ActiveCompetitionDivers
            // 
            this.ActiveCompetitionDivers.FormattingEnabled = true;
            this.ActiveCompetitionDivers.Location = new System.Drawing.Point(86, 129);
            this.ActiveCompetitionDivers.Name = "ActiveCompetitionDivers";
            this.ActiveCompetitionDivers.Size = new System.Drawing.Size(149, 95);
            this.ActiveCompetitionDivers.TabIndex = 2;
            this.ActiveCompetitionDivers.SelectedIndexChanged += new System.EventHandler(this.ActiveCompetitionDivers_SelectedIndexChanged);
            // 
            // UpdateRefereeClientInformation
            // 
            this.UpdateRefereeClientInformation.Location = new System.Drawing.Point(12, 12);
            this.UpdateRefereeClientInformation.Name = "UpdateRefereeClientInformation";
            this.UpdateRefereeClientInformation.Size = new System.Drawing.Size(75, 23);
            this.UpdateRefereeClientInformation.TabIndex = 3;
            this.UpdateRefereeClientInformation.Text = "Uppdatera";
            this.UpdateRefereeClientInformation.UseVisualStyleBackColor = true;
            this.UpdateRefereeClientInformation.Click += new System.EventHandler(this.UpdateRefereeClientInformation_Click);
            // 
            // StartJudgeButton
            // 
            this.StartJudgeButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.StartJudgeButton.Location = new System.Drawing.Point(193, 260);
            this.StartJudgeButton.Name = "StartJudgeButton";
            this.StartJudgeButton.Size = new System.Drawing.Size(157, 33);
            this.StartJudgeButton.TabIndex = 5;
            this.StartJudgeButton.Text = "Börja döm tävling";
            this.StartJudgeButton.UseVisualStyleBackColor = true;
            this.StartJudgeButton.Click += new System.EventHandler(this.StartJudgeButton_Click);
            // 
            // ActiveDiverCountLabel
            // 
            this.ActiveDiverCountLabel.AutoSize = true;
            this.ActiveDiverCountLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ActiveDiverCountLabel.Location = new System.Drawing.Point(83, 96);
            this.ActiveDiverCountLabel.Name = "ActiveDiverCountLabel";
            this.ActiveDiverCountLabel.Size = new System.Drawing.Size(131, 17);
            this.ActiveDiverCountLabel.TabIndex = 6;
            this.ActiveDiverCountLabel.Text = "Hoppare i tävlingen";
            // 
            // ActiveDiverDivesListBox
            // 
            this.ActiveDiverDivesListBox.FormattingEnabled = true;
            this.ActiveDiverDivesListBox.Location = new System.Drawing.Point(300, 129);
            this.ActiveDiverDivesListBox.Name = "ActiveDiverDivesListBox";
            this.ActiveDiverDivesListBox.Size = new System.Drawing.Size(140, 95);
            this.ActiveDiverDivesListBox.TabIndex = 7;
            this.ActiveDiverDivesListBox.SelectedIndexChanged += new System.EventHandler(this.ActiveDiverDivesListBox_SelectedIndexChanged);
            // 
            // RefereeMenu
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(550, 328);
            this.Controls.Add(this.ActiveDiverDivesListBox);
            this.Controls.Add(this.ActiveDiverCountLabel);
            this.Controls.Add(this.ActiveCompetitionInfo);
            this.Controls.Add(this.StartJudgeButton);
            this.Controls.Add(this.UpdateRefereeClientInformation);
            this.Controls.Add(this.ActiveCompetitionDivers);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Name = "RefereeMenu";
            this.Text = "Döm tävling";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        public System.Windows.Forms.Label ActiveCompetitionInfo;
        public System.Windows.Forms.ListBox ActiveCompetitionDivers;
        public System.Windows.Forms.Button UpdateRefereeClientInformation;
        private System.Windows.Forms.Button StartJudgeButton;
        private System.Windows.Forms.Label ActiveDiverCountLabel;
        public System.Windows.Forms.ListBox ActiveDiverDivesListBox;
    }
}