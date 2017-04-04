package com.hro.cmi;

import processing.core.PApplet;
import processing.core.PImage;

import java.util.ArrayList;

public class App extends PApplet
{
    private static final int APPLET_WIDTH = 1040;
    private static final int APPLET_HEIGHT = 680;

    //do maggis code 'challenge': box and triangle in console
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
        drawBaseValues();
    }

    private void drawLegend()
    {
        text("str1", 10, 10);    
    }

    private void drawAxises()
    {
        invertYAxis();
        
        stroke(0, 0, 0);

        //x axis           
        line(40, 120, 590, 120);   

        //y axis
        line(40, 120, 40, 320);           

        popMatrix();                    
    }

    private void drawBaseValues()
    {
        ArrayList<Vector2> swordSalesPoints = Parser.parseCsvToPoints("/home/robert/Documents/Projects/DataMiningExcersises/Excersise 3 - SES& DES /excersise-3/docs/SwordForecasting.csv");
                         

        //duplication :/
        float leftPadding = 40.0f;        
        float firstPointXposition = 40.0f;
        Vector2 previousPointVector = new Vector2(firstPointXposition, 120.0f);


        //extract to drawLegend or something
        for (Vector2 currentVector : swordSalesPoints) 
        {
            float shiftedXValue = (currentVector.x * 15) + leftPadding;
            float shiftedYValue = currentVector.y;

            textSize(10);
            text(Math.round(currentVector.x), shiftedXValue - 3, 575);
        }

        stroke(255, 0, 0);                                  
        fill(255, 0, 0);
        drawGivenVectors(swordSalesPoints);
        

        ArrayList<Vector2> smoothedSwordSalesPoints = Forecasting.runSESWithBestAlpha(swordSalesPoints);
        stroke(0, 0, 255);                                  
        fill(0, 0, 255);
        drawGivenVectors(smoothedSwordSalesPoints);
    }

    private void drawGivenVectors(ArrayList<Vector2> vectors)
    {
        float leftPadding = 40.0f;        
        float firstPointXposition = 40.0f;
        Vector2 previousPointVector = new Vector2(firstPointXposition, 120.0f);

        for (Vector2 currentVector : vectors) 
        {
            float shiftedXValue = (currentVector.x * 15) + leftPadding;
            float shiftedYValue = currentVector.y;

            //inverting so we dont have to map/flip the y values
            invertYAxis();
           
            ellipse(shiftedXValue, shiftedYValue, 5.0f, 5.0f);
           
            if(previousPointVector.x != firstPointXposition)
                line(previousPointVector.x, previousPointVector.y, shiftedXValue, shiftedYValue);

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
