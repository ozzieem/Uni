using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;

namespace ClassLibrary
{
    [Serializable]
    public class Admin : Person
    {
        public Dive CurrentDive = new Dive();

        public Admin()
        {
        }

        public Admin(int id, string name, string country, string accountType) : base(id, name, country, accountType)
        {
        }

        public Admin(int id, string name, string country) : base(id, name, country)
        {
        }

        public void AddCompetition(Competition competition)
        {
            SendToServer(competition);
        }

        public void AddDiver(Diver diver)
        {
            SendToServer(diver);
        }

        public void AddDiverList(List<Diver> diverList)
        {
            SendToServer(diverList);
        }

        public void AddReferee(Referee referee)
        {
            referee.Password = Hasher.GenerateHash(referee.Password);
            SendToServer(referee);
        }

        public void StartCompetition(int id)
        {
            var runningCompetition = true;
            while (ClientNetworkHandler.MainTcpClient.Connected && runningCompetition)
            {
                Console.Clear();
                Console.WriteLine("Dives:");
                var tDives = SendToServer($"SC;{id}");
                var diveList = tDives as List<Dive>;
                diveList?.Sort((x, y) => x.Order.CompareTo(y.Order));
                if (diveList != null)
                    foreach (var dive in diveList)
                    {
                        Console.WriteLine(dive);
                    }
                SendOutDives(diveList);
                runningCompetition = false;
            }
        }

        private void SendOutDives(object tDives)
        {
            var divesCount = ((List<Dive>)tDives).Count;
            for (var index = 0; index < divesCount; index++)
            {
                var dive = ((List<Dive>)tDives)[index];
                Console.WriteLine("Press enter to begin dive {0}", dive.Id);
                Console.ReadLine();
                var msg = SendToServer(dive);
                Console.WriteLine(msg);
                while (true)
                {
                    var statusMessage = SendToServer("IsCurrentDiveDone");
                    if (statusMessage != null && CurrentDive != (Dive)statusMessage)
                    {
                        CurrentDive = (Dive)statusMessage;
                        if (CurrentDive.Assessments.Count == 1)
                        {
                            break;
                        }
                    }

                    Thread.Sleep(3000);
                }
            }

            var completemsg = SendToServer("CompetitionComplete");
            Console.WriteLine(completemsg);
        }

        public List<string> GetActiveCompetitionDivers()
        {
            var leaderList = new List<string>();
            var tempList = SendToServer("GetLeaderList") as List<Diver>;
            tempList?.Sort((y, x) => x.CompetitionScore.Value.CompareTo(y.CompetitionScore.Value));
            foreach (var diver in tempList)
            {
                leaderList.Add($"Namn: {diver.Name} ID: {diver.DiverId} Poäng: {diver.CompetitionScore.Value}");
            }
            return leaderList;
        }

        public object SendToServer(object obj)
        {
            return ClientNetworkHandler.SendAndReceive(obj);
        }
    }
}