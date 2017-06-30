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


//File for Internal Scheduling using Monitor


TallyVotes::TallyVotes( unsigned int group, Printer &printer ):numNeededInt(0),group(group),printer(printer),pics(0),statue(0){}

TallyVotes::Tour TallyVotes:: vote( unsigned int id, Tour ballot ){
    printer.print(id,Voter::States::Vote,ballot);//Print voting status
    if(ballot==TallyVotes::Tour::Picture){ //Tally the vote no matter what. Also Monitor has implicit barging protection
        pics++;
    }
    else{
        statue++;
    }
    numNeededInt++;
    if(numNeededInt==group){
        printer.print(id,Voter::States::Complete);
        winner=statue>pics;
        internalQueue.signal(); //Start unblocking as the group votes have been cast
    }
    else{
        printer.print(id,Voter::States::Block,numNeededInt);
        internalQueue.wait();//Block untill all the voters in the group have voted
    }
    numNeededInt--;
     printer.print(id,Voter::States::Unblock,numNeededInt);
    if(numNeededInt!=0){

         internalQueue.signal();//continue to unblock
    }
    else{
        pics=0;statue=0; //Resetting for the next group
    }


    return static_cast<TallyVotes::Tour>(winner); //Return winner
}
