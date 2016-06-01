        static byte[] GetArray(long value)
        {

            using (MemoryStream stream = new MemoryStream())

            using (BinaryWriter writer = new BinaryWriter(stream))

            {

                writer.Write(value);

                return stream.ToArray();

            }

        }

        private static void Main(string[] args)
        {

                long someLong = 166327;

                byte[] byteArray = BitConverter.GetBytes(someLong);

            Console.WriteLine("Long: " + someLong);
            Console.Write("Stored in bytes: (");

            foreach (var bbb in byteArray)
            {
                Console.Write(bbb + ", ");
            }
            Console.Write("\b\b)");

            Console.ReadLine();
        }