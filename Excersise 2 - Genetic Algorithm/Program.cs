using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Excersise_2___Genetic_Algorithm
{
    class Program
    { 
        private static Random random = new Random(); 
        static void Main(string[] args)
        { 
            var crossoverRate = 0.8;
            var mutationRate = 0.1;
            var elitism = true;
            var populationSize = 50;
            var numIterations = 100;

            GeneticAlgorithm<BinaryVal> fakeProblemGA = new GeneticAlgorithm<BinaryVal>(crossoverRate, mutationRate, elitism, populationSize, numIterations);
            var solution = fakeProblemGA.Run(createIndividual, computeFitness, selectTwoParents, crossover, mutation); 

            Console.WriteLine("Best individual (in binary) = " + solution.ToString());
            Console.WriteLine("Best individual (in integer) = " + BinaryVal.binaryToInt(solution));
        }

        private static BinaryVal createIndividual()
        {
            return BinaryVal.intToBinary(random.Next(0, 32));
        }


        private static double computeFitness(BinaryVal binaryVal)
        {
            var intForBinary = BinaryVal.binaryToInt(binaryVal);
            return -(Math.Pow(intForBinary, 2.0)) + (7 * intForBinary); 
        }


        /*
            ROULETTE WHEEL SELECTION
         */

        private static Func<Tuple<BinaryVal, BinaryVal>> selectTwoParents (BinaryVal[] population, double[] fitnesses)
        {
            var chosenParents = new List<BinaryVal>();
            var wheelSections = getRouletteWheelSections(population, fitnesses); 

            while(chosenParents.Count < 2)
            {
                //doesnt always add up to exactly 100 because of rounding
                var highestWheelSectionValue =  wheelSections.Last().Item2;
                var randomPercentage = random.getRandomDoubleWithMinMax(0.0, highestWheelSectionValue); 

                for (int i = 0; i < wheelSections.Count; i++)
                {
                    if(randomPercentage >= wheelSections[i].Item1 && randomPercentage <= wheelSections[i].Item2
                        && chosenParents.Contains(population[i]) == false)
                    {
                        chosenParents.Add(population[i]);
                        break;
                    }
                }
            }
            return () => Tuple.Create(chosenParents[0], chosenParents[1]);

        }

        //TO REFACTOR: no need to convert to percentages
        private static List<Tuple<double, double>> getRouletteWheelSections(BinaryVal[] population, double[] fitnesses)
        {
            var wheelSections = new List<Tuple<double, double>>();

            var totalFitness = (int) fitnesses.Sum();
            var fitnessesAsPercentages = Utilities.calculatePercentagesList(fitnesses, totalFitness);

            for(var i = 0; i < population.Length; i++)
            {
                var currentFitnessPercentage = fitnessesAsPercentages[i];

                if(i > 0)
                {
                    var previousSectionEnd = wheelSections[i-1].Item2;
                    var x = previousSectionEnd + currentFitnessPercentage;

                    wheelSections.Add(new Tuple<double, double>(previousSectionEnd, x));                                       
                }
                else
                    wheelSections.Add(new Tuple<double, double>(0.0, currentFitnessPercentage));
            }
            return wheelSections;
        }

        private static Tuple<BinaryVal, BinaryVal> crossover (Tuple<BinaryVal, BinaryVal> parents)
        {
            var crossoverIndex = Utilities.getExistingRandomIndex(parents.Item1.bits, parents.Item2.bits);

            var firstChild = new BinaryVal(new int[5]);
            var secondChild = new BinaryVal(new int[5]);            

            var fatherSplit = Utilities.splitArrayOnIndex(parents.Item1.bits, crossoverIndex);
            var motherSplit = Utilities.splitArrayOnIndex(parents.Item2.bits, crossoverIndex);

            firstChild.bits = fatherSplit.Item1.Concat(motherSplit.Item2).ToArray();
            secondChild.bits = motherSplit.Item1.Concat(fatherSplit.Item2).ToArray();

            return Tuple.Create(firstChild, secondChild);
        }

        private static BinaryVal mutation(BinaryVal populationMember, double mutationRate)
        {
            double randomPercent;
            for (int i = 0; i < populationMember.bits.Length; i++)
            {
                randomPercent = random.getRandomDoubleWithMinMax(0.0, 100.0);
                if(randomPercent < mutationRate)
                    populationMember.flipBit(i);                   
            }
            return populationMember;
        }
    }
}
