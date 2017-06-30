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

TallyVotes::TallyVotes( unsigned int group, Printer &printer ):uBarrier(group),numNeededBar(group),group(group),printer(printer),pics(0),statue(0){}

void TallyVotes::block(){
    uBarrier::block();
}

void TallyVotes::resetBarrier(){
    uBarrier::reset(group);
}

unsigned int TallyVotes::getWaiters(){
    return uBarrier::waiters();
}
TallyVotes::Tour TallyVotes::vote( unsigned int id, Tour ballot){

    //First we print out the vote
     printer.print(id,Voter::States::Vote,ballot);

    if(ballot==TallyVotes::Tour::Picture){
        pics++;
    }
    else{
        statue++;
    }
    if(getWaiters()!=group-1){
        printer.print(id,Voter::States::Block,getWaiters()+1);
    }
    block(); //Block for synchronization
    if(numNeededBar==group){
        //This means that the election is complete
         printer.print(id,Voter::States::Complete);
    }

    //keep track of how many tasks have been unblocked
    numNeededBar--;

    winner=statue>pics;

     printer.print(id,Voter::States::Unblock,numNeededBar);
     if(numNeededBar==0){
         pics=0;
         numNeededBar=group;
         statue=0;
         resetBarrier();
     }
      return static_cast<TallyVotes::Tour>(winner);

}
