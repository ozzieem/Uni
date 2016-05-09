using DoublyLinkedList;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace UnitTestDoublyLinkedList
{
    [TestClass]
    public class DoublyLinkedTest
    {
        [TestMethod]
        public void DllAddFirst()
        {
            var list = new DlList<Int>();
            list.AddFirst(new Int(2));
            Assert.AreEqual(2, list.First.Data.Value);
            list.AddFirst(new Int(1));
            Assert.AreEqual(1, list.First.Data.Value);
        }

        [TestMethod]
        public void DllAddLast()
        {
            var list = new DlList<Int>();
            list.AddLast(new Int(2));
            Assert.AreEqual(2, list.Last.Data.Value);
            list.AddLast(new Int(1));
            Assert.AreEqual(1, list.Last.Data.Value);
        }

        [TestMethod]
        public void DllRemoveFirst()
        {
            var list = new DlList<Int>();
            list.AddFirst(new Int(3));
            list.AddFirst(new Int(2));
            list.AddFirst(new Int(1));
            Assert.AreEqual(1, list.First.Data.Value);

            list.RemoveFirst();
            Assert.AreEqual(2, list.First.Data.Value);
            list.RemoveFirst();
            Assert.AreEqual(3, list.First.Data.Value);
        }

        [TestMethod]
        public void DllRemoveLast()
        {
            var list = new DlList<Int>();
            list.AddLast(new Int(1));
            list.AddLast(new Int(2));
            list.AddLast(new Int(3));
            Assert.AreEqual(3, list.Last.Data.Value);

            list.RemoveLast();
            Assert.AreEqual(2, list.Last.Data.Value);
            list.RemoveLast();
            Assert.AreEqual(1, list.Last.Data.Value);
        }

        [TestMethod]
        public void DllClear()
        {
            var list = new DlList<Int>();
            list.AddLast(new Int(1));
            list.AddLast(new Int(2));
            list.AddLast(new Int(3));
            Assert.AreEqual(3, list.Last.Data.Value);
            Assert.AreEqual(1, list.First.Data.Value);

            list.Clear();
            Assert.IsNull(list.Last);
            Assert.IsNull(list.First);
        }

        [TestMethod]
        public void DllCount()
        {
            var list = new DlList<Int>();
            list.AddLast(new Int(1));
            list.AddLast(new Int(2));
            list.AddLast(new Int(3));
            list.AddLast(new Int(4));

            var listSize = list.Count();

            Assert.IsTrue(listSize == 4);
            Assert.IsFalse(listSize == 0);
        }

        [TestMethod]
        public void DllContains()
        {
            var list = new DlList<Int>();
            list.AddLast(new Int(1));
            list.AddLast(new Int(2));
            list.AddLast(new Int(3));
            list.AddLast(new Int(4));

            var trueNode = new Node<Int>(new Int(4));
            var falseNode = new Node<Int>(new Int(5));

            Assert.IsTrue(list.Contains(trueNode));
            Assert.IsFalse(list.Contains(falseNode.Data));
        }

        [TestMethod]
        public void DllFind()
        {
            var list = new DlList<Int>();
            list.AddLast(new Int(1));
            list.AddLast(new Int(2));
            list.AddLast(new Int(3));
            list.AddLast(new Int(4));

            var four = new Int(4);
            var five = new Int(5);

            Assert.AreEqual(four.Value, list.Find(four).Data.Value);
            Assert.IsFalse(list.Find(five).Data.Value.Equals(five.Value));
        }
    }
}