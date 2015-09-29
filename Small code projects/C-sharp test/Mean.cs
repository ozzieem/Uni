using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace C_sharp_test
{
    public class Mean   // Public makes the class detectable outside the namespace
    {
        private double sum = 0;
        private int nSum = 0;

        public Mean() { }   // Initiering skedd redan innan
        public Mean(double sum, int nSum)
        {
            this.sum = sum;
            this.nSum = nSum;
        }

        public void add(double x)
        {
            this.sum += x;
            nSum++;
        }

        public double GetMean()
        {
            return sum / nSum;
        }

        //Properties i C# <=> get/set
        public int NSum
        {
            get { return nSum; }
            set { nSum = value; }   // value nyckelord
        }
        public double M
        {
            get { return sum / nSum; }
            private set { } // Tomma brackets eftersom set inte gör något
        }
    }
}
