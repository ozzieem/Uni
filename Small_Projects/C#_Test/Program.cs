using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace C_sharp_test
{
    class Program
    {
        static void Main(string[] args)
        {
            Mean m1 = new Mean();   // Referensvariabel är ett Mean-objekt 
            Mean m2 = new Mean();

            m1.add(100);
            m1.add(200);
            m1.add(300);
            m2.add(200);
            m2.add(1600);

            Console.WriteLine("m1=" + m1.GetMean());
            Mean m3 = new Mean(999, 3);
            Mean m4 = m1;
            Console.WriteLine("n=" + m3.NSum);
            m3.NSum = m3.NSum + 1;
            
            //m3.M = 100; 
            /* Kan inte göras då det inte finns någon set-metod 
            för M och den är private */


        }
    }
}
