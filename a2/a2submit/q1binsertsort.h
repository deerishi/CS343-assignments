#include<iostream>
#include<cctype>
#include<cstdio>
#include<vector>
#include <fstream>
#define CHECK 1
using namespace std;

template<typename T> _Coroutine Binsertsort {
    const T Sentinel;            // value denoting end of set
    T value;                     // communication: value being passed down/up the tree
    void main() 
    {
        _Coroutine Binsertsort less(Sentinel),greater(Sentinel);
        int pivot=value;
        int l=pivot,r=pivot;
        //cout<<"pivot is "<<pivot<<"\n";
        //if(pivot==Sentinel) return;
        suspend();
        while(value!=Sentinel)
        {
            if(value < pivot)
            {
                less.sort(value);
            }
            else if(value>pivot)
            {
                greater.sort(value);
            }
            suspend();
        }
        less.sort(Sentinel);
        greater.sort(Sentinel);
        suspend();
        if(pivot!=Sentinel)
        {
            while(l!=Sentinel)
            {
                l=less.retrieve();
                if(l==Sentinel )
                {
                    break;
                }
                value=l;
                suspend();
            }
            value=pivot;
            suspend();
            while(r!=Sentinel)
            {
                r=greater.retrieve();
                if(r==Sentinel )
                {
                    break;
                }
                value=r;
                suspend();
            }
           
        }
        value=Sentinel;
        
        
    }                // YOU WRITE THIS ROUTINE
  public:
    Binsertsort( T Sentinel ) : Sentinel( Sentinel ) {}
    void sort( T value ) {       // value to be sorted
        Binsertsort::value = value;
        resume();
    }
    T retrieve() {               // retrieve sorted value
        resume();
        return value;
    }
};
