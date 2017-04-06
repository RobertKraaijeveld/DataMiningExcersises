package com.hro.cmi;

import java.util.Map;

public class ErrorMeasurer
{
    //kinda shitty that even non-beta users have to supply dummy beta values
    public Map<Double, Tuple<Double, Double>> alphasBetasAndErrors;

    //just one method that returns both alpha and beta; getBestAlphaAndBeta(). 
    //and simply set both in Forecast. The children decide what they use.
    public Tuple<Double, Double> getBestAlphaAndBeta()
    {
        double bestAlpha = 0.0;
        double bestBeta = 0.0;

        double smallestErrorYet = Double.MAX_VALUE;          
        for (Map.Entry<Double, Tuple<Double,Double>> measurement : alphasBetasAndErrors.entrySet()) 
        {
            if(measurement.getValue().second < smallestErrorYet)
            {
                smallestErrorYet = measurement.getValue().second;
                bestAlpha = measurement.getKey();
                bestBeta = measurement.getValue().first;
            }
        }        
        return new Tuple<Double, Double>(bestAlpha, bestBeta);
    }
}

