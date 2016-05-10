using ClassLibrary;
using NUnit.Framework;
using Server;
using System.Collections.Generic;

namespace UnitTestClasses
{
    /// <summary>
    ///     Summary description for CompetitionTest
    /// </summary>
    [TestFixture]
    public class CompetitionTest
    {
        [Test]
        public void TestGetAllDives()
        {
            CompetitionHandler.ActiveCompetition = DbHandler.StartCompetition(56);
            var dives = DbHandler.GetAllDiveByCompetitionId(56);
            var handlerDives = CompetitionHandler.GetAllDives();

            foreach (var dive in dives)
            {
                foreach (var hDive in handlerDives)
                {
                    if (dive.Id != hDive.Id) continue;
                    Assert.AreEqual(dive.DiverId, hDive.DiverId);
                    Assert.AreEqual(dive.Name, hDive.Name);
                    Assert.AreEqual(dive.Id, hDive.Id);
                    Assert.AreEqual(dive.Type.Difficulty, hDive.Type.Difficulty);
                    Assert.AreEqual(dive.Type.Code, hDive.Type.Code);
                }
            }
        }

        [Test]
        public void AddDiverToCompetition()
        {
            var competitionObject = new Competition(1, "Örebro Mästerskapen", "20160217", "Örebro", "DM", 6);
            var diver = new Diver(4, "Klas", "Uganda", 59, "Man", 3);

            competitionObject.AddDiver(diver);
            Assert.AreEqual(1, competitionObject.ListDiver.Count);

            competitionObject.AddDiver(diver);
            Assert.AreEqual(1, competitionObject.ListDiver.Count);

            var diver2 = new Diver(7, "Stefan", "Uganda", 14, "Man", 6);

            competitionObject.AddDiver(diver2);
            Assert.AreEqual(2, competitionObject.ListDiver.Count);

            var diver3 = new Diver();

            competitionObject.AddDiver(diver3);
            Assert.AreEqual(2, competitionObject.ListDiver.Count);
        }

        [Test]
        public void CreateBasicCompetition()
        {
            var competitionObject = new Competition(1, "Örebro Mästerskapen", "20160217", "Örebro", "DM", 6);

            Assert.AreEqual("Örebro Mästerskapen", competitionObject.Name);
            Assert.AreEqual("20160217", competitionObject.Date);
            Assert.AreEqual(6, competitionObject.Rounds);
        }

        [Test]
        public void TestFullCompetition() //Testar en fullständig tävling
        {
            var competitionObject = new Competition(1, "Örebro Mästerskapen", "20160217", "Örebro", "DM", 3);

            var diver = new Diver(4, "Klas", "Uganda", 59, "Man", 3);
            var diver2 = new Diver(5, "Susanna", "Sweden", 27, "Kvinna", 12);
            var diver3 = new Diver(2, "Klas-Göran", "Sweden", 22, "Man", 321);
            competitionObject.AddDiver(diver);
            competitionObject.AddDiver(diver2);
            competitionObject.AddDiver(diver3);

            Assert.AreEqual(3, competitionObject.ListDiver.Count);

            var dive1 = new Dive(1, 3.6f, 0, 1, diver.DiverId);
            var dive2 = new Dive(2, 6.2f, 0, 2, diver.DiverId);
            var dive3 = new Dive(3, 1.2f, 0, 3, diver.DiverId);
            diver.AddDive(dive1);
            diver.AddDive(dive2);
            diver.AddDive(dive3);

            var dive4 = new Dive(4, 2.6f, 0, 1, diver2.DiverId);
            var dive5 = new Dive(5, 3.7f, 0, 2, diver2.DiverId);
            var dive6 = new Dive(6, 9.2f, 0, 3, diver2.DiverId);
            diver2.AddDive(dive4);
            diver2.AddDive(dive5);
            diver2.AddDive(dive6);

            var dive7 = new Dive(7, 4.9f, 0, 1, diver3.DiverId);
            var dive8 = new Dive(8, 6.2f, 0, 2, diver3.DiverId);
            var dive9 = new Dive(9, 1.2f, 0, 3, diver3.DiverId);
            diver3.AddDive(dive7);
            diver3.AddDive(dive8);
            diver3.AddDive(dive9);

            if (competitionObject.CheckIfSameAmountOfDives())
            {
                var allRefScores = new List<Score>();
                var score1 = new Score(5.5f);
                var score2 = new Score(2.5f);
                var score3 = new Score(8.0f);
                var score4 = new Score(5.0f);
                var score5 = new Score(2.5f);
                allRefScores.Add(score1);
                allRefScores.Add(score2);
                allRefScores.Add(score3);
                allRefScores.Add(score4);
                allRefScores.Add(score5);
                for (var i = 0; i < competitionObject.Rounds; i++)
                {
                    foreach (var contestant in competitionObject.ListDiver)
                    {
                        contestant.ListDive[i].TotalPoints.CalculateCompleteScore(allRefScores, contestant.ListDive[i].Type.Difficulty);
                    }
                }
                foreach (var contestant in competitionObject.ListDiver)
                {
                    contestant.SummarizeDivePoints();
                }
                Assert.AreEqual("Susanna", competitionObject.GetWinner());
            }
        }
    }
}