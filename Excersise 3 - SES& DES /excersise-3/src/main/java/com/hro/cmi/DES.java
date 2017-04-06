package com.hro.cmi;

import java.awt.print.Paper;
import java.util.ArrayList;

public class DES extends Forecast
{
    private float beta;
    private ArrayList<Vector2> trendSmoothedVectors = new ArrayList<>();

    public DES(ArrayList<Vector2> originalVectors, int forecastAmount, float beta)
    {
        this.originalVectors = originalVectors;
        this.forecastAmount = forecastAmount;

        //TODO: ALSO FIND THE BEST AMOUNT FOR THIS IN computeError
        this.beta = beta;
        
        this.unforecastableVectorAmount = 2;
    }


    //Note to self; this is st    
    //the loop can be abstracted, only the formula needs to be specified
    @Override
    public ArrayList<Vector2> forecastFunction()
    {
        ArrayList<Vector2> smoothedVectors = new ArrayList<>();

        for (int i = 0; i < originalVectors.size(); i++) 
        {
            smoothedVectors.add(computeSmoothedVector(smoothedVectors, i));
            this.trendSmoothedVectors.add(computeTrendSmoothedVector(smoothedVectors, i));
        }
        Vector2 lastSmoothedVector = smoothedVectors.get(smoothedVectors.size() - 1);
        Vector2 lastTrendSmoothedVector = this.trendSmoothedVectors.get(this.trendSmoothedVectors.size() - 1);        

        smoothedVectors.addAll(getDESForecast(lastSmoothedVector, lastTrendSmoothedVector));
        return smoothedVectors;
    }

    private ArrayList<Vector2> getDESForecast(Vector2 lastSmoothedVector, Vector2 lastTrendSmoothedVector)
    {
        ArrayList<Vector2> forecastedVectors = new ArrayList<>();

        for(int i = 0; i < forecastAmount; i++)
        {
            //check if correct
            float forecastedValue = lastSmoothedVector.y + (i * lastTrendSmoothedVector.y);
            forecastedVectors.add(new Vector2(lastSmoothedVector.x + (i), forecastedValue));
        }
        return forecastedVectors;
    }

    private Vector2 computeSmoothedVector(ArrayList<Vector2> smoothedVectors, int position)
    {
        float originalVectorX = originalVectors.get(position).x;     
        float smoothedY; 

        if(position <= unforecastableVectorAmount)
        {
            System.out.println("position = " + position + " which is smaller than " + unforecastableVectorAmount);
            smoothedY = originalVectors.get(position).y;
            return new Vector2(originalVectorX, smoothedY);
        }
        else
        {
            //X is a time series so we dont smooth it
            smoothedY = this.alpha * originalVectors.get(position).y + (1 - this.alpha)
                       * (smoothedVectors.get(position - 1).y + this.trendSmoothedVectors.get(position - 1).y);

            return new Vector2(originalVectorX, smoothedY);
        }
    }

    private Vector2 computeTrendSmoothedVector(ArrayList<Vector2> smoothedVectors, int position)
    {
        float originalVectorX = originalVectors.get(position).x;
        float smoothedY = smoothedVectors.get(position).y;
        
        if(position < unforecastableVectorAmount)
        {
            if (position > 1)
            {
                float placeHolderForUnsmoothable = originalVectors.get(unforecastableVectorAmount).y 
                                                            - originalVectors.get(unforecastableVectorAmount - 1).y;

                return new Vector2(originalVectorX, placeHolderForUnsmoothable);
            }
            else
                return new Vector2(originalVectorX, smoothedY);
        }
        else
        {
            //X is a time series so we dont smooth it
            float combinedSmoothAndTrendValueForecast = beta * (smoothedVectors.get(position).y - smoothedVectors.get(position - 1).y)
                                                      + (1.0f - beta) * this.trendSmoothedVectors.get(position - 1).y;

            return new Vector2(originalVectorX, combinedSmoothAndTrendValueForecast);
        }
    }

    //error is WAY too high

    /*
        float totalSESerror = 0.0f;
        for (int i = 0; i < originalVectors.size(); i++) 
        {
            totalSESerror += Math.pow(2, (vectors.get(i).y - originalVectors.get(i).y)); 
        } 
        return (float) Math.sqrt(totalSESerror / (vectors.size() - unforecastableVectorAmount));
    */

    @Override
    public float computeError(ArrayList<Vector2> smoothedVectors) 
    {
        float totalDESerror = 0.0f;
        for (int i = 2; i < originalVectors.size(); i++) 
        {
            float combinedSmoothAndTrendValue = smoothedVectors.get(i).y + trendSmoothedVectors.get(i).y;
            totalDESerror += Math.pow(2, (combinedSmoothAndTrendValue - originalVectors.get(i).y)); 
        }   
        totalDESerror = totalDESerror / (originalVectors.size() - unforecastableVectorAmount); 
        return (float) Math.sqrt(totalDESerror);
    }
}