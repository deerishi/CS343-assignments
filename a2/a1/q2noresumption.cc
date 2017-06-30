#include <iostream>
#include<functional>
#include <sys/types.h>
#include <unistd.h>
using namespace std;


void f( int &i,std::function<void (int &)> handler ) {
    cout << "f " << i << endl;
    if ( rand() % 5 == 0 ) handler(i),f(i,handler);              // require correction ?
    
    i -= 1;
    if ( 0 < i ) f( i,handler );                            // recursion
    
}
int main(int argc, const char *argv[]) {
    int times = 25, seed = getpid();
    switch ( argc ) {
      case 3: seed = atoi( argv[2] );                   // allow repeatable experiment
      case 2: times = atoi( argv[1] );                  // control recursion depth
      case 1: break;                                    // defaults
      default: cerr << "Usage: " << argv[0] << " times seed" << endl; exit( EXIT_FAILURE );
    }
    srand( seed );     
    auto lambda1=[](int &i)->void{cout << "f handler " <<i<<endl;i-=1;};// fixed or random seed
    int i=times;
    cout<<"f "<<i<<endl;
    if(rand()%5==0)
    {
        cout << "root " << i<<endl;
    }
    i-=1;
    if(i>0) f(i,lambda1);
    return 0;
}
