


#ifndef PRINT_H
#include "q2printer.h"
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



//Defining the constructor for the type MC. This has a barging flag
TallyVotes::TallyVotes( unsigned int group, Printer &printer ):barging(false),numBlocked(0),numNeeded(0),group(group),printer(printer),pics(0),statue(0){}

TallyVotes::Tour TallyVotes:: vote( unsigned int id, Tour ballot ){
    mutex.acquire();

    //Checking for barging task
    if(barging){
        //printing Barging status
        printer.print(id,Voter::States::Barging);
        barge.wait(mutex);
    }

    numNeeded++;
    //Now we vote
    if(ballot==TallyVotes::Tour::Picture){
        pics++;
    }
    else{
        statue++;
    }
    //If group is not full
    if(numNeeded!=group){
        //Release barging task
        if(!barge.empty()){
            barge.signal();
        }
        else{
            barging=false;
        }
        //Printing blocking message
        printer.print(id,Voter::States::Block,numNeeded);
        notFull.wait(mutex);
        numNeeded--;
        //Printing unblocking message
        printer.print(id,Voter::States::Unblock,numNeeded);
     }
     else{
        printer.print(id,Voter::States::Complete);
        numNeeded--;
        //winner=statue>pics;

     }
    //Finding the result of the election
   TallyVotes::Tour winner=TallyVotes::Tour::Picture;
    if(statue>pics){
        winner=TallyVotes::Tour::Statue;
    }

    if(numNeeded==0){
        //Meaning that this was the last task that was waiting for the results of the group
        pics=0;
        statue=0;
    }
    //Check if any task is waiting on the mutex queue
    if(!notFull.empty()){
        barging=true;
        notFull.signal();
    }
    else if(!barge.empty()){ //Release any barging task
        barge.signal();
    }
    else{
        barging=false;
    }

    mutex.release();
    return winner;
}
