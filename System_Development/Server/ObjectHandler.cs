using ClassLibrary;
using NLog;
using System;
using System.Net.Sockets;

namespace Server
{
    public static class ObjectHandler
    {
        private static readonly Logger Logger = LogManager.GetCurrentClassLogger();

        /// <summary>
        ///     Handles the unpacked objects
        /// </summary>
        /// <param name="obj">Received object</param>
        public static MyMessage HandleObject(object obj)
        {
            var returnMessage = new MyMessage();

            try
            {
                var diver = obj as Diver;
                if (diver != null)
                {
                    DbHandler.InsertDiver(diver);
                    const string returnString = "Diver inserted!\n";
                    returnMessage = Serializer.Serialize(returnString);
                }

                var dive = obj as Dive;
                if (dive != null)
                {
                    CompetitionHandler.SetCurrentDive(dive);
                    string returnString = $"Current active dive = {dive}!\n";
                    returnMessage = Serializer.Serialize(returnString);
                }

                var assessment = obj as Assessment;
                if (assessment != null)
                {
                    CompetitionHandler.AddAssessment(assessment);
                    returnMessage = Serializer.Serialize("Assessment done.\n");
                }

                var operationCode = obj as string;
                if (operationCode != null)
                {
                    returnMessage = OperationCodeHandler((string)obj);
                }

                var competition = obj as Competition;
                if (competition != null)
                {
                    DbHandler.InsertCompetition(competition);
                    const string returnString = "Competition inserted!\n";
                    returnMessage = Serializer.Serialize(returnString);
                }

                var referee = obj as Referee;
                if (referee != null)
                {
                    DbHandler.InsertReferee(referee);
                    const string returnString = "Referee inserted!\n";
                    returnMessage = Serializer.Serialize(returnString);
                }
            }
            catch (ArgumentNullException argumentNullException)
            {
                var str = "ArgumentNullException: " + argumentNullException.Message;
                Logger.Debug(str);
                returnMessage = Serializer.Serialize(str);
            }
            finally
            {
                Logger.Info("Serialized message length: {0}\n", returnMessage.Data.Length);
            }
            return returnMessage;
        }

        /// <summary>
        ///     Hanterar operationskoder. Skickar tillbaka ett objekt beroende på kod.
        /// </summary>
        /// <param name="obj">Operationskod</param>
        /// <param name="stream">
        /// </param>
        private static MyMessage OperationCodeHandler(string obj)
        {
            var messageOut = new MyMessage();
            try
            {
                Logger.Info($"Executing operationcode: {obj}");
                object tempObject;
                switch (obj)
                {
                    case "GetDivers": // Hämtar diver-lista
                        tempObject = DbHandler.GetDivers();
                        messageOut = Serializer.Serialize(tempObject);
                        break;

                    case "GetLeaderList":
                        messageOut = Serializer.Serialize(CompetitionHandler.ActiveCompetition.ListDiver);
                        break;

                    case "GetDiveTypes":
                        tempObject = DbHandler.GetDiveTypes();
                        messageOut = Serializer.Serialize(tempObject);
                        break;

                    case "GetReferees": // Hämta referee-lista
                        tempObject = DbHandler.GetReferees();
                        messageOut = Serializer.Serialize(tempObject);
                        break;

                    case "GetCompetitions": // Hämtar competition-lista
                        tempObject = DbHandler.GetAvailableCompetitions();
                        messageOut = Serializer.Serialize(tempObject);
                        break;

                    case "IsCurrentDiveDone":   // Hämtar och uppdaterar admins lokala CurrentDive
                        tempObject = CompetitionHandler.CurrentDiveComplete();
                        if ((bool)tempObject)
                        {
                            CompetitionHandler.CurrentDive.CalculateTotalPoints();
                            CompetitionHandler.SendCurrentDiveToDatabaseAndUpdateActiveCompetition();
                        }
                        messageOut = Serializer.Serialize(CompetitionHandler.CurrentDive);
                        break;

                    case "CompetitionComplete":
                        CompetitionHandler.ActiveCompetition = null;
                        messageOut = Serializer.Serialize("Competition Complete");
                        break;

                    default:
                        if (obj[0] == 'G' && obj[1] == 'C' && obj[2] == 'D') // Hämtar CurrentDive
                        {
                            Dive currentDive = null;
                            var userId = int.Parse(obj.Remove(0, 4));

                            if (CompetitionHandler.ActiveCompetition != null)
                            {
                                foreach (var referee in CompetitionHandler.ActiveCompetition.ListReferee)
                                {
                                    if (referee.Id == userId)
                                    {
                                        currentDive = CompetitionHandler.CurrentDive;
                                        Logger.Info("Returning the current dive to referee with id: " + referee.Id);
                                        break;
                                    }
                                }
                            }
                            messageOut = Serializer.Serialize(currentDive);
                        }
                        else if (obj[0] == 'S' && obj[1] == 'C') // Startar competition
                        {
                            var id = int.Parse(obj.Remove(0, 3));
                            CompetitionHandler.SetCompetition(DbHandler.StartCompetition(id));
                            var activeDivesList = CompetitionHandler.GetAllDives();
                            messageOut = Serializer.Serialize(activeDivesList);
                        }
                        else if (obj[0] == 'G' && obj[1] == 'C' && obj[2] == 'C') // Hämtar pågående tävling
                        {
                            var id = int.Parse(obj.Remove(0, 4));
                            var competition = new Competition();
                            if (CompetitionHandler.ActiveCompetition != null)
                            {
                                foreach (var referee in CompetitionHandler.ActiveCompetition.ListReferee)
                                {
                                    if (referee.Id == id)
                                    {
                                        competition = CompetitionHandler.ActiveCompetition;
                                        Logger.Info("Returning the active competition to referee with id: " + referee.Id);
                                        break;
                                    }
                                }
                            }
                            messageOut = Serializer.Serialize(competition);
                        }
                        break;
                }
            }
            catch (ArgumentNullException nullException)
            {
                var str = nullException.Message;
                Logger.Error("ArgumentNullException: " + str);
                messageOut = Serializer.Serialize(str);
            }
            catch (NullReferenceException nullReferenceException)
            {
                var str = nullReferenceException.Message;
                Logger.Error("NullReferenceException: " + str);
                messageOut = Serializer.Serialize(str);
            }
            return messageOut;
        }

        public static bool CheckUserAuthentication(NetworkStream stream, string ipAdress)
        {
            lock (NetworkHandler.Users)
            {
                try
                {
                    Person person = null;
                    var loginMsg = new MyMessage();
                    stream.Read(loginMsg.Data, 0, loginMsg.Data.Length);
                    var loginInfo = Serializer.Deserialize(loginMsg) as string;
                    var str = loginInfo?.Split(';');
                    if (str?[0] == "LI")
                    {
                        Logger.Info("Client Authentication. Validating username {0}.", str[1]);
                        var validate = DbHandler.LoginCheck(str[1], str[2]);
                        person = validate as Person;
                        if (person != null)
                        {
                            Logger.Info("IP: " + ipAdress + " linked with " + person);
                            NetworkHandler.Users.TryAdd(ipAdress, person);
                        }
                        if (validate is string)
                        {
                            if ((string)validate == "WI")
                                loginMsg = Serializer.Serialize("Fel användarnamn eller lösenord.");
                        }
                        else
                            loginMsg = Serializer.Serialize(validate);
                    }
                    stream.Write(loginMsg.Data, 0, loginMsg.Data.Length);
                    if (person != null)
                        return true;
                }
                catch (IndexOutOfRangeException indexOutOfRangeException)
                {
                    Logger.Info("IndexOutOfRangeException: " + indexOutOfRangeException.Message);
                }
                return false;
            }
        }
    }
}