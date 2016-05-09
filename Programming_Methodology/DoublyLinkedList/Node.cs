namespace DoublyLinkedList
{
    public class Node<T> where T : class
    {
        public T Data;
        public Node<T> Next;
        public Node<T> Prev;

        public Node()
        {
            Data = default(T);
            Next = null;
            Prev = null;
        }

        public Node(T data)
        {
            Data = data;
        }

        public Node(T data, Node<T> next, Node<T> prev)
        {
            Data = data;
            Next = next;
            Prev = prev;
        }
    }

    public class Int
    {
        public int Value;

        public Int()
        {
            Value = 0;
        }

        public Int(int value)
        {
            Value = value;
        }
    }
}