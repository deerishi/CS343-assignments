#ifndef VOTER_H
#include "q2voter.h"
#define VOTER_H
#endif


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
#include "MPRNG.h"
#endif

Voter:: Voter( unsigned int id, TallyVotes &voteTallier, Printer &printer):id(id),voteTallier(voteTallier),printer(printer){}

void Voter::main(){
    //Yield randomly so that all tasks do not start at the same time
    yield(mprng(19));

    printer.print(id,Voter::States::Start);
     TallyVotes::Tour winner=TallyVotes::Tour::Picture;
    yield(1);

    //Now the task votes
    unsigned int rn=mprng(1); //generate a random number between 0 and 1 for Picture/Statue
    TallyVotes::Tour winner1=TallyVotes::Tour::Picture;
    if(rn==1){//Statue selected
        //printer.print(id,Voter::States::Vote,TallyVotes::Tour::Statue);
        winner1=voteTallier.vote(id,TallyVotes::Tour::Statue);
    }
    else{//Voting for Picture
        //printer.print(id,Voter::States::Vote,TallyVotes::Tour::Picture);
         winner1=voteTallier.vote(id,TallyVotes::Tour::Picture);
    }
    yield(1);

    //Printing the result
    printer.print(id,Voter::States::Finished,winner1);
}
