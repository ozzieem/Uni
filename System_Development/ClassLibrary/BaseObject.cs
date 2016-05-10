using System;
using System.Text;

namespace ClassLibrary
{
    /// <summary>
    ///     Ska tilldela ID variablern till de klasser som ärver denna.
    /// </summary>
    [Serializable]
    public class BaseObject
    {
        public int Id;

        public BaseObject()
        {
            Id = -1;
        }

        public BaseObject(int id)
        {
            Id = id;
        }

        public override string ToString()
        {
            var str = new StringBuilder();
            str.Append(Id);

            return str.ToString();
        }
    }
}