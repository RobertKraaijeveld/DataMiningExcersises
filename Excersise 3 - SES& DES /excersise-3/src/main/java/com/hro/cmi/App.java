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
        background(220);
        fill(50,100);

        drawLegend();
        drawAxises();
        drawBaseValuesAndAxisesValues();


        drawSES(swordSalesPoints);    
        drawDES(swordSalesPoints);
    }

    private void drawLegend()
    {

    }

    private void drawAxises()
    {
        invertYAxis();
        
        stroke(0, 0, 0);

        //x axis 
        line(40, 30, 690, 30);   
        //y axis
        line(40, 30, 40, 600);           

        popMatrix();                    
    }

    private void drawBaseValuesAndAxisesValues()
    {
        double firstPointPosition = 30.0f;

        //X AXIS VALUES
        float positionStep = 0.0f;
        
        for(int i = 0; i < 37; i++)
        {
            if(i < 9)
                positionStep += 12.0f;
            else
                positionStep += 19.4f;
                
            text(i, (float) firstPointPosition + positionStep, 660);            
        }

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

        System.out.println("Final alpha for SES: " + sesForecast.alpha);
        System.out.println("Final error for SES: " + sesForecast.error);            
    }

    private void drawDES(ArrayList<Vector2> swordSalesPoints)
    {
        DES desForecast = new DES(swordSalesPoints, 11);
        desForecast.searchForBeta = true;

        ArrayList<Vector2> desSwordSalesPoints = desForecast.runForecastWithBestError();
        
        stroke(0, 128, 0);                                  
        fill(0, 128, 0);
        drawGivenVectors(desSwordSalesPoints);

        System.out.println("Final alpha for DES: " + desForecast.alpha);   
        System.out.println("Final beta for DES: " + desForecast.beta);
        System.out.println("Final error for DES: " + desForecast.error);    
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


    //temporarily inverting y values can be used because processings' y = 0 starts at the top left         
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
