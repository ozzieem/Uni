using System;

namespace ClassLibrary
{
    [Serializable]
    public class MyException : Exception
    {
        public MyException(string message)
            : base(message)
        {
        }
    }

    public class ListObjectNotFoundException : MyException
    {
        public ListObjectNotFoundException(string message)
            : base(message)
        {
        }
    }

    public class ListObjectAlreadyExistsException : MyException
    {
        public ListObjectAlreadyExistsException(string message)
            : base(message)
        {
        }
    }
}