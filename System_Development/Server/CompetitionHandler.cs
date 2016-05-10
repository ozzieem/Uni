using ClassLibrary;
using NLog.Time;
using System.Collections.Generic;

namespace Server
{
    public static class CompetitionHandler
    {
        public static Competition ActiveCompetition;
        public static Dive CurrentDive = new Dive();    // Överför färdigbedömt hopp till databasen

        public static void SendAssessmentsToDatabase()
        {
            foreach (var assessment in CurrentDive.Assessments)
            {
                DbHandler.InsertAssessment(assessment);
            }
        }

        public static void SendCurrentDiveToDatabaseAndUpdateActiveCompetition()
        {
            CurrentDive.CalculateTotalPoints();
            UpdateCurrentDiveInActiveCompetition();
            SendAssessmentsToDatabase();
            DbHandler.UpdateDiveTotalPoints(CurrentDive);
        }

        public static void UpdateCurrentDiveInActiveCompetition()
        {
            for (int i = 0; i < ActiveCompetition.ListDiver.Count; i++)
            {
                for (int j = 0; j < ActiveCompetition.ListDiver[i].ListDive.Count; j++)
                {
                    if (ActiveCompetition.ListDiver[i].ListDive[j].Id == CurrentDive.Id)
                    {
                        ActiveCompetition.ListDiver[i].ListDive[j] = CurrentDive;
                        break;
                    }
                }
            }
        }

        public static void SetCompetition(Competition competition)
        {
            ActiveCompetition = competition;
        }

        public static void SetCurrentDive(Dive dive)
        {
            CurrentDive = dive;
        }

        public static bool CurrentDiveComplete()
        {
            return CurrentDive.Assessments.Count == ActiveCompetition.ListReferee.Count;
        }

        public static void AddAssessment(Assessment assessment)
        {
            assessment.CompetitionId = ActiveCompetition.Id;
            assessment.DiveId = CurrentDive.Id;
            CurrentDive.Assessments.Add(assessment);
        }

        public static List<Dive> GetAllDives()
        {
            var tDives = new List<Dive>();

            foreach (var diver in ActiveCompetition.ListDiver)
            {
                tDives.AddRange(diver.ListDive);
            }

            return tDives;
        }
    }
}