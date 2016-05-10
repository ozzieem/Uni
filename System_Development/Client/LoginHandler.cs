using ClassLibrary;
using System;
using System.Net.Sockets;
using System.Windows.Forms;

namespace Client
{
    /// <summary>
    ///     Hanterar inloggning för användare. Växling mellan ConsoleIO.
    /// </summary>
    public static class LoginHandler
    {
        public static Admin UserAdmin = new Admin();
        public static Referee UserReferee = new Referee();

        public enum UserState
        {
            Admin,
            Referee,
            None
        }

        public enum ProgramState
        {
            Gui,
            Console
        }

        public static UserState userState = UserState.None;
        public static ProgramState programState;

        public static void LoginMenu(object obj)
        {
            Console.Clear();

            while (true)
            {
                try
                {
                    switch (userState)
                    {
                        case UserState.None:
                            switch (programState)
                            {
                                case ProgramState.Console:
                                    LoginValidationConsole();
                                    break;

                                case ProgramState.Gui:
                                    LoginValidationGui(obj);
                                    break;

                                default:
                                    throw new ArgumentOutOfRangeException();
                            }
                            break;

                        case UserState.Admin:
                            ConsoleIO.RunAdmin(UserAdmin);
                            break;

                        case UserState.Referee:
                            ConsoleIO.RunReferee(UserReferee);
                            break;

                        default:
                            throw new ArgumentOutOfRangeException();
                    }
                }
                catch (InvalidCastException invalidCastException)
                {
                    Console.WriteLine(invalidCastException.Message);
                }
                catch (ArgumentOutOfRangeException outOfRangeException)
                {
                    Console.WriteLine(outOfRangeException.Message);
                }
                catch (TypeInitializationException initialization)
                {
                    Console.WriteLine(initialization.Message);
                }
            }
        }

        private static void LoginValidationGui(object userInfo)
        {
            ClientNetworkHandler.Connect();
            var obj = ClientNetworkHandler.SendAndReceive($"LI;{userInfo}");

            // Checks which user through received object
            var tAdmin = obj as Admin;
            if (tAdmin != null)
            {
                UserAdmin = tAdmin;
                userState = UserState.Admin;
            }

            var tReferee = obj as Referee;
            if (tReferee != null)
            {
                UserReferee = tReferee;
                userState = UserState.Referee;
            }
            else if (obj is string)
            {
                MessageBox.Show((string)obj, "Wrong Input!", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private static void LoginValidationConsole()
        {
            while (true)
            {
                try
                {
                    Console.Write("Login Name: ");
                    var name = Console.ReadLine();
                    Console.Write("Password: ");
                    var password = Console.ReadLine();
                    ClientNetworkHandler.Connect();
                    var obj = ClientNetworkHandler.SendAndReceive($"LI;{name};{password}");

                    // Checks which user through received object
                    var tAdmin = obj as Admin;
                    if (tAdmin != null)
                    {
                        UserAdmin = tAdmin;
                        userState = UserState.Admin;
                        Console.Clear();
                        Console.WriteLine("Welcome {0}! (Admin)", tAdmin.Name);
                        return;
                    }

                    var tReferee = obj as Referee;
                    if (tReferee != null)
                    {
                        UserReferee = tReferee;
                        userState = UserState.Referee;
                        Console.Clear();
                        Console.WriteLine("Welcome {0}! (Referee)", tReferee.Name);
                        return;
                    }
                    if ((string)obj == "")
                    {
                        Console.WriteLine("Wrong usernamn or password!");
                    }
                }
                catch (SocketException socketException)
                {
                    Console.WriteLine(socketException.Message);
                }
                catch (FormatException formatException)
                {
                    Console.WriteLine(formatException.Message);
                }
                catch (NullReferenceException nullReference)
                {
                    Console.WriteLine(nullReference.Message);
                    Console.WriteLine("Wrong username or password!");
                }
            }
        }
    }
}