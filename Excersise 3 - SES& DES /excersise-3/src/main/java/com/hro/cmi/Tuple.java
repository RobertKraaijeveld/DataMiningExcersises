package com.hro.cmi;

public class Tuple<T, J>
{
    public T first;
    public J second;


    public Tuple(){}

    public Tuple(T first, J second) 
    {
        this.first = first;
        this.second = second; 
    }
}
