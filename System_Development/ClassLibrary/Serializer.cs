using System.IO;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;

namespace ClassLibrary
{
    public static class Serializer
    {
        public static MyMessage Serialize(object anySerializableObject)
        {
            using (var memoryStream = new MemoryStream())
            {
                new BinaryFormatter().Serialize(memoryStream, anySerializableObject);
                return new MyMessage { Data = memoryStream.ToArray() };
            }
        }

        public static object Deserialize(MyMessage message)
        {
            try
            {
                using (var memoryStream = new MemoryStream(message.Data))
                    return new BinaryFormatter().Deserialize(memoryStream);
            }
            catch (SerializationException serializationException)
            {
                return "SerializationException: " + serializationException.Message;
            }
        }
    }
}