using System;

namespace ClassLibrary
{
    [Serializable]
    public class Assessment : BaseObject
    {
        public Score Point;
        public int DiveId;
        public int RefereeId;
        public int CompetitionId;

        public Assessment()
        {
            Point = new Score();
            DiveId = -1;
            RefereeId = -1;
            CompetitionId = -1;
        }

        public Assessment(int id, Score score, Dive dive, Referee referee) : base(id)
        {
            Point = score;
            DiveId = dive.Id;
            RefereeId = referee.Id;
        }

        public Assessment(int id, float scoreValue, int diveId, int refereeId, int competitionId) : base(id)
        {
            Point = new Score(scoreValue);
            DiveId = diveId;
            RefereeId = refereeId;
            CompetitionId = competitionId;
        }

        public Assessment(Score score, Dive dive, Referee referee)
        {
            this.Point = score;
            this.DiveId = dive.Id;
            this.RefereeId = referee.Id;
        }
    }
}