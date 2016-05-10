using System;
using System.Text;

namespace ClassLibrary
{
    /// <summary>
    ///     Arvsklass för Diver och Referee
    /// </summary>
    [Serializable]
    public class Person : BaseObject
    {
        public string Country;
        public string Name;
        public string Username;
        public string Password;
        public string AccountType;

        /// <summary>
        ///     ToString-funktion för att skriva ut information i konsol
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            var str = new StringBuilder();
            str.Append(base.ToString() + " " + Name + " " + Country);

            return str.ToString();
        }

        #region Konstruktorer

        public Person()
        {
            Country = "";
            Name = "";
            Username = "";
            Password = "";
            AccountType = "";
        }

        public Person(int id, string name, string country, string accountType) : base(id)
        {
            Name = name;
            Country = country;
            AccountType = accountType;
        }

        public Person(string name, string country, string accountType)
        {
            Name = name;
            Country = country;
            AccountType = accountType;
        }

        public Person(int id, string name, string country) : base(id)
        {
            Name = name;
            Country = country;
        }

        public Person(string name, string country)
        {
            Name = name;
            Country = country;
        }

        #endregion Konstruktorer
    }
}