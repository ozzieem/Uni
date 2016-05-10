using ClassLibrary;
using NUnit.Framework;

namespace UnitTestClasses
{
    /// <summary>
    ///     Summary description for SerializerTest
    /// </summary>
    [TestFixture]
    public class SerializerTest
    {
        [Test]
        public void SerializeTest()
        {
            var diver = new Diver(5, "Körberg", "Finland", 105, "Kvinna", 9);
            var seriObject = Serializer.Serialize(diver);

            var deseriObject = Serializer.Deserialize(seriObject);

            Assert.AreEqual("Körberg", ((Diver)deseriObject).Name);
            Assert.AreEqual("Finland", ((Diver)deseriObject).Country);
        }
    }
}