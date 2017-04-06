package com.hro.cmi;

import java.util.ArrayList;
import java.util.Map;
import java.util.HashMap;
import java.util.function.Function;


public abstract class Forecast
{
    //make sure these are used by the forecast function
    public int unforecastableVectorAmount = 2;
    public int forecastAmount = 5; 

    //Fix: A extension forecast is also a forecast! THen we can make the extension set its resultVectors to whatever, and then those
    //together with the appropriate funcs will be used..  
    public ArrayList<Vector2> originalVectors = new ArrayList<>();
    public ArrayList<Vector2> resultVectors = new ArrayList<>();   

    //this will be alpha or beta in SES/DES and will be used by the forecastFunction
    protected float alpha = 0.0f;

    /*
    ABSTRACT METHODS
    */

    public abstract ArrayList<Vector2> forecastFunction();
    public abstract float computeError(ArrayList<Vector2> vectors);
    

    /*
    COMMON METHODS
    */


    //TO FIX: Flaw with beta/alpha combos
    public ArrayList<Vector2> runForecastWithBestError()
    {
        this.alpha = 0.7f; // getKeyWithSmallestValue(getErrorCombinations());

        resultVectors = forecastFunction(); 
        return resultVectors;
    }


    /*
    ERROR COMPUTATION
    */

    private Map<Float, Float> getErrorCombinations()
    {
        Map<Float, Float> errorCombination = new HashMap<>();

        for(float alpha = 0.0f; alpha < 1.0f; alpha += 0.01f)
        {
            //TO FIX make this cleaner. Now we have to modify members for testing :/
            this.alpha = alpha;

            ArrayList<Vector2> smoothedVectors = forecastFunction();
            errorCombination.put(alpha, computeError(smoothedVectors));
        }
        return errorCombination;
    }



    /* IS THIS POSSIBLE? AS IN, ONLY DEFINING THE FORMULA
    private Float computeError()
    {
        float totalError = 0.0f;        
        for(int i = 0; i < resultVectors.size(); i++)
        {
            //not sure if this is possible
            totalError += errorFunction();
        }
        return (float) Math.sqrt(totalError / (resultVectors.size() - unforecastableVectorAmount));
    }*/

    //error function is faulty
    private float getKeyWithSmallestValue(Map<Float, Float> floatMap)
    {
        System.out.println("getKeyWithSmallestValue");
        Float keyWithSmallestValue = 0.0f; 
        Float smallestValueYet = Float.MAX_VALUE;

        for (Map.Entry<Float, Float> kvPair : floatMap.entrySet()) 
        {
            System.out.println("Looking at alpha " + kvPair.getKey() + " has error " + kvPair.getValue());            
            if(kvPair.getValue() < smallestValueYet)
            {
                smallestValueYet = kvPair.getValue();
                keyWithSmallestValue = kvPair.getKey();
            }    
        }
        System.out.println("Best alpha is " + keyWithSmallestValue);
        return keyWithSmallestValue;
    }
}