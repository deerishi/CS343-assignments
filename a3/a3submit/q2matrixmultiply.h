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
    ul start,xrows,xcolYrows,ycols;
    int **x,**y,**z; 
    //For each task xrow signifies the row number of the matrix X and matrix Z, we start from the last row and create tasks exponentially 
    // i.e. for each previous row we create a task
    void mul(ul mid){
        ul i,j;
            For(i,0,ycols)
            {
                z[mid][i]=0;
                For(j,0,xcolYrows)
                {
                    z[mid][i]+=(x[mid][j]*y[j][i]);
                }
                //cout<<"z["<<xrows<<"]["<<i<<"] is "<<z[xrows][i]<<"\n";
            }
            
    }
    void main()
    {
    
        ul mid=(start+xrows)/2;
        if(start==xrows){
           mul(mid);
        }
        else if(mid+1==xrows and start==mid){//means 2 rows
            MultiplyMatrices t1(mid+1,xrows,xcolYrows,ycols,x,y,z);
            mul(mid);
        }
        else{
            MultiplyMatrices t1(mid+1,xrows,xcolYrows,ycols,x,y,z);
            MultiplyMatrices t2(start,mid-1,xcolYrows,ycols,x,y,z);
            mul(mid);
        }       
    
    }
    public:
    MultiplyMatrices(ul start,ul xrows,ul xcolYrows,ul ycols,int **x,int **y,int **z) : start(start),xrows(xrows),xcolYrows(xcolYrows),ycols(ycols),x(x),y(y),z(z) {}
};

void matrixmultiply( int *Z[], int *X[], unsigned int xr, unsigned int xc, int *Y[], unsigned int yc )
{
    //Now this is matix multiply, we will create tasks recursilly and only print out the lat row
    MultiplyMatrices t1(0,xr,xc,yc,X,Y,Z);
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
        cout<<setw(xc*9+4)<<"|";
        For(j,0,yc)
        {
            cout<<setw(9)<<y[i][j];
        }
        cout<<" \n";
    }
    For(i,0,1)
    {
        For(j,0,xc*9+3)
        cout<<"-";
        if(i==0)
        cout<<"*";
        For(j,0,9*yc+1)
        cout<<"-";
    }
    cout<<"\n";
    For(i,0,xr)
    {
        For(j,0,xc){
        if(j==0)
        cout<<setw(8)<<x[i][j];
        else
        cout<<setw(9)<<x[i][j];
        }
        cout<<setw(5)<<"|";
        
        For(j,0,yc)
        cout<<setw(9)<<z[i][j];
        cout<<" \n";
    }
}
