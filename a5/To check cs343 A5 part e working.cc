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
    if(ballot==TallyVotes::Tour::Picture){pics++;} //Tally the vote no matter what.
    else{ statue++;}
    printer.print(id,Voter::States::Block,numNeededTask);
    bench.wait();
    printer.print(id,Voter::States::Unblock,numNeededTask);
    return static_cast<TallyVotes::Tour>(winner); //Return winner
}


void TallyVotes::main(){

    for(;;){
        _Accept(~TallyVotes){
            break;
        }or _When((numNeededTask++)!=group and !flag) _Accept(vote){
            if(numNeededTask==group){
                //I.e. all the voters in a group have cast the vote
                //Now we start signalling the blocked tasks,
                flag=true;//means we are starting a unwind of the stack
                winner=statue>pics;
                numNeededTask--;
                bench.signalBlock();
                if(numNeededTask==0){
                     pics=0;statue=0;
                     flag=false;
                }
            }
        }
       _Else{
            numNeededTask--;
            bench.signalBlock();
             if(numNeededTask==0){
                     pics=0;statue=0;
                     flag=false;
                }
        }
    }
}

