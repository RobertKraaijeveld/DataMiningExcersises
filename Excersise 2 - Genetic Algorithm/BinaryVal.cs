using System;
using System.Linq;
using System.Collections.Generic;


namespace Excersise_2___Genetic_Algorithm
{
    class BinaryVal
    {
        private static readonly int BINARY_BASE = 2;
        private int[] bits;

        public BinaryVal(int[] bits)
        {
            this.bits = bits;
        }

        public override string ToString()
        {
            //join concats all str elements with the specified delimiter
            return string.Join("", bits.Select(x => x.ToString()).ToArray());
        }

        public static int binaryToInt(BinaryVal bv)
        {
            int returnInt = 0;

            for (int i = 0; i < bv.bits.Length; i++)
            {
                var exponent = bv.bits.Length - (i + 1);
                returnInt += bv.bits[i] * (int) Math.Pow(BINARY_BASE, exponent);
            }
            return returnInt;
        }

        public static BinaryVal  intToBinary(int x)
        {
            var returnBitsList = new List<int>();
            int quotient;

            do
            {
                quotient = x / BINARY_BASE;
                
                returnBitsList.Add(x % BINARY_BASE);
                x = quotient;                
            } 
            while (quotient != 0);
            
            returnBitsList.Reverse();
            return new BinaryVal(returnBitsList.ToArray());
        }
    }
}
