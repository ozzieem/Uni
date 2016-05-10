using Client.Forms.RefereeClient;
using System.Net.Mime;
using System.Windows.Forms;

namespace Client
{
    internal class Program
    {
        private static void Main(string[] args)
        {
            // User Login. Directs to ConsoleIO.
            //LoginHandler.programState = LoginHandler.ProgramState.Console;
            //LoginHandler.programState = LoginHandler.ProgramState.Gui;
            //LoginHandler.LoginMenu(args);

            var presenter = new Presenter.Presenter();
            presenter.Initialize();
            presenter.RunApplication();
        }
    }
}