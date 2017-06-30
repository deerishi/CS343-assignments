
#include "q1binsertsort.h"
#ifndef CHECK
#define CHECK 1
#include<iostream>
#include<cctype>
#include<cstdio>
#include <fstream>
#include<vector>
using namespace std;
#endif


void uMain::main()
{     
    int num,x,i   ;
    
    ifstream unsorted;
    
    ofstream sorted;
    
    bool fileOut=false;;
    
    vector<int> arr;
    switch ( argc ) {
    case 1: 
            cout<<"Usage: ./binsertsort_INT unsorted-file [ sorted-file ]\n";
            exit(0);
    case 2: 
            try{
            unsorted.open(argv[1]);
                
                break;
            }
            catch(...){
            cout << "Error! Could not open input file \""<<argv[1]<<"\"\n"; 
            cout<<"Usage: ./binsertsort_INT unsorted-file [ sorted-file ]\n";
            exit(0);
            }
    
    case 3: 
            try{
            unsorted.open(argv[1]);
                
            }
            catch(...){
            cout << "Error! Could not open input file \""<<argv[1]<<"\"\n"; 
            cout<<"Usage: ./binsertsort_INT unsorted-file [ sorted-file ]\n";
            exit(0);
            }
            
            
            try{
            sorted.open(argv[2]);
                fileOut=true;
                break;
            }
            catch(...){
            cout << "Error! Could not open output file \""<<argv[2]<<"\"\n"; 
            cout<<"Usage: ./binsertsort_INT unsorted-file [ sorted-file ]\n";
            exit(0);
            }
    
    };
    
    
    
    while(1)
    {
        unsorted>>num;
        
        if(unsorted.eof()) break;
        _Coroutine Binsertsort<int> f1(SENTINEL);
        if(num==0)
        {
            if(fileOut )
            sorted<<"\n\n\n";
            else
            cout<<"\n\n\n";
            
            continue;    
        }
        arr.clear(); 
        for(i=0;i<num;i++)
        {
            unsorted>>x;
            arr.push_back(x);    
        }
        for(i=0;i<num;i++)
        {
            if(fileOut )
            sorted<<arr[i]<<" ";
            else
            cout<<arr[i]<<" ";
        }
        
        if(fileOut )
            sorted<<"\n";
            else
            cout<<"\n";
        for(i=0;i<int(arr.size());i++)
        {
            f1.sort(arr[i]);
        }
        f1.sort(SENTINEL);

        for(i=0;i<num;i++)
        {
            x=f1.retrieve();
            
          if(fileOut )
            sorted<<x<<" ";
            else
            cout<<x<<" ";
        }
        if(fileOut )
            sorted<<"\n\n";
            else
            cout<<"\n\n";
        
        
    }
}



