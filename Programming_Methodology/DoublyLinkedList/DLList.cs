using System;
using System.Collections;
using System.Collections.Generic;
using static System.String;

namespace DoublyLinkedList
{
    /// <summary>
    ///     DoublyLinkedList
    /// </summary>
    /// <typeparam name="T">Any datatype</typeparam>
    public class DlList<T> : ICollection<T> where T : class
    {
        public DlList()
        {
            First = null;
            Last = null;
        }

        public Node<T> First { get; set; }
        public Node<T> Last { get; set; }

        /// <summary>
        ///     Removes all nodes from the LinkedList<T />.
        /// </summary>
        public void Clear()
        {
            First = null;
            Last = null;
        }

        /// <summary>
        ///     Same as AddLast
        /// </summary>
        /// <param name="item"></param>
        public void Add(T item)
        {
            AddLast(item);
        }

        /// <summary>
        ///     Determines whether a value is in the LinkedList<T />.
        /// </summary>
        /// <param name="item"></param>
        /// <returns></returns>
        public bool Contains(T item)
        {
            foreach (var classItem in this)
            {
                if (classItem.Equals(item))
                {
                    return true;
                }
            }
            return false;
        }

        /// <summary>
        ///     Copies the entire LinkedList
        ///     <T /> to a compatible one-dimensional Array, starting at the specified index of the target array.
        /// </summary>
        /// <param name="array"></param>
        /// <param name="arrayIndex"></param>
        public void CopyTo(T[] array, int arrayIndex)
        {
            var i = arrayIndex;
            foreach (var item in this)
            {
                array[i] = item;
                i++;
            }
        }

        /// <summary>
        ///     Returns an enumerator that iterates through the LinkedList<T />.
        /// </summary>
        /// <returns></returns>
        public IEnumerator<T> GetEnumerator()
        {
            var node = First;

            while (node != null)
            {
                yield return node.Data;
                node = node.Next;
            }
        }

        IEnumerator IEnumerable.GetEnumerator()
        {
            return GetEnumerator();
        }

        int ICollection<T>.Count
        {
            get
            {
                var count = 0;
                foreach (var item in this)
                {
                    count++;
                }
                return count;
            }
        }

        public bool Remove(T item)
        {
            throw new NotImplementedException();
        }

        public bool IsReadOnly
        {
            get { throw new NotImplementedException(); }
        }

        /// <summary>
        ///     Adds a new node containing the specified data at the start of the LinkedList.
        /// </summary>
        /// <param name="data"></param>
        public void AddFirst(T data)
        {
            var newNode = new Node<T>(data);

            if (First == null)
            {
                First = Last = newNode;
            }
            else
            {
                newNode.Next = First;
                First.Prev = newNode;
                First = newNode;
            }
        }

        /// <summary>
        ///     Adds the specified new node at the end of the LinkedList.
        /// </summary>
        /// <param name="data"></param>
        public void AddLast(T data)
        {
            var newNode = new Node<T>(data);

            if (Last == null)
            {
                First = Last = newNode;
            }
            else
            {
                Last.Next = newNode;
                newNode.Prev = Last;
                Last = newNode;
            }
        }

        /// <summary>
        ///     Removes the node at the start of the LinkedList<T />.
        /// </summary>
        public void RemoveFirst()
        {
            if (First == null)
            {
                throw new ArgumentNullException();
            }
            First = First.Next;
            First.Prev.Next = null;
            First.Prev = null;
        }

        /// <summary>
        ///     Removes the node at the end of the LinkedList<T />.
        /// </summary>
        public void RemoveLast()
        {
            if (Last == null)
            {
                throw new ArgumentNullException();
            }
            Last = Last.Prev;
            Last.Next.Prev = null;
            Last.Next = null;
        }

        /// <summary>
        ///     Finds the first node that contains the specified value.
        /// </summary>
        /// <param name="data"></param>
        /// <returns></returns>
        public Node<T> Find(T data)
        {
            var travNode = First;
            while (travNode.Next != null)
            {
                travNode = travNode.Next;
                if (travNode.Data.Equals(data))
                    return null;
            }
            return travNode;
        }

        /// <summary>
        ///     Gets the number of nodes actually contained in the LinkedList<T />.
        /// </summary>
        /// <returns></returns>
        public int Count()
        {
            var temp = First;

            var count = 0;

            while (temp != null)
            {
                count += 1;
                temp = temp.Next;
            }
            return count;
        }

        /// <summary>
        ///     Determines whether a node is in the LinkedList<T />.
        /// </summary>
        /// <param name="node"></param>
        /// <returns></returns>
        public bool Contains(Node<T> node)
        {
            var temp = First;
            var contains = false;

            while (temp != null)
            {
                if (Compare(temp.Data.ToString(), node.Data.ToString(), StringComparison.Ordinal) == 0)
                {
                    contains = true;
                    break;
                }

                temp = temp.Next;
            }
            return contains;
        }
    }
}

/*
Implementation of the doubly linked list:
+---------+<-- -->+---------+<-- -->+---------+<-- -->+---------+
| Data	  |  | |  | Data    |  | |  | Data    |  | |  | Data    |
+---------+  | |  +---------+  | |  +---------+  | |  +---------+
| next    |----   | next    |----   | next    |----   | next    |
+---------+  |    +---------+  |    +---------+  |    +---------+
| prev    |  -----| prev    |  -----| prev    |  -----| prev    |
+---------+       +---------+       +---------+       +---------+
*/