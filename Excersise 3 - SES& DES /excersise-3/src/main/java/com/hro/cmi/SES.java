package com.hro.cmi;

import java.util.ArrayList;
import java.util.Map;

class SES extends Forecast
{
    public SES(ArrayList<Vector2> originalVectors, int forecastAmount)
    {
        this.originalVectors = originalVectors;
        this.forecastAmount = forecastAmount;
        this.unforecastableVectorAmount = 1;
    }


    //the loop can be abstracted, only the formula needs to be specified
    @Override
    public ArrayList<Vector2> forecastFunction()
    {
        ArrayList<Vector2> smoothedVectors = new ArrayList<>();

        for (int i = 0; i < originalVectors.size(); i++) 
        {
             smoothedVectors.add(computeSESSmoothedVector(smoothedVectors, i));       
        }

        Vector2 lastSmoothedPoint = smoothedVectors.get(smoothedVectors.size() - 1);
        smoothedVectors.addAll(getSESForecast(lastSmoothedPoint));

        //debug
        for (int i = 0; i < originalVectors.size(); i++) 
        {
            System.out.println("originalVector = " + originalVectors.get(i).x + "," + originalVectors.get(i).y);
            System.out.println("SES smooth = " + smoothedVectors.get(i).x + "," + smoothedVectors.get(i).y);            
        }        
        return smoothedVectors;
    }
    private Vector2 computeSESSmoothedVector(ArrayList<Vector2> smoothedVectors, int position)
    {
        float originalVectorX = originalVectors.get(position).x;     
        float smoothedY; 

        if(position < unforecastableVectorAmount)
        {
            smoothedY = originalVectors.get(position).y;
            return new Vector2(originalVectorX, smoothedY);
        }
        else
        {
            //NOTE: Formula uses the Roberts (1959) rather than Hunter (1986). Both are equally valid.
            smoothedY = alpha * originalVectors.get(position).y + (1.0f - alpha) * smoothedVectors.get(position - 1).y;
            return new Vector2(originalVectorX, smoothedY);
        }   
    }

    private ArrayList<Vector2> getSESForecast(Vector2 lastSmoothedPoint)
    {
        ArrayList<Vector2> returnListToBeMerged = new ArrayList<>();
        for(int i = unforecastableVectorAmount; i < forecastAmount; i++)
        {
            Vector2 newPoint = new Vector2(lastSmoothedPoint.x + (i + 1), lastSmoothedPoint.y); 
            returnListToBeMerged.add(newPoint);
        }
        return returnListToBeMerged;
    } 


    @Override
    public float computeError(ArrayList<Vector2> vectors) 
    {
        float totalSESerror = 0.0f;
        for (int i = unforecastableVectorAmount; i < originalVectors.size(); i++) 
        {
            totalSESerror += Math.pow(2, (vectors.get(i).y - originalVectors.get(i).y)); 
        } 
        return (float) Math.sqrt(totalSESerror / (vectors.size() - unforecastableVectorAmount));
    }
}