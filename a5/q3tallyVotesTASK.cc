#ifndef PRINT_H
#include "q3printer.h"
#define PRINT_H
#endif

#ifndef STD
#include<iostream>
using namespace std;
#define STD
#endif

#ifndef MPRNG_H
#define MPRNG_H
#include "MPRNG.h"
#endif

//File for Automatic Signal Scheduling with Barging using Monitor




TallyVotes::TallyVotes( unsigned int group, Printer &printer ):numNeededTask(0),group(group),printer(printer),pics(0),statue(0){}

TallyVotes::Tour TallyVotes:: vote( unsigned int id, Tour ballot ){

     printer.print(id,Voter::States::Vote,ballot);//Print voting status
    if(ballot==TallyVotes::Tour::Picture){ //Tally the vote no matter what.
        pics++;
    }
    else{
        statue++;
    }
    numNeededTask++;
    printer.print(id,Voter::States::Block,numNeededTask);
    if(numNeededTask==group){
        printer.print(id,Voter::States::Complete);
    }
    bench.wait();
    numNeededTask--;
    printer.print(id,Voter::States::Unblock,numNeededTask);
    if(numNeededTask!=0){
        bench.signal();
    }
    return static_cast<TallyVotes::Tour>(winner); //Return winner
}


void TallyVotes::main(){

    for(;;){
        _Accept(~TallyVotes){
            break;
        }or _Accept(vote){
            if(numNeededTask==group){
                //I.e. all the voters in a group have cast the vote
                //Now we start signalling the blocked tasks,
                winner=statue>pics;
                bench.signalBlock();
                pics=0;statue=0;
            }
        }
    }
}
