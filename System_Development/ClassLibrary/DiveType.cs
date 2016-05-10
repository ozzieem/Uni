using System;

namespace ClassLibrary
{
    [Serializable]
    public class DiveType : BaseObject
    {
        public string Code { get; set; }
        public float Difficulty;

        public DiveType()
        {
            Difficulty = -1.0f;
            Code = "";
        }

        public DiveType(int id, string code, float difficulty)
            : base(id)
        {
            Difficulty = difficulty;
            Code = code;
        }
    }
}