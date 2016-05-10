using System;
using System.Collections.Generic;
using System.Data.Entity.ModelConfiguration.Conventions;
using System.Text;

namespace ClassLibrary
{
    /// <summary>
    ///     Klassen representerar ett hopp.
    ///     Variabeln _order ska sättas vid konstruktion av tävlingen.
    /// </summary>
    [Serializable]
    public class Dive : BaseObject
    {
        public DiveType Type = new DiveType();

        public Score TotalPoints { get; set; }
        public int Order { get; set; }
        public int DiverId { get; set; }
        public int CompetitionId { get; set; }
        public List<Assessment> Assessments = new List<Assessment>();
        public string DiveCode => Type.Code;
        private string _name;

        public string Name
        {
            get { return _name; }
            set { _name = value; }
        }

        public string CreateName()
        {
            return "";
        }

        public override string ToString()
        {
            var str = new StringBuilder();
            str.Append(
                $"Hopp nr: {Order}, Hoppkod: {DiveCode}");

            return str.ToString();
        }

        public void CalculateTotalPoints()
        {
            var scores = new List<Score>();
            foreach (var assessment in Assessments)
            {
                scores.Add(assessment.Point);
            }
            TotalPoints.CalculateCompleteScore(scores, Type.Difficulty);
        }

        #region Konstruktorer

        public Dive()
        {
            TotalPoints = new Score();
            Order = -1;
            Name = "";
        }

        public Dive(int id, DiveType diveType, float totalPoints, int order, int diverId)
            : base(id)
        {
            Assessments = new List<Assessment>();
            DiverId = diverId;
            Type = diveType;
            TotalPoints = new Score(totalPoints);
            Order = order;
            //_name = Name; //Skall anropa en funktion som genererar namnet på hoppet från koden.
        }

        public Dive(int id, float totalPoints, int order, int diverId, int competitionId, DiveType diveType)
            : base(id)
        {
            DiverId = diverId;
            Type = diveType;
            TotalPoints = new Score(totalPoints);
            Order = order;
            CompetitionId = competitionId;
            Assessments = new List<Assessment>();
            //_name = Name; //Skall anropa en funktion som genererar namnet på hoppet från koden.
        }

        public Dive(int id, float difficulty, float totalPoints, int order, int diverId)
            : base(id)
        {
            DiverId = diverId;
            Type.Difficulty = difficulty;
            TotalPoints = new Score(totalPoints);
            Order = order;
            //_name = Name; //Skall anropa en funktion som genererar namnet på hoppet från koden.
        }

        public Dive(string diveCode, int diverid)
        {
            Order = -1;
            TotalPoints = new Score();
            Name = "";
            DiverId = diverid;
            Type.Code = diveCode;
        }

        #endregion Konstruktorer
    }
}