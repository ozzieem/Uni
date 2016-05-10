namespace ClassLibrary
{
    public class MyMessage
    {
        public MyMessage()
        {
            Data = new byte[16384];
        }

        public MyMessage(int size)
        {
            Data = new byte[size];
        }

        public byte[] Data { get; set; }
    }
}