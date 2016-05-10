using NLog;

namespace Server
{
    /// <summary>
    ///     Server konsol. Lyssnande tråd körs under hela exekveringen.
    /// </summary>
    public static class Program
    {
        private static readonly Logger Logger = LogManager.GetCurrentClassLogger();

        private static void Main(string[] args)
        {
            Logger.Info("---------- Starting new session ----------");
            NetworkHandler.StartListening();
        }
    }
}