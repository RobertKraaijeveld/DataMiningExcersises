package com.hro.cmi;

import processing.core.PApplet;
import processing.core.PImage;

import java.util.ArrayList;

public class App extends PApplet
{
    
    private static final int APPLET_WIDTH = 1040;
    private static final int APPLET_HEIGHT = 680;
    private ArrayList<Vector2> swordSalesPoints = Parser.parseCsvToPoints("/home/robert/Documents/Projects/DataMiningExcersises/Excersise 3 - SES& DES /excersise-3/docs/SwordForecasting.csv");
    
    private static final int YAXIS_OFFSET = 100;
    private static final int XAXIS_OFFSET = 18;
        

    public void setup() {
        noSmooth();
        noLoop();
        size(APPLET_WIDTH, APPLET_HEIGHT);
    }

    public void draw()
    {
        background(225, 225, 225);
        fill(0,0,0);

        drawAxises();

        drawBaseValuesAndAxisesValues();

        drawSES(swordSalesPoints);    
        drawDES(swordSalesPoints);

        drawLegend();
        
    }

    private void drawLegend()
    {
        textSize(16);

        fill(255, 0, 0);
        text("Red line: Original values", 550.0f, 90.0f);

        fill(0, 0, 255);
        text("Blue line: Single exponential smoothing", 550.0f, 120.0f);

        fill(0, 128, 0);
        text("Green line: Double exponential smoothing", 550.0f, 150.0f);

        textSize(40);
        fill(0,0,0);
        text("Forecast of sword sales", 10.0f, 100.0f);       

        textSize(9);
        text("Source: http://eu.wiley.com/WileyCDA/WileyTitle/productCd-111866146X.html", 10.0f, 115.0f);               
    }

    private void drawAxises()
    {
        invertYAxis();
        
        stroke(0, 0, 0);

        //x axis 
        line(40, 30, 920, 30);   
        //y axis
        line(40, 30, 40, 460);           

        popMatrix();                    
    }

    private void drawBaseValuesAndAxisesValues()
    {
        double firstPointPosition = 30.0f;

        //X axis values
        float positionStep = 0.0f;
        
        for(int i = 0; i < 49; i++)
        {
            if(i < 9)
                positionStep += 14.0f;
            else if (i > 35)
                positionStep += 16f;                
            else
                positionStep += 20f;
                
            textSize(9);
            text(i, (float) firstPointPosition + positionStep, 665);            
        }

        //Y axis values
        float valueStep = 145.0f;
        positionStep = 605.0f;

        for(int i = 0; i < 20; i++)
        {
            positionStep -= 20.0f;
            valueStep += 20.0f;

            text(Float.toString(valueStep), 0.0f, (float) firstPointPosition + positionStep);            
        }

        stroke(255, 0, 0);  
        fill(255, 0, 0);
                                        
        drawGivenVectors(swordSalesPoints);
    }

    private void drawSES(ArrayList<Vector2> swordSalesPoints)
    {
        SES sesForecast = new SES(swordSalesPoints, 11);
        ArrayList<Vector2> sesSwordSalesPoints = sesForecast.runForecastWithBestError();
        
        stroke(0, 0, 255);                                  
        fill(0, 0, 255);
        drawGivenVectors(sesSwordSalesPoints);

        textSize(18);
        fill(0, 0, 255);
        text("SES Measurements", 10.0f, 145.0f);

        textSize(13);
        fill(0,0,0);
        text("SES Alpha: " + Double.toString(sesForecast.alpha).substring(0, 6), 10.0f, 170.0f);
        text("SES Error: " + Double.toString(sesForecast.error).substring(0, 6), 10.0f, 185.0f);
    }

    private void drawDES(ArrayList<Vector2> swordSalesPoints)
    {
        DES desForecast = new DES(swordSalesPoints, 11);
        desForecast.searchForBeta = true;

        ArrayList<Vector2> desSwordSalesPoints = desForecast.runForecastWithBestError();
        
        stroke(0, 128, 0);                                  
        fill(0, 128, 0);
        drawGivenVectors(desSwordSalesPoints);

        textSize(18);
        fill(0, 128, 0);
        text("DES Measurements", 200.0f, 145.0f);

        textSize(13);
        fill(0,0,0);
        text("DES Alpha: " + Double.toString(desForecast.alpha).substring(0, 6), 200.0f, 170.0f);
        text("DES Beta: " + Double.toString(desForecast.beta).substring(0, 6), 200.0f, 185.0f);   
        text("DES Error: " + Double.toString(desForecast.error).substring(0, 6), 200.0f, 200.0f);   
        
    }

    private void drawGivenVectors(ArrayList<Vector2> vectors)
    {
        double leftPadding = 40.0f;        
        double firstPointXposition = 40.0f;
        Vector2 previousPointVector = new Vector2(firstPointXposition, 120.0f);

        for (Vector2 currentVector : vectors) 
        {
            double shiftedXValue = (currentVector.x * XAXIS_OFFSET) + leftPadding;
            double shiftedYValue = currentVector.y - YAXIS_OFFSET;

            //inverting so we dont have to map/flip the y values
            invertYAxis();
           
            ellipse((float) shiftedXValue, (float) shiftedYValue, 5.0f, 5.0f);
           
            if(previousPointVector.x != firstPointXposition)
                line((float) previousPointVector.x, (float) previousPointVector.y, (float) shiftedXValue, (float) shiftedYValue);

            previousPointVector.x = shiftedXValue; 
            previousPointVector.y = shiftedYValue;

            popMatrix();
        }
    }


    //temporarily inverting y values is used because processings' y = 0 starts at the top left         
    private void invertYAxis()
    {
        pushMatrix();
        translate(0, height);
        scale(1,-1);
    }

    public static void main( String[] args )
    {
         PApplet.main(new String[] { App.class.getName() });
    }
}
