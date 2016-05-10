using System.ComponentModel;
using System.Windows.Forms;

namespace Client
{
    partial class AddDiverForm
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
            this.Create = new System.Windows.Forms.Button();
            this.nameBox = new System.Windows.Forms.TextBox();
            this.CountryBox = new System.Windows.Forms.TextBox();
            this.nameLabel = new System.Windows.Forms.Label();
            this.countryLabel = new System.Windows.Forms.Label();
            this.AgeBox = new System.Windows.Forms.TextBox();
            this.diverIDBox = new System.Windows.Forms.TextBox();
            this.ageLabel = new System.Windows.Forms.Label();
            this.DiverIDLabel = new System.Windows.Forms.Label();
            this.radioWoman = new System.Windows.Forms.RadioButton();
            this.radioMan = new System.Windows.Forms.RadioButton();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.QuitButton = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // Create
            // 
            this.Create.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.Create.Location = new System.Drawing.Point(197, 206);
            this.Create.Name = "Create";
            this.Create.Size = new System.Drawing.Size(104, 44);
            this.Create.TabIndex = 5;
            this.Create.Text = "Skapa";
            this.Create.UseVisualStyleBackColor = true;
            this.Create.Click += new System.EventHandler(this.Create_Click);
            // 
            // nameBox
            // 
            this.nameBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.nameBox.Location = new System.Drawing.Point(23, 68);
            this.nameBox.Name = "nameBox";
            this.nameBox.Size = new System.Drawing.Size(133, 23);
            this.nameBox.TabIndex = 0;
            // 
            // CountryBox
            // 
            this.CountryBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.CountryBox.Location = new System.Drawing.Point(23, 145);
            this.CountryBox.Name = "CountryBox";
            this.CountryBox.Size = new System.Drawing.Size(133, 23);
            this.CountryBox.TabIndex = 2;
            // 
            // nameLabel
            // 
            this.nameLabel.AutoSize = true;
            this.nameLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.nameLabel.Location = new System.Drawing.Point(20, 35);
            this.nameLabel.Name = "nameLabel";
            this.nameLabel.Size = new System.Drawing.Size(51, 20);
            this.nameLabel.TabIndex = 4;
            this.nameLabel.Text = "Namn";
            // 
            // countryLabel
            // 
            this.countryLabel.AutoSize = true;
            this.countryLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.countryLabel.Location = new System.Drawing.Point(22, 112);
            this.countryLabel.Name = "countryLabel";
            this.countryLabel.Size = new System.Drawing.Size(45, 20);
            this.countryLabel.TabIndex = 5;
            this.countryLabel.Text = "Land";
            // 
            // AgeBox
            // 
            this.AgeBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.AgeBox.Location = new System.Drawing.Point(201, 68);
            this.AgeBox.Name = "AgeBox";
            this.AgeBox.Size = new System.Drawing.Size(130, 23);
            this.AgeBox.TabIndex = 1;
            this.AgeBox.TextChanged += new System.EventHandler(this.textBox4_TextChanged);
            // 
            // diverIDBox
            // 
            this.diverIDBox.Font = new System.Drawing.Font("Microsoft Sans Serif", 10F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.diverIDBox.Location = new System.Drawing.Point(197, 145);
            this.diverIDBox.Name = "diverIDBox";
            this.diverIDBox.Size = new System.Drawing.Size(134, 23);
            this.diverIDBox.TabIndex = 3;
            // 
            // ageLabel
            // 
            this.ageLabel.AutoSize = true;
            this.ageLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ageLabel.Location = new System.Drawing.Point(198, 35);
            this.ageLabel.Name = "ageLabel";
            this.ageLabel.Size = new System.Drawing.Size(46, 20);
            this.ageLabel.TabIndex = 9;
            this.ageLabel.Text = "Ålder";
            // 
            // DiverIDLabel
            // 
            this.DiverIDLabel.AutoSize = true;
            this.DiverIDLabel.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.DiverIDLabel.Location = new System.Drawing.Point(198, 112);
            this.DiverIDLabel.Name = "DiverIDLabel";
            this.DiverIDLabel.Size = new System.Drawing.Size(107, 20);
            this.DiverIDLabel.TabIndex = 10;
            this.DiverIDLabel.Text = "Simhoppar ID";
            // 
            // radioWoman
            // 
            this.radioWoman.AutoSize = true;
            this.radioWoman.Location = new System.Drawing.Point(0, 25);
            this.radioWoman.Name = "radioWoman";
            this.radioWoman.Size = new System.Drawing.Size(74, 24);
            this.radioWoman.TabIndex = 0;
            this.radioWoman.TabStop = true;
            this.radioWoman.Text = "Kvinna";
            this.radioWoman.UseVisualStyleBackColor = true;
            // 
            // radioMan
            // 
            this.radioMan.AutoSize = true;
            this.radioMan.Location = new System.Drawing.Point(0, 47);
            this.radioMan.Name = "radioMan";
            this.radioMan.Size = new System.Drawing.Size(58, 24);
            this.radioMan.TabIndex = 1;
            this.radioMan.TabStop = true;
            this.radioMan.Text = "Man";
            this.radioMan.UseVisualStyleBackColor = true;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.radioWoman);
            this.groupBox1.Controls.Add(this.radioMan);
            this.groupBox1.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.groupBox1.Location = new System.Drawing.Point(26, 201);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(97, 77);
            this.groupBox1.TabIndex = 4;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Kön";
            // 
            // QuitButton
            // 
            this.QuitButton.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.QuitButton.Location = new System.Drawing.Point(197, 265);
            this.QuitButton.Name = "QuitButton";
            this.QuitButton.Size = new System.Drawing.Size(104, 44);
            this.QuitButton.TabIndex = 6;
            this.QuitButton.Text = "Avsluta";
            this.QuitButton.UseVisualStyleBackColor = true;
            this.QuitButton.Click += new System.EventHandler(this.QuitButton_Click);
            // 
            // AddDiverForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(392, 333);
            this.Controls.Add(this.QuitButton);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.DiverIDLabel);
            this.Controls.Add(this.ageLabel);
            this.Controls.Add(this.diverIDBox);
            this.Controls.Add(this.AgeBox);
            this.Controls.Add(this.countryLabel);
            this.Controls.Add(this.nameLabel);
            this.Controls.Add(this.CountryBox);
            this.Controls.Add(this.nameBox);
            this.Controls.Add(this.Create);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.Name = "AddDiverForm";
            this.Text = "Skapa Ny Simhoppare";
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private Button Create;
        private Label nameLabel;
        private Label countryLabel;
        private Label ageLabel;
        private Label DiverIDLabel;
        private GroupBox groupBox1;
        public TextBox nameBox;
        public TextBox CountryBox;
        public TextBox AgeBox;
        public TextBox diverIDBox;
        public RadioButton radioWoman;
        public RadioButton radioMan;
        private Button QuitButton;
    }
}