using ClassLibrary;
using NUnit.Framework;
using System;
using System.Collections.Generic;

namespace UnitTestClasses
{
    /// <summary>
    ///     Summary description for DiverScoreTest
    /// </summary>
    [TestFixture]
    public class DiverScoreTest
    {
        [Test]
        public void TestDiverTotalScore()
        {
            var diver = new Diver(1, "Fred", "S", 23, "M", 23);
            Assert.IsTrue(diver.CompetitionScore.Value == 0f);

            var dives = new List<Dive>
            {
                new Dive(1, 1.5f, 5.0f, 1, 23),
                new Dive(2, 1.5f, 6.0f, 2, 23),
                new Dive(3, 1.5f, 7.0f, 3, 23),
                new Dive(4, 1.5f, 8.0f, 4, 23)
            };

            diver.AddDiveList(dives);
            Assert.AreEqual(diver.SummarizeDivePoints().Value, diver.CompetitionScore.Value);

            Assert.AreEqual(26f, diver.CompetitionScore.Value);
        }

        [Test]
        public void TestCalculateCompetitionPoints()
        {
            var diver = new Diver(3, "Johan", "Sweden", 23, "Man", 365);
            var dive1 = new Dive(1, 3.6f, 0, 1, diver.DiverId);
            var dive2 = new Dive(1, 6.2f, 0, 2, diver.DiverId);
            var dive3 = new Dive(1, 1.2f, 0, 3, diver.DiverId);
            var dive4 = new Dive(1, 3.0f, 0, 4, diver.DiverId);
            var dive5 = new Dive(1, 4.7f, 0, 5, diver.DiverId);
            diver.AddDive(dive1);
            diver.AddDive(dive2);
            diver.AddDive(dive3);
            diver.AddDive(dive4);
            diver.AddDive(dive5);

            Assert.AreEqual(5, diver.ListDive.Count);

            var score1 = new Score(5.5f);
            var score2 = new Score(2.5f);
            var score3 = new Score(8.0f);
            var score4 = new Score(5.0f);
            var score5 = new Score(2.5f);

            var allRefScores = new List<Score> { score1, score2, score3, score4, score5 };

            diver.ListDive[0].TotalPoints.CalculateCompleteScore(allRefScores, diver.ListDive[0].Type.Difficulty);
            diver.ListDive[1].TotalPoints.CalculateCompleteScore(allRefScores, diver.ListDive[1].Type.Difficulty);
            diver.ListDive[2].TotalPoints.CalculateCompleteScore(allRefScores, diver.ListDive[2].Type.Difficulty);
            diver.ListDive[3].TotalPoints.CalculateCompleteScore(allRefScores, diver.ListDive[3].Type.Difficulty);
            diver.ListDive[4].TotalPoints.CalculateCompleteScore(allRefScores, diver.ListDive[4].Type.Difficulty);

            diver.SummarizeDivePoints();

            //Assert.AreEqual(243.1, Math.Round(diver._competitionScore, 2));
        }

        [Test]
        public void TestCreateDiver()
        {
            var diver = new Diver(3, "Johan", "Sweden", 23, "Man", 365);
            var dive1 = new Dive(1, 3.6f, 0, 1, diver.DiverId);
            var dive2 = new Dive(1, 6.2f, 0, 2, diver.DiverId);
            var dive3 = new Dive(1, 1.2f, 0, 3, diver.DiverId);
            var dive4 = new Dive(1, 3.0f, 0, 4, diver.DiverId);
            var dive5 = new Dive(1, 4.7f, 0, 5, diver.DiverId);
            diver.AddDive(dive1);
            diver.AddDive(dive2);
            diver.AddDive(dive3);
            diver.AddDive(dive4);
            diver.AddDive(dive5);

            Assert.AreEqual(5, diver.ListDive.Count);
        }
    }
}