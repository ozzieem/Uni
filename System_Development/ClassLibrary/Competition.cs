using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace ClassLibrary
{
    /// <summary>
    ///     Klassen skall hantera skapandet av och även hämtningen av en tävling.
    ///     Tanken är att denna klass skall vara länkad med Diver-klassen och Referee-klassen.
    ///     Denna klass skall kunna hanteras av någon administratörsmeny
    /// </summary>
    [Serializable]
    public class Competition : BaseObject
    {
        public string Date;
        public List<Diver> ListDiver;
        public List<Referee> ListReferee;
        public string Location;
        public string Name;
        public int Rounds;
        public string Type;

        public Competition()
        {
            ListDiver = new List<Diver>();
            ListReferee = new List<Referee>();
            Name = Date = Location = Type = "";
            Rounds = -1;
        }

        public Competition(int id, string name, string date, string location, string type, int rounds)
            : base(id)
        {
            ListDiver = new List<Diver>();
            ListReferee = new List<Referee>();
            Name = name;
            Date = date;
            Location = location;
            Type = type;
            Rounds = rounds;
        }

        public Competition(string name, string date, string location, string type, int rounds)
        {
            ListDiver = new List<Diver>();
            ListReferee = new List<Referee>();
            Name = name;
            Date = date;
            Location = location;
            Type = type;
            Rounds = rounds;
        }

        /// <summary>
        ///     Tillagd funktion för att checka att en hoppare har fullständig information
        /// </summary>
        /// <param name="diver"></param>
        /// <returns></returns>
        public static bool CheckCompleteDiver(Diver diver)
        {
            if (diver.Age == -1)
                return false;
            if (diver.DiverId == -1)
                return false;
            if (diver.Gender == "")
                return false;
            if (diver.Name == "")
                return false;
            if (diver.Country == "")
                return false;
            if (diver.Id == -1)
                return false;
            return true;
        }

        /// <summary>
        ///     Kollar om det finns en diver i listan, annars läggs den till
        ///     Kontrollerar så inga tomma objekt läggs till
        /// </summary>
        /// <param name="diver"></param>
        public void AddDiver(Diver diver)
        {
            var contains = false;

            if (CheckCompleteDiver(diver))
            {
                foreach (var dvr in ListDiver.Where(dvr => diver == dvr))
                {
                    contains = true;
                }

                if (contains)
                {
                    Console.Write("Diver is already in list!");
                }
                else
                {
                    ListDiver.Add(diver);
                }
            }
        }

        public void AddDivetoDiver(Diver diver, Dive dive)
        {
            foreach (var dvr in ListDiver.Where(dvr => dvr == diver))
            {
                dvr.AddDive(dive);
                break;
            }
        }

        public void AddReferee(Referee referee)
        {
            ListReferee.Add(referee);
        }

        /// <summary>
        ///     Kontrollerar att samtliga tillagda hoppare har samma mängd hopp tillagda
        /// </summary>
        /// <returns></returns>
        public bool CheckIfSameAmountOfDives()
        {
            foreach (var diver in ListDiver)
            {
                if (diver.ListDive.Count != Rounds)
                {
                    Console.WriteLine($"Diver: {diver.Name} does not have the correct amount of dives added.");
                    return false;
                }
            }
            return true;
        }

        public string GetWinner()
        {
            var winner = "";
            float points = 0;

            foreach (var contestant in ListDiver)
            {
                if (contestant.CompetitionScore.Value > points)
                {
                    winner = contestant.Name;
                    points = contestant.CompetitionScore.Value;
                }
            }
            return winner;
        }

        public override string ToString()
        {
            var str = new StringBuilder();
            str.Append(Id != -1
                ? $"{Name}, {Location}, {Date}, \n{Type}, Omgångar: {Rounds}"
                : "Ingen aktiv tävling");

            return str.ToString();
        }

        public void SortDiveOrder()
        {
            var index = 1;
            var orderNr = 1;
            foreach (var diver in ListDiver)
            {
                foreach (var dive in diver.ListDive)
                {
                    dive.Order = orderNr;
                    orderNr += ListDiver.Count;
                }
                index++;
                orderNr = index;
            }
        }
    }
}