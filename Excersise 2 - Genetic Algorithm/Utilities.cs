using System;
using System.Collections.Generic;

namespace Excersise_2___Genetic_Algorithm
{
    static class Utilities
    {
        public static List<double> calculatePercentagesList(double[] values, double total)
        {
            var returnList = new List<double>();
            for (int i = 0; i < values.Length; i++)
            {
                returnList.Add((values[i] / total) * 100.0); 
            }
            return returnList;
        }

        public static double getRandomDoubleWithMinMax(this Random random, double min, double max)
        {
            return random.NextDouble() * (max - min) + min;
        }
    }
}