using NLog;
using System;
using System.Diagnostics;
using System.IO;
using System.Net;
using System.Net.NetworkInformation;
using System.Net.Sockets;

namespace ClassLibrary
{
    public static class ClientNetworkHandler
    {
        private static readonly Logger Logger = LogManager.GetCurrentClassLogger();
        public static NetworkStream MainStream;
        public static TcpClient MainTcpClient;
        private const string IpAdress = "10.22.3.74";
        private const int Port = 5004;

        public static void Connect()
        {
            try
            {
                var ping = new Ping();
                var reply = ping.Send(IpAdress, 10);

                Logger.Info("Attempting to connect to server.");
                if (reply.Status == IPStatus.Success)
                {
                    MainTcpClient = new TcpClient(IPAddress.Parse(IpAdress).ToString(), Port);
                    Logger.Info($"{((IPEndPoint)MainTcpClient.Client.RemoteEndPoint).Address}" +
                                ": Connected to server.");
                    MainStream = MainTcpClient.GetStream();
                }
                else
                {
                    Logger.Info("Failed to connect to server.");
                    throw new PingException("Servern är inte aktiv");
                }
            }
            catch (PingException pingException)
            {
                Console.WriteLine("PingException: " + pingException.Message);
            }
            catch (SocketException socketException)
            {
                Console.WriteLine("SocketException:" + socketException.Message);
            }
        }

        /// <summary>
        ///     Communicates with the server as a client through the Tcp-connection
        /// </summary>
        /// <param name="obj">Object to send to Server</param>
        /// <returns></returns>
        public static object SendAndReceive(object obj)
        {
            try
            {
                while (MainTcpClient.Connected)
                {
                    SendToServer(obj);
                    var returnObject = ReceiveFromServer();

                    if (returnObject == null)
                    {
                        throw new NullReferenceException("Unable to recieve data.\n");
                    }

                    return returnObject;
                }
                return null;
            }
            catch (SocketException socketException)
            {
                return "SocketException: " + socketException.Message;
            }
            catch (IOException ioException)
            {
                return "IOException: " + ioException.Message;
            }
            catch (NullReferenceException nullReferenceException)
            {
                return $"Finns ej någon server på IP-adress: {IpAdress}";
            }
        }

        /// <summary>
        ///     Reads the stream with data from server
        /// </summary>
        /// <returns>Received object from server</returns>
        public static object ReceiveFromServer()
        {
            var recmsg = new MyMessage();
            //if (MainStream.DataAvailable)
            MainStream.Read(recmsg.Data, 0, recmsg.Data.Length);
            var receivedObject = Serializer.Deserialize(recmsg);
            Logger.Info($"{((IPEndPoint)MainTcpClient.Client.RemoteEndPoint).Address}: Receiving {receivedObject.GetType()} from server");
            return receivedObject;
        }

        /// <summary>
        ///     Sending object to server on current stream
        /// </summary>
        /// <param name="obj">Object to send</param>
        public static void SendToServer(object obj)
        {
            Logger.Info($"{((IPEndPoint)MainTcpClient.Client.RemoteEndPoint).Address}: Sending {obj.GetType()} to server");
            var message = Serializer.Serialize(obj);
            MainStream.Write(message.Data, 0, message.Data.Length);
        }
    }
}