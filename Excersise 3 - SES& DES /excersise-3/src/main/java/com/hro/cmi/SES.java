package com.hro.cmi;

import java.util.ArrayList;
import java.util.Set;

class SES extends Forecast
{
    public SES(ArrayList<Vector2> originalVectors, int forecastAmount)
    {
        this.originalVectors = originalVectors;
        this.forecastAmount = forecastAmount;
        this.unforecastableVectorAmount = 1;
    }


    //rename
    @Override
    public ArrayList<Vector2> forecastFunction()
    {
        ArrayList<Vector2> smoothedVectors = new ArrayList<>();

        Vector2 firstOriginal = originalVectors.get(0);
        smoothedVectors.add(firstOriginal);

        for (int i = 1; i < originalVectors.size() + 1; i++) 
        {
             smoothedVectors.add(computeSESSmoothedVector(smoothedVectors, i));       
        }
        Vector2 lastSmoothedPoint = smoothedVectors.get(smoothedVectors.size() - 1);
        smoothedVectors.addAll(getSESForecast(lastSmoothedPoint));

        return smoothedVectors;
    }
    private Vector2 computeSESSmoothedVector(ArrayList<Vector2> smoothedVectors, int position)
    {
        double originalVectorX;
        double smoothedY; 

            /* NOTE: The implemented Formula uses the Hunter (1986) rather than Roberts (1959) method. 
               The latter is more correct since it does not 'skip' the first position,
               (which is especially noticable with alpha = 1), but it does not work with the error function.
                smoothedY = alpha * originalVectors.get(position).y + (1.0f - alpha) * smoothedVectors.get(position - 1).y; 
            */

        if(position == originalVectors.size())
        {
            originalVectorX = originalVectors.get(position - 1).x + 1;             
            smoothedY = alpha * originalVectors.get(position - 1).y + (1.0f - alpha) * smoothedVectors.get(position - 1).y;              
        }
        else
        {
            originalVectorX = originalVectors.get(position).x;                 
            smoothedY = alpha * originalVectors.get(position - 1).y + (1.0f - alpha) * smoothedVectors.get(position - 1).y;      
        }
        return new Vector2(originalVectorX, smoothedY);
    }

    private ArrayList<Vector2> getSESForecast(Vector2 lastSmoothedPoint)
    {
        ArrayList<Vector2> returnListToBeMerged = new ArrayList<>();
        for(int i = 0; i < forecastAmount; i++)
        {
            Vector2 newPoint = new Vector2(lastSmoothedPoint.x + (i + 1), lastSmoothedPoint.y); 
            returnListToBeMerged.add(newPoint);
        }
        return returnListToBeMerged;
    } 


    /* 
    ERROR MEASURING
    */

    @Override
    public ErrorMeasurer getErrorMeasurements()
    {
        ErrorMeasurer em = new ErrorMeasurer();        
        ArrayList<Triple<Double, Double, Double>> alphasBetasAndErrors = new ArrayList<>();

        for(double alpha = 0.01f; alpha < 1.0f; alpha += 0.01f)
        {
            double placeHolderBetaValue = 0.0f;
            this.alpha = alpha;

            ArrayList<Vector2> smoothedVectors = this.forecastFunction();
            alphasBetasAndErrors.add(new Triple(alpha, placeHolderBetaValue, computeError(smoothedVectors)));
        }
        em.alphasBetasAndErrors = alphasBetasAndErrors;
        return em;
    }

    @Override
    public double computeError(ArrayList<Vector2> vectors) 
    {
        double totalSESerror = 0.0f;
        for (int i = unforecastableVectorAmount; i < originalVectors.size(); i++) 
        {
            totalSESerror += Math.pow((vectors.get(i).y - originalVectors.get(i).y), 2); 
        } 
        return (double) Math.sqrt(totalSESerror / (vectors.size() - unforecastableVectorAmount));
    }
}