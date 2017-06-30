#include <iostream>
#include <cstdlib>
using namespace std;
#include <unistd.h>				// getpid
#include<string.h>
#include<setjmp.h>

#ifdef NOOUTPUT
#define print( x )
#else
#define print( x ) x
#endif

static  jmp_buf globalBuf;

#define Try(buf) if(!setjmp(buf))
#define Catch else
#define Throw longjmp(globalBuf,1)
struct E {};

long int freq = 5;

long int Ackermann( long int m, long int n ) 
{
    //cout<<"In Ackermann with "<<m<<","<<n<<"\n";
    jmp_buf  buf1,buf2;
	if ( m == 0 ) 
	{
		if ( random() % freq == 0 )  Throw;
		
		//cout<<" m,n = "<<m<<","<<n<<" ,Now returning "<<n+1<<"\n";
		return n + 1;
	} 
	else if ( n == 0 ) 
	{
		if ( random() % freq == 0 )  Throw;
		
		Try(buf1) 
		{
		    //printf( "Setjmp1 in call frame %p\n", (void*)&buf1 );
		    
		    memcpy(globalBuf,buf1,sizeof(jmp_buf));
		    //cout<<"in try 1 with m,n = "<<m<<","<<n<<" Calling ac1 with m-1,n = "<<m-1<<","<<n<<"\n";
		    long int x=Ackermann( m - 1, 1 );
			//cout<<"in try1 done with ac1 returned with x= "<<x<<"\n";
			return x;
		} 
		Catch 
		{
		    //printf( "Entering call1 from longjmp frame %p\n", buf1 );
		    //cout<<"In catch1 with m,n = "<<m<<","<<n<<"\n";
			//print( cout << "E1 " << m << " " << n << endl );
		} // try
	} 
	else 
	{
		Try(buf2) 
		{
		    //printf( "Setjmp2 in call frame %p\n", (void*)&buf2 );
		    memcpy(globalBuf,buf2,sizeof(jmp_buf));
		    //cout<<"In try2 with m,n ="<<m<<","<<n<<" calling recursive nested ac2 with m,n-1 = "<<m<<","<<n-1<<"\n";
		    long int x1=Ackermann( m, n - 1 );
		    memcpy(globalBuf,buf2,sizeof(jmp_buf));
		    //cout<<"(m,n) = "<<m<<","<<n<<" Done with first now calling recursive case returned with x1 = "<<x1<<" now calling second with m-1,x1 = "<<m-1<<","<<x1<<"\n";
		    long int x2=Ackermann( m - 1,  x1);
		    //cout<<"(m,n) = "<<m<<","<<n<<" done with second case retured with x2 = "<<x2<<"\n";
			return x2;
		} 
		Catch 
		{
		    //printf( "Entering call2 from longjmp frame %p\n", buf2 );
		    //cout<<"In catch2 with m,n = "<<m<<","<<n<<"\n";
			//print( cout << "E2 " << m << " " << n << endl );
		} // try
	} // if
	//printf("Now returning 0 \n");
	return 0;	// recover by returning 0
}

int main( int argc, const char *argv[] ) 
{
    jmp_buf bufMain;
	long int Ackermann( long int m, long int n );
	
	long int m = 4, n = 6, seed = getpid();	// default values

	switch ( argc ) 
	{
	  case 5: freq = atoi( argv[4] );
	  case 4: seed = atoi( argv[3] );
	  case 3: n = atoi( argv[2] );
	  case 2: m = atoi( argv[1] );
	} // switch
	
	srandom( seed );
	
	cout << m << " " << n << " " << seed << " " << freq << endl;
	
	Try(bufMain) 
	{
	    //printf( "SetjmpMain in call frame %p\n", (void*)&bufMain );
	    memcpy(globalBuf,bufMain,sizeof(jmp_buf));
		cout << Ackermann( m, n ) << endl;
	} 
	Catch 
	{
	     //printf( "EnteringMain call from longjmp frame %p\n", (void*)&bufMain );
		//print( cout << "E3" << endl );
	} // try
}
