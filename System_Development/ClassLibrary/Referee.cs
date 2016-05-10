using System;
using System.Threading;

namespace ClassLibrary
{
    /// <summary>
    ///     Denna klass ärver alla sina variabler från Person och BaseObject.
    ///     Ska bara vara för att kategorisera alla domare som domare.
    /// </summary>
    [Serializable]
    public class Referee : Person
    {
        public int OldDive = -1;  //TEMPPP

        public Referee()
        {
        }

        public Referee(int id, string name, string country) : base(id, name, country)
        {
        }

        public Referee(int id, string name, string country, string accountType)
            : base(id, name, country, accountType)
        {
        }

        public Referee(string name, string country, string password, string username)
            : base(name, country)
        {
            Password = password;
            Username = username;
        }

        public Dive ReceiveDive()
        {
            while (ClientNetworkHandler.MainTcpClient.Connected)
            {
                var dive = ClientNetworkHandler.SendAndReceive("GCD;" + Id);
                var tDive = dive as Dive;
                if (tDive != null && tDive.Id != -1)
                {
                    if (tDive.Id != OldDive)
                    {
                        //AssessDive(dive as Dive);
                        OldDive = tDive.Id;
                        return tDive;
                    }
                }
                //else
                //{
                //    break;
                //}
                //Console.WriteLine("Awaiting dive...");
                Thread.Sleep(3000);
            }
            return null;
        }

        public Score AddRefereeScore()
        {
            while (true)
            {
                var value = Convert.ToSingle(Console.ReadLine());

                try
                {
                    if (value < 0 || value > 10 || (value * 10) % 5 != 0)
                    {
                        throw new Exception("Fel inmatning. Försök igen!");
                    }
                    var score = new Score(value);
                    return score;
                }
                catch (FormatException formatException)
                {
                    Console.WriteLine(formatException.Message);
                }
                catch (Exception e)
                {
                    Console.WriteLine(e.Message);
                }
            }
        }

        public void AssessDive(Score score, Dive dive)
        {
            //Console.WriteLine($"Give points to dive {dive.DiveCode} by {dive.DiverId}");
            //var score = AddRefereeScore();
            var assessment = new Assessment(score, dive, this);
            var str = ClientNetworkHandler.SendAndReceive(assessment);
            //Console.WriteLine(str);
        }
    }
}