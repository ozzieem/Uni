using System.ComponentModel;
using System.Windows.Forms;

namespace Client
{
    partial class MainAdminForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private IContainer components = null;

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
            this.CreateNewDiverButton = new System.Windows.Forms.Button();
            this.createCompetitionButton = new System.Windows.Forms.Button();
            this.CreateNewReferee = new System.Windows.Forms.Button();
            this.activate_button = new System.Windows.Forms.Button();
            this.QuitButton = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // CreateNewDiverButton
            // 
            this.CreateNewDiverButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.CreateNewDiverButton.Location = new System.Drawing.Point(30, 149);
            this.CreateNewDiverButton.Name = "CreateNewDiverButton";
            this.CreateNewDiverButton.Size = new System.Drawing.Size(167, 33);
            this.CreateNewDiverButton.TabIndex = 2;
            this.CreateNewDiverButton.Text = "Registrera Ny Hoppare";
            this.CreateNewDiverButton.UseVisualStyleBackColor = true;
            this.CreateNewDiverButton.Click += new System.EventHandler(this.CreateNewDiverButton_Click);
            // 
            // createCompetitionButton
            // 
            this.createCompetitionButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.createCompetitionButton.Location = new System.Drawing.Point(30, 31);
            this.createCompetitionButton.Name = "createCompetitionButton";
            this.createCompetitionButton.Size = new System.Drawing.Size(167, 59);
            this.createCompetitionButton.TabIndex = 0;
            this.createCompetitionButton.Text = "Skapa Ny Tävling";
            this.createCompetitionButton.UseVisualStyleBackColor = true;
            this.createCompetitionButton.Click += new System.EventHandler(this.createCompetitionButton_Click);
            // 
            // CreateNewReferee
            // 
            this.CreateNewReferee.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.CreateNewReferee.Location = new System.Drawing.Point(30, 199);
            this.CreateNewReferee.Name = "CreateNewReferee";
            this.CreateNewReferee.Size = new System.Drawing.Size(167, 33);
            this.CreateNewReferee.TabIndex = 3;
            this.CreateNewReferee.Text = "Registrera Ny Domare";
            this.CreateNewReferee.UseVisualStyleBackColor = true;
            this.CreateNewReferee.Click += new System.EventHandler(this.CreateNewReferee_Click);
            // 
            // activate_button
            // 
            this.activate_button.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.activate_button.Location = new System.Drawing.Point(230, 31);
            this.activate_button.Name = "activate_button";
            this.activate_button.Size = new System.Drawing.Size(167, 59);
            this.activate_button.TabIndex = 1;
            this.activate_button.Text = "Aktivera Tävling";
            this.activate_button.UseVisualStyleBackColor = true;
            this.activate_button.Click += new System.EventHandler(this.activate_button_Click);
            // 
            // QuitButton
            // 
            this.QuitButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.QuitButton.Location = new System.Drawing.Point(230, 242);
            this.QuitButton.Name = "QuitButton";
            this.QuitButton.Size = new System.Drawing.Size(167, 33);
            this.QuitButton.TabIndex = 4;
            this.QuitButton.Text = "Avsluta";
            this.QuitButton.UseVisualStyleBackColor = true;
            this.QuitButton.Click += new System.EventHandler(this.QuitButton_Click);
            // 
            // MainAdminForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(443, 312);
            this.Controls.Add(this.QuitButton);
            this.Controls.Add(this.activate_button);
            this.Controls.Add(this.CreateNewReferee);
            this.Controls.Add(this.createCompetitionButton);
            this.Controls.Add(this.CreateNewDiverButton);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Name = "MainAdminForm";
            this.Text = "Adminmeny";
            this.ResumeLayout(false);

        }

        #endregion

        private Button CreateNewDiverButton;
        private Button createCompetitionButton;
        private Button CreateNewReferee;
        private Button activate_button;
        private Button QuitButton;
    }
}