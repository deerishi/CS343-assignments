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




TallyVotes::TallyVotes( unsigned int group, Printer &printer ):numNeededAUTO(0),group(group),printer(printer),pics(0),statue(0){}

TallyVotes::Tour TallyVotes:: vote( unsigned int id, Tour ballot ){

     printer.print(id,Voter::States::Vote,ballot);//Print voting status
    if(ballot==TallyVotes::Tour::Picture){ //Tally the vote no matter what. Also Monitor has implicit barging protection
        pics++;
    }
    else{
        statue++;
    }
    numNeededAUTO++;
    //Checking for the Waituntil condition which is if all voters have voted or not

    flag=(numNeededAUTO==group);
    WAITUNTIL(flag,printer.print(id,Voter::States::Block,numNeededAUTO), printer.print(id,Voter::States::Unblock,numNeededAUTO-1))

    if(numNeededAUTO==group){ //Checking for completion
         printer.print(id,Voter::States::Complete);
         winner=statue>pics;
    }


    numNeededAUTO--; //Decrementing the number of blocked tasks
    if(numNeededAUTO==0){
        pics=0;statue=0;
    }


    RETURN(static_cast<TallyVotes::Tour>(winner)); //Return winner
}
