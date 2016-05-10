using ClassLibrary;
using NUnit.Framework;
using Server;
using System;
using System.Linq;

namespace UnitTestClasses
{
    [TestFixture]
    public class DatabaseTest
    {
        [Test]
        public void TestGetReferee()
        {
            var referees = DbHandler.GetReferees();
            foreach (var referee in referees)
            {
                Assert.AreEqual("referee", referee.AccountType);
            }
        }

        [Test]
        public void TestGetCompetition()
        {
            var competition = DbHandler.GetCompetition(49);

            Assert.AreEqual("Flydiving Cup", competition.Name);
            Assert.AreEqual("Moskva", competition.Location);
            Assert.AreEqual(4, competition.Rounds);

            var diver = DbHandler.GetDiver(3);
            var dive = DbHandler.GetDive(113);
            var referees = DbHandler.GetAssignedRefereesByCompetition(49);

            foreach (var tDiver in competition.ListDiver)
            {
                if (diver == tDiver)
                {
                    Assert.AreEqual(diver.Name, tDiver.Name);
                    Assert.AreEqual(diver.ListDive, tDiver.ListDive);
                }
                foreach (var tDive in tDiver.ListDive.Where(tDive => dive == tDive))
                {
                    Assert.AreEqual(dive.Type.Code, tDive.Type.Code);
                    Assert.AreNotEqual(34, tDive.DiverId);
                }
            }

            var referee1 = new Referee(4, "Katja", "Ryssland");
            var referee2 = new Referee(10, "Kalle", "Finland");

            foreach (var judge in referees)
            {
                if (judge != referee1 && judge != referee2) continue;
                Assert.AreEqual(judge.Name, referee1.Name);
                Assert.AreEqual(judge.Country, referee2.Country);
            }
        }

        [Test]
        public void TestGetDive()
        {
            var dive = DbHandler.GetDive(111);

            Assert.AreEqual(2, dive.DiverId);
            Assert.AreEqual("010c", dive.Type.Code);
            Assert.AreEqual(-1.0f, dive.TotalPoints.Value);
            Assert.False(dive.Name == "3332");
            Assert.False(Math.Abs(dive.TotalPoints.Value) < 0);
        }

        [Test]
        public void TestGetDiver()
        {
            var diver = DbHandler.GetDiver(1);

            Assert.AreEqual("Hannah", diver.Name);
            Assert.AreEqual(23, diver.Age);
            Assert.AreEqual(0, diver.Rank);
            Assert.AreEqual("Sverige", diver.Country);
            Assert.AreEqual("F", diver.Gender);
            Assert.False(diver.DiverId == 2);
            Assert.False(diver.Name == "Gurt");
        }

        [Test]
        public void TestGetDiveType()
        {
            var diveType = new DiveType(1, "100a", 1.0f);
            var testType = DbHandler.GetDiveType("1");

            Assert.AreEqual(diveType.Difficulty, testType.Difficulty);
            Assert.AreEqual(diveType.Code, testType.Code);
            Assert.AreEqual(diveType.Id, testType.Id);
            Assert.AreNotEqual("200c", testType.Code);
        }

        [Test]
        public void TestLogin()
        {
            var admin = new Admin(19, "Kjellbo", "Danmark");
            var obj = DbHandler.LoginCheck("user_Kjellbo1", "0815");
            var tAdmin = obj as Admin;
            if (tAdmin != null)
            {
                Assert.AreEqual(admin.Name, tAdmin.Name);
                Assert.AreEqual(admin.Country, tAdmin.Country);
            }

            var referee = new Referee(17, "Kjell", "Sverige");
            obj = DbHandler.LoginCheck("user_Kjell1", "0815");
            var tReferee = obj as Referee;
            if (tReferee == null) return;
            Assert.AreEqual(referee.Name, tReferee.Name);
            Assert.AreEqual(referee.Country, tReferee.Country);
        }
    }
}