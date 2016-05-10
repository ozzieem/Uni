using System;
using System.Collections.Generic;

namespace ClassLibrary
{
    /// <summary>
    ///     Denna klass kommer hålla koll på de poäng som kommer användas i programmen.
    /// </summary>
    [Serializable]
    public class Score
    {
        public float Value; //Ändrat från Doubles till Floats (RA)

        public Score()
        {
            Value = -1;
        }

        public Score(float value)
        {
            Value = value;
        }

        public void CalculateCompleteScore(List<Score> refScores, float difficulty)
        //Beräknar totalpoängen för ett hopp (RA)
        {
            float min = 10;
            float high = 0;
            float total = 0;
            foreach (var score in refScores)
            {
                if (score.Value < min)
                    min = score.Value;
                if (score.Value > high)
                    high = score.Value;
                total += score.Value;
            }
            total = total - min - high;
            total = total * difficulty;
            Value = total;
        }

        public float GetValue()
        {
            return Value;
        }
    }
}