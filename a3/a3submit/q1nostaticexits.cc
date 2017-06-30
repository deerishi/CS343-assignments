#include <cstdlib>                    // atoi
#include <iostream>
using namespace std;

// volatile prevents dead-code removal
void do_work( int C1, int C2, int C3, int L1, int L2, volatile int L3 ) {
    int f1=1,f2=1,f3=1;
    int i=0,j=0,k=0;
    
    //for ( int i = 0; i < (L1); i += 1 ) 
    while(i<L1)
    {
        f2=1;
        j=0;
        if(1&f1){
#ifndef NOOUPUT
        cout << "S1 i:" << i << endl;
#endif
        //for ( int j = 0; j < (L2); j += 1 )
         while(j<L2)
         {
            f3=1;
            k=0;
            if(1&f1&f2){
#ifndef NOOUPUT
            cout << "S2 i:" << i << " j:" << j << endl;
#endif            //for ( int k = 0; k < (L3); k += 1 ) 
            while(k<L3)
            {
                if(1&f1&f2&f3){ 
#ifndef NOOUPUT
                cout << "S3 i:" << i << " j:" << j << " k:" << k << " : ";
#endif
                //if ( C1 ) goto EXIT1;
                if(C1) f1=0;
                
                if(f1==1)
                {
#ifndef NOOUPUT
                    cout << "S4 i:" << i << " j:" << j << " k:" << k << " : ";
#endif
                    //if ( C2 ) goto EXIT2;
                    if(C2) f2=0;
                    
                    if(f2==1)
                    {
#ifndef NOOUPUT
                        cout << "S5 i:" << i << " j:" << j << " k:" << k << " : ";
#endif         
                        //if ( C3 ) goto EXIT3;
                        if(C3) f3=0;
                        
                        if(f3==1){
#ifndef NOOUPUT
                        cout << "S6 i:" << i << " j:" << j << " k:" << k << " : ";
#endif           
                        }
                    }

                }
            }
            k+=1;
            } //for
          //EXIT3:;
            if(f2&1&f1) {
#ifndef NOOUPUT
            cout << "S7 i:" << i << " j:" << j << endl;
#endif        
        }
        }
        j+=1;
        } //for
      //EXIT2:;
    
        if(f1&1) {
#ifndef NOOUPUT
        cout << "S8 i:" << i << endl;
#endif        
        }

    }
    i+=1;
    } // for
  //EXIT1:;
} // do_work

int main( int argc, char *argv[] ) {
    int times = 1, L1 = 10, L2 = 10, L3 = 10;
    switch ( argc ) {
      case 5:
        L3 = atoi( argv[4] );
        L2 = atoi( argv[3] );
        L1 = atoi( argv[2] );
        times = atoi( argv[1] );
        break;
      default:
        cerr << "Usage: " << argv[0] << " times L1 L2 L3" << endl;
        exit( EXIT_FAILURE );
    } // switch

    for ( int i = 0; i < times; i += 1 ) {
        for ( int C1 = 0; C1 < 2; C1 += 1 ) {
            for ( int C2 = 0; C2 < 2; C2 += 1 ) {
                for ( int C3 = 0; C3 < 2; C3 += 1 ) {
                //cout<<"\t\ncalling "<<C1<<","<<C2<<","<<C3<<"\n";
                    do_work( C1, C2, C3, L1, L2, L3 );
#ifndef NOOUPUT
                    cout << endl;
#endif
                } // for
            } // for
        } // for
    } // for
} // main
