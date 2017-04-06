package com.hro.cmi;

import java.util.ArrayList;
import java.util.Scanner;
import java.io.File;
import java.security.KeyStore.TrustedCertificateEntry;

class Parser
{
    //Do note that this is a very simple parser for this use case only, please dont use it in any serious way.
    public static ArrayList<Vector2> parseCsvToPoints(String fileLocationString)
    {
        ArrayList<Vector2> returnList = new ArrayList<>();
        try 
        {
            Scanner scanner = new Scanner(new File(fileLocationString));
            
            //ignoring headers
            scanner.nextLine();

            while (scanner.hasNextLine()) 
            {
                String line = scanner.nextLine(); 
                line = line.replace("\"", "");

                String[] delimiterSeparatedLine = line.split(",");

                double x = Double.parseDouble(delimiterSeparatedLine[0]);
                double y = Double.parseDouble(delimiterSeparatedLine[1]);

                returnList.add(new Vector2(x, y));                    
            }
            scanner.close();                
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
        return returnList;
    }
}