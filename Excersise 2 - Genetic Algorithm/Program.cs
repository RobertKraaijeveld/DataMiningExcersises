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
            /* FUNCTIONS TO DEFINE (for each problem):
            Func<Ind> createIndividual;                                 ==> input is nothing, output is a new individual
            Func<Ind,double> computeFitness;                            ==> input is one individual, output is its fitness
            Func<Ind[],double[],Func<Tuple<Ind,Ind>>> selectTwoParents; ==> input is an array of individuals (population) and an array of corresponding fitnesses, output is a function which (without any input) returns a tuple with two individuals (parents)
            Func<Tuple<Ind, Ind>, Tuple<Ind, Ind>> crossover;           ==> input is a tuple with two individuals (parents), output is a tuple with two individuals (offspring/children)
            Func<Ind, double, Ind> mutation;                            ==> input is one individual and mutation rate, output is the mutated individual
            
            public GeneticAlgorithm(double crossoverRate, double mutationRate, bool elitism, int populationSize, int numIterations)
            {
                this.crossoverRate = crossoverRate;
                this.mutationRate = mutationRate;
                this.elitism = elitism;
                this.populationSize = populationSize;
                this.numIterations = numIterations;
            }
            */

            var crossoverRate = 0.85;
            var mutationRate = 0;
            var elitism = true;
            var populationSize = 5;
            var numIterations = 100;

            GeneticAlgorithm<BinaryVal> fakeProblemGA = new GeneticAlgorithm<BinaryVal>(crossoverRate, mutationRate, elitism, populationSize, numIterations);
            var solution = fakeProblemGA.Run(createIndividual, computeFitness, selectTwoParents, null, null); 
        }

        private static BinaryVal createIndividual()
        {
            return BinaryVal.intToBinary(random.Next(0, 32));
        }

/*
Func<Ind> createIndividual, Func<Ind, double> computeFitness, Func<Ind[], double[], Func<Tuple<Ind, Ind>>> selectTwoParents,
            Func<Tuple<Ind, Ind>, Tuple<Ind, Ind>> crossover, Func<Ind, double, Ind> mutation)
 */

        private static double computeFitness(BinaryVal binaryVal)
        {
            var intForBinary = BinaryVal.binaryToInt(binaryVal);
            return -(Math.Pow(intForBinary, 2.0)) + (7 * intForBinary); 
        }


        private static Func<Tuple<BinaryVal, BinaryVal>> selectTwoParents (BinaryVal[] population, double[] fitnesses)
        {
            var chosenParents = new List<BinaryVal>();
            var wheelSections = getRouletteWheelSections(population, fitnesses); 

            while(chosenParents.Count < 2)
            {
                //doesnt always add up to exactly 100 because of rounding
                var highestWheelSectionValue =  wheelSections.Last().Item2;
                var randomPercentage = random.getRandomDoubleWithMinMax(0.0, highestWheelSectionValue); 

                //TODO: Maybe make wheelsection a class or struct 
                for (int i = 0; i < wheelSections.Count; i++)
                {
                    if(randomPercentage >= wheelSections[i].Item1 && randomPercentage <= wheelSections[i].Item2
                        && chosenParents.Contains(population[i]) == false)
                    {
                        Console.WriteLine("Binary value " + BinaryVal.binaryToInt(population[i]) + " has won the roulette since " + randomPercentage + " is greater "
                        + " than its wheelsection start, " + wheelSections[i].Item1 + " and smaller than " + wheelSections[i].Item2);
                        chosenParents.Add(population[i]);
                        break;
                    }
                }
            }
            return () => Tuple.Create(chosenParents[0], chosenParents[1]);

        }

        private static List<Tuple<double, double>> getRouletteWheelSections(BinaryVal[] population, double[] fitnesses)
        {
            var totalFitness = (int) fitnesses.Sum();
            var fitnessesAsPercentages = Utilities.calculatePercentagesList(fitnesses, totalFitness);

            var percentageSections = new List<Tuple<double, double>>();
            for(var i = 0; i < population.Length; i++)
            {
                var currentFitnessPercentage = Math.Abs(fitnessesAsPercentages[i]);

                //problems are caused by negative fitnesses. 
                if(i != 0)
                {
                    var previousSectionEnd = percentageSections[i-1].Item2;
                    var x = previousSectionEnd + currentFitnessPercentage;
                    Console.WriteLine("Adding new percentage section of " + previousSectionEnd + " to " + x + 
                    " since " + previousSectionEnd + " plus " + currentFitnessPercentage + " equals to " + x);
                    percentageSections.Add(new Tuple<double, double>(previousSectionEnd, x));                                       
                }
                else
                {
                    Console.WriteLine("Adding new percentage section of " + 0 + " to " + currentFitnessPercentage);                    
                    percentageSections.Add(new Tuple<double, double>(0.0, currentFitnessPercentage));
                }
            }
            return percentageSections;
        }
/*        
        private static Tuple<BinaryVal, BinaryVal> crossover (Func<Tuple<BinaryVal, BinaryVal>> parents)
        {}
        
        private static Tuple<BinaryVal, BinaryVal> crossover (Tuple<BinaryVal, BinaryVal> parents)
   */      
    }
}
