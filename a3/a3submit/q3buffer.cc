#include "q3buffer.h"
#ifndef CHECK
#define CHECK 1
#include<iostream>
#include<cctype> 
#include<cstdio>
#include <fstream>
#include<queue>
#include<vector>
using namespace std;
#endif

void uMain::main(){
    //cout<<"hi::umain()\n";
    int cons=5,prods=3,produce=10,bufferSize=10,delays=cons+prods,i;
    switch(argc){
        case 2 : cons=atoi(argv[1]);delays=cons+prods; break;
        case 3 : cons=atoi(argv[1]); prods=atoi(argv[2]);delays=cons+prods;break;
        case 4 : cons=atoi(argv[1]); prods=atoi(argv[2]);produce=atoi(argv[3]);delays=cons+prods;break;
        case 5 : cons=atoi(argv[1]); prods=atoi(argv[2]);produce=atoi(argv[3]);bufferSize=atoi(argv[4]);delays=cons+prods;break;
        case 6: cons=atoi(argv[1]); prods=atoi(argv[2]);produce=atoi(argv[3]);bufferSize=atoi(argv[4]);delays=atoi(argv[5]);break;
    }
    int sum=0;
    if(cons<=0 or prods<=0 or produce<=0 or bufferSize<=0 or delays<=0)
    {
        cout<<"Usage: ./buffer [ Cons (> 0) [ Prods (> 0) [ Produce (> 0) [ BufferSize (> 0) [ Delay (> 0) ] ] ] ] ]\n";
        exit(0);
    }
    #ifdef __U_MULTI__
        uProcessor p[3] __attribute__((unused));
    #endif
    //cout<<"delay is "<<delays<<"\n";
    BoundedBuffer<int> buffer(bufferSize);
    Producer *producers[prods];
    Consumer *consumers[cons];
    for(i=0;i<prods;i++){ 
        producers[i]=new Producer(buffer,produce,delays);
    }
    
    for(i=0;i<cons;i++){
        consumers[i]=new Consumer(buffer,delays,SENTINEL,sum);
    }
    for(i=0;i<prods;i++){
        delete producers[i];
    }

    for(i=0;i<cons;i++){
        buffer.insert(SENTINEL);
    }
    cout<<"total: "<<sum<<"\n";
    for(i=0;i<cons;i++){
        delete consumers[i];
    }
}
