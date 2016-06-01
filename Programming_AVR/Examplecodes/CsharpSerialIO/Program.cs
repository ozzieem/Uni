using System;
using System.Collections.Generic;
using System.Text;
using System.IO.Ports;

namespace SerialApp2
{
    class Program
    {
        SerialPort sio = null;

        /// <summary>
        /// Konstruktor, Öppnar en COM-port
        /// </summary>
        Program()
        {
            sio = new SerialPort("COM1", 9600, Parity.None, 8, StopBits.Two);

            //Kopplar egendefinierade metoden sio_DataReceived till HÄNDELSEN DataReceived
            sio.DataReceived +=new SerialDataReceivedEventHandler(sio_DataReceived);

            try 
	        {
                sio.Open();
	        }
	        catch (Exception e)
	        {
                Console.WriteLine(e.Message);
		        //throw;
	        };
        }

        /// <summary>
        /// Händelsemetod / Call back-funktion
        /// Svarar på händelsen att ett nytt tecken har mottagits
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void sio_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            char c;
            while (sio.BytesToRead > 0)
            {
                c = (char) sio.ReadChar();
                Console.Write(c);
            }
        }

        static void Main(string[] args)
        {
            Program prgm = new Program();

            while (true)
               {
                    
               }
        }
    }
}
