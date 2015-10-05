using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Test_window
{

    public partial class Form1 : Form
    {
        FormInputDialog _fid;

        public Form1()
        {
            _fid = new FormInputDialog();
            this.InitializeComponent();
        }

        private void läsToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            _fid.ShowDialog();
        }
    }


}



