package com.hro.cmi;

import java.util.ArrayList;
import java.util.Map;

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
    public boolean searchForBeta;
    protected double alpha = 0.0;
    protected double beta = 0.0;


    /*
    ABSTRACT METHODS
    */

    public abstract ArrayList<Vector2> forecastFunction();
    public abstract double computeError(ArrayList<Vector2> vectors);
    

    /*
    COMMON METHODS
    */


    //TO FIX: Beta is not always used by a child
    public ArrayList<Vector2> runForecastWithBestError()
    {
        ErrorMeasurer em = getErrorMeasurements();
        Tuple<Double, Double> bestAlphaAndBeta = em.getBestAlphaAndBeta();

        this.alpha = bestAlphaAndBeta.first;
        this.beta = bestAlphaAndBeta.second;

        resultVectors = forecastFunction(); 
        return resultVectors;
    }


    /*
    ERROR COMPUTATION
    */

    public abstract ErrorMeasurer getErrorMeasurements();
}