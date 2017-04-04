package com.hro.cmi;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.Map;
import java.util.stream.Collectors;
import java.util.HashMap;


public class Forecasting
{
    public static ArrayList<Vector2> originalVectors;

    public static ArrayList<Vector2> runSESWithBestAlpha(ArrayList<Vector2> originalVectors)
    {
        Forecasting.originalVectors = originalVectors;

        //make these static?
        boolean useDES = false;
        boolean useForecasting = true;

        float bestAlpha = getKeyWithSmallestValue(createErrorCombinations(useDES).alphasAndErrors, useDES);
        return getSES(bestAlpha, useForecasting);
    }   


    /*
    SINGLE EXPONENTIAL SMOOTHING AND FORECASTING
    */

    private static ArrayList<Vector2> getSES(float alpha, boolean useForecasting)
    {
        ArrayList<Vector2> returnList = new ArrayList<>();

        for (int i = 0; i < originalVectors.size(); i++) 
        {
            //go beyond i, a specified amount, the value at that forecast time is just the last smooth point, but a time series further
            if(i == 0)
            {
                returnList.add(i, originalVectors.get(i));
            }
            else
            {
                //X is a time series so we dont smooth it
                float originalVectorX = originalVectors.get(i).x;

                float smoothedY = alpha * originalVectors.get(i - 1).y + (1.0f - alpha) * returnList.get(i - 1).y;

                returnList.add(i, new Vector2(originalVectorX, smoothedY));
            }
        }

        if(useForecasting)
        {
            Vector2 lastVector = returnList.get(returnList.size() - 1);
            ArrayList<Vector2> forecastedVectors = getSESForecast(lastVector, 5);

            forecastedVectors.stream()
                         .forEach(x -> returnList.add(x));

        }
        return returnList;
    }

    private static ArrayList<Vector2> getSESForecast(Vector2 lastSmoothedPoint, int amountOfTimeUnitsToForecast)
    {
        ArrayList<Vector2> returnListToBeMerged = new ArrayList<>();
        for(int i = 0; i < amountOfTimeUnitsToForecast; i++)
        {
            //i + 1 since a amountOfTimeUnitsToForecast = 1 would mean i = 0 which means no forecast at all
            Vector2 newPoint = new Vector2(lastSmoothedPoint.x + (i + 1), lastSmoothedPoint.y); 
            returnListToBeMerged.add(newPoint);
        }
        return returnListToBeMerged;
    }

    // AND * (st-1 + b t - 1)
        

    /*
     FINDING ALPHA AND BETA
    */


    //split this function up?
    //make a single, 3 way map. we want stuff like a = 0.01 b = 0.5 e = 5 etc so we can see all possible combinations.
    private static ForecastingError createErrorCombinations(boolean useDES)
    {
        Map<Float, Float> alphasAndErrors = new HashMap<Float, Float>();
        Map<Float, Float> betasAndErrors = new HashMap<Float, Float>();
        
        for(float alpha = 0.0f; alpha < 1.0f; alpha += 0.01f)
        {
            boolean useForecasting = false;
            ArrayList<Vector2> smoothedVectors = getSES(alpha, useForecasting);
            alphasAndErrors.put(alpha, computeSESError(smoothedVectors));

            /*            
            if(useDES)
            {
                //extract?
                for(float beta = 0.0f; beta < 1.0f; beta += 0.01f)
                {
                    ArrayList<Vector2> trendSmoothedVectors = getDESTrendSmoothing(beta, trendSmoothedVectors);
                    betasAndErrors.put(beta, computeDESError(smoothedVectors, trendSmoothedVectors));                
                }
            }*/
        }
        return new ForecastingError(alphasAndErrors, betasAndErrors);
    }

    //list sizes have to be equal, enforce this 1      
    private static float computeDESError(ArrayList<Vector2> smoothedVectors, ArrayList<Vector2> trendSmoothedVectors)
    {
        float totalDESerror = 0.0f;        
        for(int i = 0; i < smoothedVectors.size(); i++)
        {
            totalDESerror += Math.pow(2, (smoothedVectors.get(i).y - trendSmoothedVectors.get(i).y));
        }
        return (float) Math.sqrt(totalDESerror / (smoothedVectors.size() - 2));        
    }

    //list sizes have to be equal, enforce this 2
    private static float computeSESError(ArrayList<Vector2> smoothedVectors) 
    {
        float totalSESerror = 0.0f;
        for (int i = 0; i < smoothedVectors.size(); i++) 
        {
            totalSESerror += Math.pow(2, (smoothedVectors.get(i).y - originalVectors.get(i).y)); 
        } 
        return (float) Math.sqrt(totalSESerror / (smoothedVectors.size() - 1));
    }

    private static float getKeyWithSmallestValue(Map<Float, Float> floatMap, boolean useDES)
    {
        Float keyWithSmallestValue = 0.0f; 
        Float smallestValueYet = Float.MAX_VALUE;

        //get alpha with smallest error measure         
        for (Map.Entry<Float, Float> kvPair : floatMap.entrySet()) 
        {
            if(kvPair.getValue() < smallestValueYet)
            {
                smallestValueYet = kvPair.getValue();
                keyWithSmallestValue = kvPair.getKey();
            }    
        }
        return keyWithSmallestValue;
    }
}






//when using the maps, check if they are filled
class ForecastingError                                 
{
    public Map<Float, Float> alphasAndErrors;
    public Map<Float, Float> betasAndErrors;

    public ForecastingError(Map<Float, Float> alphas, Map<Float, Float> betas)
    {
        alphasAndErrors = alphas;
        betasAndErrors = betas;
    }    
}