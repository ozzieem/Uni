using ClassLibrary;
using NLog;
using System;
using System.Collections.Concurrent;
using System.IO;
using System.Net;
using System.Net.Sockets;
using System.Threading;

namespace Server
{
    public static class NetworkHandler
    {
        private static readonly Logger Logger = LogManager.GetCurrentClassLogger();
        public static ConcurrentDictionary<string, Person> Users = new ConcurrentDictionary<string, Person>();
        public static string TempIp = "";

        public static void StartListening()
        {
            var tcpServerRunThread = new Thread(TcpServerRun);
            tcpServerRunThread.Start();
        }

        private static void TcpServerRun()
        {
            Logger.Info("Server is running.\n Listening...");
            var tcpListener = new TcpListener(IPAddress.Any, 5004);
            tcpListener.Start();
            while (true)
            {
                var client = tcpListener.AcceptTcpClient();
                var tcpHandlerThread = new Thread(TcpHandler);
                tcpHandlerThread.Start(client);
            }
        }

        /// <summary>
        ///     Opens a stream for clients to connect and send objects to.
        ///     Server sends back an object if needed depending on received object.
        /// </summary>
        /// <param name="client"></param>
        private static void TcpHandler(object client)
        {
            var clientIp = "";
            try
            {
                var tcpClient = (TcpClient)client;
                var stream = tcpClient.GetStream();
                clientIp = ((IPEndPoint)tcpClient.Client.RemoteEndPoint).Address.ToString();

                Logger.Info("Connected client: {0}, TTL: {1}, Protocol: {2}",
                    clientIp,
                    tcpClient.Client.Ttl,
                    tcpClient.Client.ProtocolType);

                if (!ObjectHandler.CheckUserAuthentication(stream, clientIp))
                    tcpClient.Close();

                while (tcpClient.Connected)
                {
                    var receivedMessage = new MyMessage();
                    // Reads input message from the client
                    stream.Read(receivedMessage.Data, 0, receivedMessage.Data.Length);
                    // Unpacks the object for inspection
                    var receivedObject = Serializer.Deserialize(receivedMessage);

                    var logout = receivedObject as string;
                    if (logout == "Logout")
                    {
                        break;
                    }
                    receivedMessage = ObjectHandler.HandleObject(receivedObject);
                    stream.Write(receivedMessage.Data, 0, receivedMessage.Data.Length);
                }
                Logger.Info("Client: {0} disconnected.\n", clientIp);
                stream.Close();
                tcpClient.Close();
            }
            catch (InvalidCastException invalidCastException)
            {
                Logger.Info("InvalidCastException: " + invalidCastException.Message);
            }
            catch (EndOfStreamException endOfStreamException)
            {
                Logger.Info("EndOfStreamException: " + endOfStreamException.Message);
            }
            catch (IOException ioException)
            {
                Logger.Info("IOException: " + ioException.Message);
            }
            catch (SocketException socketException)
            {
                Logger.Info("SocketException: " + socketException.Message);
            }
            finally
            {
                Person tPerson;
                Users.TryRemove(clientIp, out tPerson);
            }
        }
    }
}