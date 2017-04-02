using System;
using System.Linq;
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
                var percentage = (values[i] / total) * 100.0;
                percentage = percentage < 0.0 ? 0.0 : percentage;   
                returnList.Add(percentage);
            }
            return returnList;
        }

        public static double getRandomDoubleWithMinMax(this Random random, double min, double max)
        {
            return random.NextDouble() * (max - min) + min;
        }

        public static int getExistingRandomIndex(int[] a, int[] b)
        {
            var random = new Random();
            //this makes sure the random index is not beyond one of the parents' length 
            if(a.Length >= b.Length)
                return random.Next(0, b.Length - 1);
            else
                return random.Next(0, a.Length - 1);                
        } 

        public static Tuple<int[], int[]> splitArrayOnIndex(int[] array, int index)
        {
            var firstArray = array.Take(index).ToArray();
            var secondArray = array.Skip(index).ToArray();
            return Tuple.Create(firstArray, secondArray);
        }
    }
}