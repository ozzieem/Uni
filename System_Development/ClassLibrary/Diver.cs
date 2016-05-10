using System;
using System.Collections.Generic;
using System.Text;

namespace ClassLibrary
{
    /// <summary>
    ///     Klassen representerar en dykare i en tävling. Ärver från Person och BaseObject.
    /// </summary>
    [Serializable]
    public class Diver : Person
    {
        public List<Dive> ListDive = new List<Dive>();
        public int Age { get; set; }
        public int DiverId { get; set; }
        public string Gender { get; set; }
        public int Rank { get; set; }
        private Score _competitionScore;

        public Score CompetitionScore
        {
            get { return _competitionScore = SummarizeDivePoints(); }
            set { _competitionScore = value; }
        }

        /// <summary>
        ///     Lägger till ett hopp för dykaren
        /// </summary>
        /// <param name="dive"></param>
        public void AddDive(Dive dive)
        {
            ListDive.Add(dive);
        }

        public void AddDiveList(List<Dive> diveList)
        {
            ListDive = diveList;
        }

        /// <summary>
        ///     Summera alla poäng från alla hopp
        /// </summary>
        public Score SummarizeDivePoints()
        {
            var points = new Score(0);
            foreach (var dive in ListDive)
            {
                if (dive.TotalPoints.Value != -1)
                    points.Value += dive.TotalPoints.Value;
            }
            return points;
        }

        /// <summary>
        ///     Skriver ut information om ett Diver-objekt
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            var str = new StringBuilder();
            str.Append(DiverId != -1
                ? $"{DiverId} {Name} {Country} {Age} {Gender}"
                : "Could not retrieve diver information.");

            return str.ToString();
        }

        #region Konstruktorer

        public Diver()
        {
            Age = -1;
            DiverId = -1;
            Rank = -1;
            Gender = "";
            ListDive = new List<Dive>();
            CompetitionScore = new Score();
        }

        public Diver(string name, string country, int age, string gender, int diverId)
            : base(name, country)
        {
            Age = age;
            Gender = gender;
            DiverId = diverId;
            CompetitionScore = new Score();
        }

        public Diver(int id, string name, string country, int age, string gender, int diverId)
            : base(id, name, country)
        {
            Age = age;
            Gender = gender;
            DiverId = diverId;
            CompetitionScore = new Score();
        }

        #endregion Konstruktorer
    }
}