using ClassLibrary;
using NUnit.Framework;
using System.Collections.Generic;

namespace UnitTestClasses
{
    [TestFixture]
    public class DiverTest
    {
        [Test]
        public void TestAddDive()
        {
            var testDiver = new Diver();
            testDiver.AddDive(new Dive(1, (float)3.5, 0, 1, testDiver.DiverId));
            testDiver.AddDive(new Dive(2, (float)5.5, 0, 2, testDiver.DiverId));
            Assert.AreEqual(testDiver.ListDive[0].Type.Difficulty, 3.5);
            Assert.AreEqual(testDiver.ListDive[1].Type.Difficulty, 5.5);
        }

        [Test]
        public void TestAddDiveList()
        {
            var testDiver = new Diver();
            var testDiveList = new List<Dive>
            {
                new Dive(1, 3.3f, 0, 1, testDiver.DiverId),
                new Dive(2, 4.4f, 0, 2, testDiver.DiverId)
            };
            testDiver.AddDiveList(testDiveList);
            Assert.AreEqual(testDiver.ListDive[0].Type.Difficulty, 3.3f);
            Assert.AreNotEqual(testDiver.ListDive[1].Type.Difficulty, 5.5f);
        }
    }
}