using ClassLibrary;
using NUnit.Framework;
using System.Linq;

namespace UnitTestClasses
{
    [TestFixture]
    public class ScoreTest
    {
        [Test]
        public void TestCalculateTotalPoints()
        {
            var dive = new Dive(1, new DiveType(1, "100a", 1.5f), -1, 4, 3);
            Assert.AreEqual(dive.TotalPoints.Value, -1.0f);

            for (var i = 0; i < 5; i++)
            {
                var assessment = new Assessment(i, new Score(5.0f + i), dive, new Referee());
                dive.Assessments.Add(assessment);
            }

            Assert.IsNotEmpty(dive.Assessments);
            Assert.AreEqual(dive.Assessments.Count, 5);

            var scores = dive.Assessments.Select(assessment => assessment.Point).ToList();

            dive.TotalPoints.CalculateCompleteScore(scores, dive.Type.Difficulty);

            /* Points in assessment-list
             5, 6, 7, 8, 9 -> lowest(5) and highest(9) gets removed. Left: 6, 7, 8.
             Totalpoints = 6 + 7 + 8 * 1.5f = 31.5 points
             */
            Assert.AreEqual(dive.TotalPoints.Value, 31.5f);
        }
    }
}