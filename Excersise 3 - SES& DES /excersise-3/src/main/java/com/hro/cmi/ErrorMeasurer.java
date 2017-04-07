package com.hro.cmi;

import java.util.ArrayList;

public class ErrorMeasurer
{
    //kinda shitty that even non-beta users have to supply dummy beta values
    public ArrayList<Triple<Double, Double, Double>> alphasBetasAndErrors;

    //just one method that returns both alpha and beta; getBestAlphaAndBeta(). 
    //and simply set both in Forecast. The children decide what they use.
    public Triple<Double, Double, Double> getBestAlphaAndBeta()
    {
        double bestAlpha = 0.0;
        double bestBeta = 0.0;

        double smallestErrorYet = Double.MAX_VALUE;          
        for (Triple<Double, Double, Double> measurement : alphasBetasAndErrors) 
        {
            if(measurement.third < smallestErrorYet)
            {
                smallestErrorYet = measurement.third;
                bestAlpha = measurement.first;
                bestBeta = measurement.second;
            }
        }        

        return new Triple<Double, Double, Double>(bestAlpha, bestBeta, smallestErrorYet);
    }
}

