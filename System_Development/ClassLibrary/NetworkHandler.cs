using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Threading;
using System.Net.Sockets;
using System.Net;

namespace ClassLibrary
{
    public static class NetworkHandler
    {
        public static void ConnectAndSend(object obj)
        {
            var mThread = new Thread(ConnectAsClient);
            mThread.Start(obj);
        }

        private static void ConnectAsClient(object obj)
        {
            var client = new TcpClient();
            client.Connect(IPAddress.Parse("10.22.2.1"), 5004);
            NetworkStream stream = client.GetStream();
            
            MyMessage Message = Serializer.Serialize(obj);

            // Send message to server
            //if (diverMessage == null);
            var receiveMsg = new byte[1024];
            stream.Write(Message.Data, 0, Message.Data.Length);
            Console.Write("Message length: {0}\n\n", Message.Data.Length);

            // Reads from server
            stream.Read(receiveMsg, 0, receiveMsg.Length);
            var recMsgStr = Encoding.ASCII.GetString(receiveMsg).TrimEnd((char)0);
            Console.Write("Received message: {0} \n", recMsgStr);

        }

        public static void StartListening()
        {

            var tcpServerRunThread = new Thread(TcpServerRun);
            tcpServerRunThread.Start();

        }
        private static void TcpServerRun()
        {

            var tcpListener = new TcpListener(IPAddress.Any, 5004);
            tcpListener.Start();
            while (true)
            {
                var client = tcpListener.AcceptTcpClient();
                var tcpHandlerThread = new Thread(TcpHandler);
                tcpHandlerThread.Start(client);
            }
        }

        private static void TcpHandler(object client)
        {
            var mClient = (TcpClient)client;
            var stream = mClient.GetStream();

            var mm = new MyMessage();
            // Reads input message from the client
            var message = new byte[4096];
            stream.Read(message, 0, message.Length);
            mm.Data = message;
            var obj = Serializer.Deserialize(mm);
            if (obj is Diver)
                //GetDiverObject(diverEtt as Diver);

            stream.Close();
            mClient.Close();
        }
    }
}
