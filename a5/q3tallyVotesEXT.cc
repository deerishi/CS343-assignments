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

//File for External Scheduling using Monitor

TallyVotes::TallyVotes( unsigned int group, Printer &printer ):numNeededExt(0),group(group),printer(printer),pics(0),statue(0){}

TallyVotes::Tour TallyVotes:: vote( unsigned int id, Tour ballot ){

     printer.print(id,Voter::States::Vote,ballot);
    if(ballot==TallyVotes::Tour::Picture){ //Tally the vote no matter what. Also Monitor has explicit barging protection
        pics++;
    }
    else{
        statue++;
    }
    numNeededExt++;
    if(numNeededExt==group){ //i.e. that this is the last task arriving on the queue
        printer.print(id,Voter::States::Complete);
         winner=statue>pics;
    }
    else{
         printer.print(id,Voter::States::Block,numNeededExt);
        //Block untill all the voters in the group have voted
         _Accept(vote); //Recursive  vote Blocking
    }
    numNeededExt--;
     printer.print(id,Voter::States::Unblock,numNeededExt);
     if(numNeededExt==0){
        pics=0;statue=0; //Resetting for the next group
        }

    return static_cast<TallyVotes::Tour>(winner); //Return winner

}
