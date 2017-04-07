package com.hro.cmi;

public class Triple<T, J, L>
{
    public T first;
    public J second;
    public L third;


    public Triple(){}

    public Triple(T first, J second, L third) 
    {
        this.first = first;
        this.second = second; 
        this.third = third;
    }
}
