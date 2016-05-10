using System;
using System.Collections.Generic;

namespace ClassLibrary
{
    public class MyEventArgs : EventArgs
    {
        public object MyObject { get; set; }
    }

    public class MyErrorEventArgs : EventArgs
    {
        public string MyTitle { get; set; }
        public string MyText { get; set; }
    }

    public class DiverEventArgs : EventArgs
    {
        public List<Dive> ListDive = new List<Dive>();
        public string Name { get; set; }
        public string Country { get; set; }
        public int Age { get; set; }
        public int DiverId { get; set; }
        public int Rank { get; set; }
        public float CompetitionPoints { get; set; }
        public string Gender { get; set; }

        public override string ToString()
        {
            return $"{Name}, {Country}, {Age}, {Gender}.";
        }
    }

    public class DiverListEventArgs : EventArgs
    {
        public List<Diver> DiverList = new List<Diver>();
    }

    public class CompetitionEventArgs : EventArgs
    {
        public string Date;
        public List<Diver> ListDiver = new List<Diver>();
        public List<Referee> ListReferee = new List<Referee>();
        public string Location;
        public string Name;
        public int Rounds;
        public string Type;
    }
}