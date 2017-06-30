#include<iostream>
#include<cctype>
#include<cstdio>
#include<vector>
#include <fstream>
#include<iomanip>
#define CHECK 1
using namespace std;
typedef unsigned int ul;

#define blank putc_unlocked('\n',stdout);
#define ForIter( it,name) for(auto it=name.begin();it!=name.end();it++)
#define Forall(i,start,end) for(i=start;i<=end;i++)
#define For(i,start,end) for(i=start;i<end;i++)
_Task MultiplyMatrices{
    ul xrows,xcolYrows,ycols;
    int **x,**y,**z; 
    //For each task xrow signifies the row number of the matrix X and matrix Z, we start from the last row and create tasks exponentially 
    // i.e. for each previous row we create a task
    void main()
    {
        if(xrows<0) return;
       
        
        ul i,j;
        For(i,0,ycols)
        {
            z[xrows][i]=0;
            For(j,0,xcolYrows)
            {
                z[xrows][i]+=(x[xrows][j]*y[j][i]);
            }
            //cout<<"z["<<xrows<<"]["<<i<<"] is "<<z[xrows][i]<<"\n";
        }
        
        if(xrows >0) 
        {
            MultiplyMatrices t1(xrows-1,xcolYrows,ycols,x,y,z);
        }
        if(xrows>1)
        {
            MultiplyMatrices t2(xrows-2,xcolYrows,ycols,x,y,z);
        }
    
    }
    public:
    MultiplyMatrices(ul xrows,ul xcolYrows,ul ycols,int **x,int **y,int **z) : xrows(xrows),xcolYrows(xcolYrows),ycols(ycols),x(x),y(y),z(z) {}
};

void matrixmultiply( int *Z[], int *X[], unsigned int xr, unsigned int xc, int *Y[], unsigned int yc )
{
    //Now this is matix multiply, we will create tasks recursilly and only print out the lat row
    MultiplyMatrices t1(xr,xc,yc,X,Y,Z);
    //cout<<"hi babe\n";
}

void printMatrix(int **a,ul x,ul y)
{
    ul i,j;
    For(i,0,x)
    {
        For(j,0,y)
        {
            cout<<a[i][j]<<" ";
        }
        cout<<"\n";
    }
}

void printOutput(int **x,ul xr,ul xc,int **y,ul yc,int**z)
{
    //first print y
    ul i,j;
    For(i,0,xc)
    {
        cout<<setw(31)<<"|";
        For(j,0,yc)
        {
            cout<<setw(10)<<y[i][j];
        }
        cout<<"\n";
    }
    For(i,0,2)
    {
        For(j,0,30)
        cout<<"-";
        if(i==0)
        cout<<"*";
    }
    cout<<"\n";
    For(i,0,xr)
    {
        For(j,0,xc)
        cout<<setw(10)<<x[i][j];
        cout<<"|";
        
        For(j,0,yc)
        cout<<setw(10)<<z[i][j];
        cout<<"\n";
    }
}
