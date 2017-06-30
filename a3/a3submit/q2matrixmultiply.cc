#include "q2matrixmultiply.h"
#ifndef CHECK
#define CHECK 1
#include<iostream>
#include<cctype>
#include<cstdio>
#include <fstream>
#include<iomanip>
#include<vector>
using namespace std;
#endif



void matrixmultiply( int *Z[], int *X[], unsigned int xr, unsigned int xc, int *Y[], unsigned int yc );

void uMain::main()
{
    ul xrows,xcolYrows,ycols;
    ifstream xfile,yfile;
    bool fileInp=false;
    switch ( argc ) 
    {
        case 1:
        case 2:
        case 3:  cout<<"Usage: ./matrixmultiply xrows (> 0)  xycols (> 0)  ycols (> 0)  [ x-matrix-file  y-matrix-file ]\n";exit(0);
        case 4: xrows=atoi(argv[1]); xcolYrows=atoi(argv[2]) ; ycols=atoi(argv[3]); break;
        case 5: cout<<"Usage: ./matrixmultiply xrows (> 0)  xycols (> 0)  ycols (> 0)  [ x-matrix-file  y-matrix-file ]\n";exit(0);
        case 6: xrows=atoi(argv[1]); xcolYrows=atoi(argv[2]) ; ycols=atoi(argv[3]);
                try
                {
                    xfile.open(argv[4]);
                    
                }
                catch(...)
                {
                    cout<<"Error! Cannot open y-matrix input-file "<<argv[5]<<"\nUsage: ./matrixmultiply xrows (> 0)  xycols (> 0)  ycols (> 0)  [ x-matrix-file  y-matrix-file ]";
                    exit(0);
                }
                try
                {
                    yfile.open(argv[5]);
                    
                }
                catch(...)
                {
                    cout<<"Error! Cannot open y-matrix input-file "<<argv[6]<<"\nUsage: ./matrixmultiply xrows (> 0)  xycols (> 0)  ycols (> 0)  [ x-matrix-file  y-matrix-file ]";
                    exit(0);
                }
                fileInp=true;
                break;
    }
    if(xrows<=0 or xcolYrows<=0 or ycols<=0)
    {
        cout<<"Usage: ./matrixmultiply xrows (> 0)  xycols (> 0)  ycols (> 0)  [ x-matrix-file  y-matrix-file ]\n";exit(0);
    }
    //cout<<xrows<<","<<xcolYrows<<","<<ycols<<","<<fileInp<<"\n";
    uProcessor p[xrows-1] __attribute__((unused));
    //Now we allocate arrays; 
    int **x=new int*[xrows];
    int **y=new int*[xcolYrows];
    int **z=new int*[xrows];
    //cout<<"hi\n";
    //Now we allocate the arrays columns;
    ul i,j;
    For(i,0,xrows)
    {
        x[i]=new int[xcolYrows];
        z[i]=new int[ycols];
    }
    For(i,0,xcolYrows)
    {
        y[i]=new int[ycols];
    }
    
    //now take the input for the arrays
    int val;
    For(i,0,xrows)
    {
        For(j,0,xcolYrows)
        {
            if(fileInp) 
                xfile>>val;
            else
                val=37;
            x[i][j]=val;
        }
    }
    For(i,0,xcolYrows)
    {
        For(j,0,ycols)
        {
            if(fileInp)
                yfile>>val;
            else
                val=37;
            y[i][j]=val;
        }
    }
    //Now input is complete , now do the multiplication
    //cout<<"now printing x\n";printMatrix(x,xrows,xcolYrows);
    //cout<<"\n now printing y \n";printMatrix(y,xcolYrows,ycols);cout<<"\n";
    
    //Now we will multiply matrices
    matrixmultiply( z, x, xrows-1,  xcolYrows, y, ycols );
    //cout<<"\n now printing the result Z\n";
    //printMatrix(z,xrows,ycols);cout<<"\n";
    if(fileInp)
    printOutput(x, xrows, xcolYrows,y,ycols,z);
    //now we have dynamically allcated the arrays, now delete them , but remember you have to print them too;
    For(i,0,xrows)
    {
        delete [] x[i];
        delete [] z[i];
    }
    For(i,0,xcolYrows)
    {
        delete [] y[i];
    } 
    delete [] x;
    delete [] y;
    delete [] z;
}
