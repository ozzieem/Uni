using ClassLibrary;
using MySql.Data.MySqlClient;
using NLog;
using System;
using System.Collections.Generic;
using System.Data.SqlClient;
using System.Reflection;

namespace Server
{
    /// <summary>
    ///     Klassen skall ta hand om kopplingen mellan databasen och server-programmet.
    ///     Ett gäng SQL-komandon kommer definieras så att all form av kommunikation kommer gå genom denna klass.
    /// </summary>
    public static class DbHandler
    {
        private const string ConnectionDetails =
            "server = 10.22.2.1;" +
            "user id = dbserver;" +
            "database = simhopp;";

        private static readonly Logger Logger = LogManager.GetCurrentClassLogger();

        /// <summary>
        ///     Kopplar upp mot databasen
        /// </summary>
        /// <returns></returns>
        public static MySqlConnection ConnectToDatabase()
        {
            MySqlConnection mySqlConnection;
            try
            {
                mySqlConnection = new MySqlConnection { ConnectionString = ConnectionDetails };
                Logger.Info("Opening connection to SQL server{0}", mySqlConnection.Database);
                mySqlConnection.Open();
            }
            catch (MySqlException mySqlException)
            {
                Logger.Error("MySqlException: " + mySqlException.Message);
                mySqlConnection = null;
            }
            catch (Exception exception)
            {
                Logger.Error("Exception: " + exception.Message);
                mySqlConnection = null;
            }
            return mySqlConnection;
        }

        public static List<Dive> GetAllDiveByCompetitionId(int id)
        {
            Logger.Trace($"Entering method {MethodBase.GetCurrentMethod().Name}");
            var sql = $"SELECT * FROM dive WHERE Competition = {id}";

            using (var sqlConnection = ConnectToDatabase())
            {
                var allDive = new List<Dive>();
                using (var sqlQuery = new MySqlCommand(sql, sqlConnection))
                {
                    Logger.Info("Running Query: \"{0}\"", sql);

                    var tableReader = sqlQuery.ExecuteReader();
                    while (tableReader.Read())
                    {
                        var dive = new Dive(
                            tableReader.GetInt32("ID"),
                            tableReader.GetFloat("Totalpoints"),
                            tableReader.GetInt32("diveOrder"),
                            tableReader.GetInt32("Diver"),
                            tableReader.GetInt32("Competition"),
                            GetDiveType(tableReader.GetString("Divetype"))
                            );
                        dive.Assessments = GetAssessments(dive.Id);
                        allDive.Add(dive);
                    }
                }

                Logger.Trace($"Leaving method {MethodBase.GetCurrentMethod().Name}");
                return allDive;
            }
        }

        public static List<Referee> GetAssignedRefereesByCompetition(int id)
        {
            Logger.Trace($"Entering method {MethodBase.GetCurrentMethod().Name}");
            var sql = "SELECT * FROM referee WHERE id IN " +
                      $"(SELECT referee FROM assignment WHERE Competition = {id})";

            using (var sqlConnection = ConnectToDatabase())
            {
                var tReferees = new List<Referee>();
                using (var sqlQuery = new MySqlCommand(sql, sqlConnection))
                {
                    Logger.Info("Running Query: \"{0}\"", sql);

                    var tableReader = sqlQuery.ExecuteReader();
                    while (tableReader.Read())
                    {
                        var tReferee = new Referee(
                            tableReader.GetInt32("ID"),
                            tableReader.GetString("Name"),
                            tableReader.GetString("Country"));
                        tReferees.Add(tReferee);
                    }
                }
                Logger.Trace($"Leaving method {MethodBase.GetCurrentMethod().Name}");
                return tReferees;
            }
        }

        public static List<Competition> GetAvailableCompetitions()
        {
            Logger.Trace($"Entering method {MethodBase.GetCurrentMethod().Name}");
            const string sql = "SELECT * FROM simhopp.competition WHERE id IN (SELECT Competition FROM simhopp.assignment " +
                               "WHERE State = 'Active' OR State = 'InActive')";

            using (var sqlConnection = ConnectToDatabase())
            {
                var idList = new List<int>();
                var competitionList = new List<Competition>();

                using (var sqlQuery = new MySqlCommand(sql, sqlConnection))
                {
                    Logger.Info("Running Query: \"{0}\"", sql);

                    var tableReader = sqlQuery.ExecuteReader();
                    while (tableReader.Read())
                    {
                        idList.Add(tableReader.GetInt32("ID"));
                    }
                }
                foreach (var id in idList)
                {
                    competitionList.Add(GetCompetition(id));
                }

                Logger.Trace($"Leaving method {MethodBase.GetCurrentMethod().Name}");
                Logger.Trace($"Leaving method {MethodBase.GetCurrentMethod().Name}");
                return competitionList;
            }
        }

        public static Competition GetCompetition(int id)
        {
            Logger.Trace($"Entering method {MethodBase.GetCurrentMethod().Name}");
            var sql = $"SELECT * FROM competition WHERE id = {id}";

            using (var sqlConnection = ConnectToDatabase())
            {
                var competition = new Competition();

                using (var sqlQuery = new MySqlCommand(sql, sqlConnection))
                {
                    Logger.Info("Running Query: \"{0}\"", sql);

                    var tableReader = sqlQuery.ExecuteReader();
                    while (tableReader.Read())
                    {
                        competition = new Competition(
                            tableReader.GetInt32("ID"),
                            tableReader.GetString("Name"),
                            tableReader.GetString("Date"),
                            tableReader.GetString("Location"),
                            tableReader.GetString("Type"),
                            tableReader.GetInt32("Rounds"));
                    }
                }
                // Hämtar divers och deras dives
                var dives = GetAllDiveByCompetitionId(competition.Id);
                var divers = GetDivers();
                foreach (var diver in divers)
                {
                    foreach (var dive in dives)
                    {
                        if (dive.DiverId == diver.Id && dive.CompetitionId == competition.Id)
                        {
                            diver.ListDive.Add(dive);
                        }
                    }
                    if (diver.ListDive.Count > 0)
                    {
                        competition.ListDiver.Add(diver);
                    }
                }
                // Hämtar judges
                competition.ListReferee = GetAssignedRefereesByCompetition(competition.Id);

                Logger.Trace($"Leaving method {MethodBase.GetCurrentMethod().Name}");
                return competition;
            }
        }

        public static int GetCompetitionId()
        {
            Logger.Trace($"Entering method {MethodBase.GetCurrentMethod().Name}");
            const string sql = "SELECT MAX(ID)FROM competition";

            using (var sqlConnection = ConnectToDatabase())
            {
                var competitionId = 0;
                using (var sqlQuery = new MySqlCommand(sql, sqlConnection))
                {
                    Logger.Info("Running Query: \"{0}\"", sql);

                    var tableReader = sqlQuery.ExecuteReader();
                    while (tableReader.Read())
                    {
                        competitionId = tableReader.GetInt32("MAX(ID)");
                    }
                }
                Logger.Trace($"Leaving method {MethodBase.GetCurrentMethod().Name}");
                return competitionId;
            }
        }

        public static List<Competition> GetCompetitions()
        {
            Logger.Trace($"Entering method {MethodBase.GetCurrentMethod().Name}");
            const string sql = "SELECT * FROM competition";

            using (var sqlConnection = ConnectToDatabase())
            {
                var idList = new List<int>();
                var competitionList = new List<Competition>();

                using (var sqlQuery = new MySqlCommand(sql, sqlConnection))
                {
                    Logger.Info("Running Query: \"{0}\"", sql);

                    var tableReader = sqlQuery.ExecuteReader();
                    while (tableReader.Read())
                    {
                        idList.Add(tableReader.GetInt32("ID"));
                    }
                }
                foreach (var id in idList)
                {
                    competitionList.Add(GetCompetition(id));
                }

                Logger.Trace($"Leaving method {MethodBase.GetCurrentMethod().Name}");
                Logger.Trace($"Leaving method {MethodBase.GetCurrentMethod().Name}");
                return competitionList;
            }
        }

        public static Dive GetDive(int id)
        {
            Logger.Trace($"Entering method {MethodBase.GetCurrentMethod().Name}");
            var sql = $"SELECT * FROM dive WHERE id = {id}";

            using (var sqlConnection = ConnectToDatabase())
            {
                var dive = new Dive();
                using (var sqlQuery = new MySqlCommand(sql, sqlConnection))
                {
                    Logger.Info("Running Query: \"{0}\"", sql);

                    var tableReader = sqlQuery.ExecuteReader();
                    while (tableReader.Read())
                    {
                        var tempDive = new Dive(
                            tableReader.GetInt32("ID"),
                            GetDiveType(tableReader.GetString("Divetype")),
                            tableReader.GetFloat("TotalPoints"),
                            tableReader.GetInt32("DiveOrder"),
                            tableReader.GetInt32("Diver"));
                        dive = tempDive;
                    }
                }
                dive.Assessments = GetAssessments(dive.Id);
                Logger.Trace($"Leaving method {MethodBase.GetCurrentMethod().Name}");
                return dive;
            }
        }

        public static Diver GetDiver(int diverId)
        {
            Logger.Trace($"Entering method {MethodBase.GetCurrentMethod().Name}");
            var sql = $"SELECT * FROM diver WHERE ID = {diverId}";

            using (var sqlConnection = ConnectToDatabase())
            {
                var diver = new Diver();
                using (var sqlQuery = new MySqlCommand(sql, sqlConnection))
                {
                    Logger.Info("Running Query: \"{0}\"", sql);

                    var tableReader = sqlQuery.ExecuteReader();
                    while (tableReader.Read())
                    {
                        var tempDiver = new Diver(
                            tableReader.GetInt32("Id"),
                            tableReader.GetString("Name"),
                            tableReader.GetString("Country"),
                            tableReader.GetInt32("Age"),
                            tableReader.GetString("Gender"),
                            tableReader.GetInt32("DiverId"));
                        diver = tempDiver;
                    }
                }
                Logger.Trace($"Leaving method {MethodBase.GetCurrentMethod().Name}");
                return diver;
            }
        }

        public static List<Diver> GetDivers()
        {
            Logger.Trace($"Entering method {MethodBase.GetCurrentMethod().Name}");
            const string sql = "SELECT * FROM diver";

            using (var sqlConnection = ConnectToDatabase())
            {
                var diverList = new List<Diver>();
                using (var sqlQuery = new MySqlCommand(sql, sqlConnection))
                {
                    Logger.Info("Running Query: \"{0}\"", sql);

                    var tableReader = sqlQuery.ExecuteReader();
                    while (tableReader.Read())
                    {
                        var diver = new Diver(
                            tableReader.GetInt32("ID"),
                            tableReader.GetString("Name"),
                            tableReader.GetString("Country"),
                            tableReader.GetInt32("Age"),
                            tableReader.GetString("Gender"),
                            tableReader.GetInt32("DiverId"));
                        diverList.Add(diver);
                    }
                }
                Logger.Trace($"Leaving method {MethodBase.GetCurrentMethod().Name}");
                return diverList;
            }
        }

        public static DiveType GetDiveType(string data)
        {
            Logger.Trace($"Entering method {MethodBase.GetCurrentMethod().Name}");

            int id;
            int.TryParse(data, out id);
            var sql = id > 0
                ? $"SELECT * FROM divetype WHERE ID = {id}"
                : $"SELECT * FROM divetype WHERE Code = '{data}'";

            using (var sqlConnection = ConnectToDatabase())
            {
                var diveType = new DiveType();
                using (var sqlQuery = new MySqlCommand(sql, sqlConnection))
                {
                    Logger.Info("Running Query: \"{0}\"", sql);

                    var tableReader = sqlQuery.ExecuteReader();
                    while (tableReader.Read())
                    {
                        var tDiveType = new DiveType(
                            tableReader.GetInt32("Id"),
                            tableReader.GetString("Code"),
                            tableReader.GetFloat("Difficulty"));
                        diveType = tDiveType;
                    }
                }
                Logger.Trace($"Leaving method {MethodBase.GetCurrentMethod().Name}");
                return diveType;
            }
        }

        public static List<DiveType> GetDiveTypes()
        {
            Logger.Trace($"Entering method {MethodBase.GetCurrentMethod().Name}");
            const string sql = "SELECT * FROM divetype";

            using (var sqlConnection = ConnectToDatabase())
            {
                var tDiveTypes = new List<DiveType>();
                using (var sqlQuery = new MySqlCommand(sql, sqlConnection))
                {
                    Logger.Info("Running Query: \"{0}\"", sql);

                    var tableReader = sqlQuery.ExecuteReader();
                    while (tableReader.Read())
                    {
                        var tDiveType = new DiveType(
                            tableReader.GetInt32("Id"),
                            tableReader.GetString("Code"),
                            tableReader.GetFloat("Difficulty"));
                        tDiveTypes.Add(tDiveType);
                    }
                }
                Logger.Trace($"Leaving method {MethodBase.GetCurrentMethod().Name}");
                return tDiveTypes;
            }
        }

        public static List<Referee> GetReferees()
        {
            Logger.Trace($"Entering method {MethodBase.GetCurrentMethod().Name}");
            const string sql = "SELECT * FROM referee";

            using (var sqlConnection = ConnectToDatabase())
            {
                var refereeList = new List<Referee>();

                using (var sqlQuery = new MySqlCommand(sql, sqlConnection))
                {
                    Logger.Info("Running Query: \"{0}\"", sql);

                    var tableReader = sqlQuery.ExecuteReader();
                    while (tableReader.Read())
                    {
                        var referee = new Referee(
                            tableReader.GetInt32("Id"),
                            tableReader.GetString("Name"),
                            tableReader.GetString("Country"),
                            tableReader.GetString("AccountType"));
                        refereeList.Add(referee);
                    }
                }
                Logger.Trace($"Leaving method {MethodBase.GetCurrentMethod().Name}");
                return refereeList;
            }
        }

        public static void InsertAllAssignment(Competition competition)
        {
            foreach (var referee in competition.ListReferee)
            {
                InsertAssignment(competition, referee);
            }
        }

        public static void InsertAllDives(Competition competition)
        {
            Logger.Trace($"Entering method {MethodBase.GetCurrentMethod().Name}");
            const string sql = "INSERT INTO dive (TotalPoints, diveOrder, Diver, Competition, Divetype) " +
                               "VALUES (@TotalPoints, @diveOrder, @Diver, @Competition, @DiveType)";

            using (var sqlConnection = ConnectToDatabase())
            {
                var result = 0;
                foreach (var diver in competition.ListDiver)
                {
                    foreach (var dive in diver.ListDive)
                    {
                        using (var sqlQuery = new MySqlCommand(sql, sqlConnection))
                        {
                            Logger.Info("Running Query: \"{0}\"", sql);

                            sqlQuery.Parameters.AddWithValue("@DiveType", GetDiveType(dive.Type.Code).Id);
                            sqlQuery.Parameters.AddWithValue("@TotalPoints", dive.TotalPoints.Value);
                            sqlQuery.Parameters.AddWithValue("@diveOrder", dive.Order);
                            sqlQuery.Parameters.AddWithValue("@Diver", diver.Id);
                            sqlQuery.Parameters.AddWithValue("@Competition", competition.Id);

                            result += sqlQuery.ExecuteNonQuery();
                        }
                    }
                }
                Logger.Info("{0} rows affected", result);
            }
            Logger.Trace($"Leaving method {MethodBase.GetCurrentMethod().Name}");
        }

        public static void InsertAssessment(Assessment assessment)
        {
            Logger.Trace($"Entering method {MethodBase.GetCurrentMethod().Name}");
            const string sql = "INSERT INTO assessment(Points, Dive, Referee, Competition) " +
                               "VALUES (@Points, @Dive, @Referee, @Competition)";

            using (var sqlConnection = ConnectToDatabase())
            {
                using (var sqlQuery = new MySqlCommand(sql, sqlConnection))
                {
                    Logger.Info("Running Query: \"{0}\"", sql);

                    sqlQuery.Parameters.AddWithValue("@Points", assessment.Point.Value);
                    sqlQuery.Parameters.AddWithValue("@Dive", assessment.DiveId);
                    sqlQuery.Parameters.AddWithValue("@Referee", assessment.RefereeId);
                    sqlQuery.Parameters.AddWithValue("@Competition", assessment.CompetitionId);

                    var result = sqlQuery.ExecuteNonQuery();
                    Logger.Info("{0} rows affected", result);
                }
                Logger.Trace($"Leaving method {MethodBase.GetCurrentMethod().Name}");
            }
        }

        public static void InsertAssignment(Competition competition, Referee referee)
        {
            Logger.Trace($"Entering method {MethodBase.GetCurrentMethod().Name}");
            const string sql = "INSERT INTO Assignment (Competition, Referee) " +
                               "VALUES (@competitionId, @refereeId)";

            using (var sqlConnection = ConnectToDatabase())
            {
                using (var sqlQuery = new MySqlCommand(sql, sqlConnection))
                {
                    Logger.Info("Running Query: \"{0}\"", sql);

                    sqlQuery.Parameters.AddWithValue("@competitionId", competition.Id);
                    sqlQuery.Parameters.AddWithValue("@refereeId", referee.Id);
                    var result = sqlQuery.ExecuteNonQuery();
                    Logger.Info("{0} rows affected", result);
                }
            }
            Logger.Trace($"Leaving method {MethodBase.GetCurrentMethod().Name}");
        }

        public static void InsertCompetition(Competition competition)
        {
            Logger.Trace($"Entering method {MethodBase.GetCurrentMethod().Name}");
            const string sql = "INSERT INTO competition (Name, Date, Location, Type, Rounds) " +
                               "VALUES (@Name, @Date, @Location, @Type, @Rounds)";

            using (var sqlConnection = ConnectToDatabase())
            {
                using (var sqlQuery = new MySqlCommand(sql, sqlConnection))
                {
                    Logger.Info("Running Query: \"{0}\"", sql);

                    sqlQuery.Parameters.AddWithValue("@Name", competition.Name);
                    sqlQuery.Parameters.AddWithValue("@Date", competition.Date);
                    sqlQuery.Parameters.AddWithValue("@Location", competition.Location);
                    sqlQuery.Parameters.AddWithValue("@Type", competition.Type);
                    sqlQuery.Parameters.AddWithValue("@Rounds", competition.Rounds);

                    var result = sqlQuery.ExecuteNonQuery();
                    Logger.Info("{0} rows affected", result);
                }
                competition.Id = GetCompetitionId();
                InsertAllAssignment(competition);
                InsertAllDives(competition);
            }
            Logger.Trace($"Leaving method {MethodBase.GetCurrentMethod().Name}");
        }

        public static void InsertDiver(Diver diver)
        {
            Logger.Trace($"Entering method {MethodBase.GetCurrentMethod().Name}");
            const string sql = "INSERT INTO diver (Name, Age, Worldrank, Country, Gender, DiverId) " +
                               "VALUES (@name, @age, @worldRank, @country, @gender, @diverId)";

            using (var sqlConnection = ConnectToDatabase())
            {
                using (var sqlQuery = new MySqlCommand(sql, sqlConnection))
                {
                    Logger.Info("Running Query: \"{0}\"", sql);

                    sqlQuery.Parameters.AddWithValue("@name", diver.Name);
                    sqlQuery.Parameters.AddWithValue("@age", diver.Age);
                    sqlQuery.Parameters.AddWithValue("@worldRank", diver.Rank);
                    sqlQuery.Parameters.AddWithValue("@country", diver.Country);
                    sqlQuery.Parameters.AddWithValue("@gender", diver.Gender);
                    sqlQuery.Parameters.AddWithValue("@diverId", diver.DiverId);

                    var result = sqlQuery.ExecuteNonQuery();
                    Logger.Info("{0} rows affected", result);
                }
            }
            Logger.Trace($"Leaving method {MethodBase.GetCurrentMethod().Name}");
        }

        public static void InsertReferee(Referee referee)
        {
            Logger.Trace($"Entering method {MethodBase.GetCurrentMethod().Name}");
            const string sql = "INSERT INTO User (Name, Country, Loginname, password, Accounttype) " +
                               "VALUES (@Name, @Country, @Loginname, @password, @Accounttype)";

            using (var sqlConnection = ConnectToDatabase())
            {
                using (var sqlQuery = new MySqlCommand(sql, sqlConnection))
                {
                    Logger.Info("Running Query: \"{0}\"", sql);

                    sqlQuery.Parameters.AddWithValue("@Name", referee.Name);
                    sqlQuery.Parameters.AddWithValue("@Country", referee.Country);
                    sqlQuery.Parameters.AddWithValue("@Loginname", referee.Username);
                    sqlQuery.Parameters.AddWithValue("@password", referee.Password);
                    sqlQuery.Parameters.AddWithValue("@Accounttype", "referee");

                    var result = sqlQuery.ExecuteNonQuery();
                    Logger.Info("{0} rows affected", result);
                }
            }
            Logger.Trace($"Leaving method {MethodBase.GetCurrentMethod().Name}");
        }

        public static object LoginCheck(string userName, string password)
        {
            Logger.Trace($"Entering method {MethodBase.GetCurrentMethod().Name}");
            Logger.Info($"Validating user with username {userName} and password {password}");
            var sql = $"SELECT * FROM User WHERE loginName = '{userName}'";

            using (var sqlConnection = ConnectToDatabase())
            {
                var localPassword = "";
                var localAccountType = "";
                var localId = 0;
                var localName = "";
                var localCountry = "";

                using (var sqlQuery = new MySqlCommand(sql, sqlConnection))
                {
                    Logger.Info("Running Query: \"{0}\"", sql);

                    var tableReader = sqlQuery.ExecuteReader();

                    while (tableReader.Read())
                    {
                        localPassword = tableReader.GetString("password");
                        localAccountType = tableReader.GetString("accounttype");
                        localId = tableReader.GetInt32("ID");
                        localName = tableReader.GetString("name");
                        localCountry = tableReader.GetString("country");
                    }
                }

                if (localAccountType == "admin" && localPassword == password)
                {
                    var admin = new Admin(localId, localName, localCountry, localAccountType);
                    Logger.Info("User successfully validated as {0}", admin);
                    Logger.Trace($"Leaving method {MethodBase.GetCurrentMethod().Name}");
                    return admin;
                }
                if (localAccountType == "referee" && localPassword == password)
                {
                    var referee = new Referee(localId, localName, localCountry, localAccountType);
                    Logger.Info("User successfully validated as {0}", referee);
                    Logger.Trace($"Leaving method {MethodBase.GetCurrentMethod().Name}");
                    return referee;
                }
                Logger.Info("Unable to validate user.");
                Logger.Trace($"Leaving method {MethodBase.GetCurrentMethod().Name}");
                return "WI";
            }
        }

        public static Competition StartCompetition(int id)
        {
            Logger.Trace($"Entering method {MethodBase.GetCurrentMethod().Name}");
            const string sql = "UPDATE competition set State = 'Active' where id = @id";

            using (var sqlConnection = ConnectToDatabase())
            {
                using (var sqlQuery = new MySqlCommand(sql, sqlConnection))
                {
                    Logger.Info("Running Query: \"{0}\"", sql);

                    sqlQuery.Parameters.AddWithValue("@id", id);

                    var result = sqlQuery.ExecuteNonQuery();
                    Logger.Info("{0} rows affected", result);
                }
            }
            Logger.Trace($"Leaving method {MethodBase.GetCurrentMethod().Name}");
            return GetCompetition(id);
        }

        public static void UpdateDiveTotalPoints(Dive dive)
        {
            Logger.Trace($"Entering method {MethodBase.GetCurrentMethod().Name}");
            const string sql = "UPDATE dive set TotalPoints = @totalpoints WHERE id = @id";
            using (var sqlConnection = ConnectToDatabase())
            {
                int result;
                using (var sqlQuery = new MySqlCommand(sql, sqlConnection))
                {
                    Logger.Info("Running Query: \"{0}\"", sql);

                    sqlQuery.Parameters.AddWithValue("@id", dive.Id);
                    sqlQuery.Parameters.AddWithValue("@totalpoints", dive.TotalPoints.Value);

                    result = sqlQuery.ExecuteNonQuery();
                    Logger.Info("{0} rows affected", result);
                }
                Logger.Trace($"Leaving method {MethodBase.GetCurrentMethod().Name}");
            }
        }

        /// <summary>
        ///     A framework for creating a new SQL-method.
        ///     Copy this and add/edit/replace code as needed
        /// </summary>
        private static void GenericSqlMethod()
        {
            Logger.Trace($"Entering method {MethodBase.GetCurrentMethod().Name}");
            const string sql = "ENTER YOUR SQL-CODE HERE";

            using (var sqlConnection = ConnectToDatabase())
            {
                // Put used variables here
                using (var sqlQuery = new MySqlCommand(sql, sqlConnection))
                {
                    Logger.Info("Running Query: \"{0}\"", sql);

                    // Put your database manipulating code here

                    // Use only the two rows below if inserting data to db
                    var result = sqlQuery.ExecuteNonQuery();
                    Logger.Info("{0} rows affected", result);
                }
            }
            Logger.Trace($"Leaving method {MethodBase.GetCurrentMethod().Name}");
        }

        /// <summary>
        ///     Test for trying to get values from a sanitised SQL-command for logger
        /// </summary>
        /// <param name="sqlQuery"></param>
        /// <returns> Returns the sanitised sql query string </returns>
        private static string SqlStatement(MySqlCommand sqlQuery)
        {
            var query = sqlQuery.CommandText;

            foreach (SqlParameter parameter in sqlQuery.Parameters)
            {
                query = query.Replace(parameter.ParameterName, parameter.Value.ToString());
                //query = Regex.Replace(query, parameter.ParameterName + @"\b", parameter.Value.ToString());
            }
            return query;
        }

        public static List<Assessment> GetAssessments(int diveId)
        {
            Logger.Trace($"Entering method {MethodBase.GetCurrentMethod().Name}");
            var sql = $"SELECT * FROM assessment WHERE DIVE = {diveId}";

            using (var sqlConnection = ConnectToDatabase())
            {
                var assessments = new List<Assessment>();
                using (var sqlQuery = new MySqlCommand(sql, sqlConnection))
                {
                    Logger.Info("Running Query: \"{0}\"", sql);

                    var tableReader = sqlQuery.ExecuteReader();
                    while (tableReader.Read())
                    {
                        var tempAssessment = new Assessment(
                            tableReader.GetInt32("Id"),
                            tableReader.GetFloat("Points"),
                            tableReader.GetInt32("Dive"),
                            tableReader.GetInt32("Referee"),
                            tableReader.GetInt32("Competition")
                            );
                        assessments.Add(tempAssessment);
                    }
                }
                Logger.Trace($"Leaving method {MethodBase.GetCurrentMethod().Name}");
                return assessments;
            }
        }
    }
}