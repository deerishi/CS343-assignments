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

//Defining the constructor for the type SEM. This has a barging flag
TallyVotes::TallyVotes(unsigned int group, Printer &printer ):entry(1),oneGroupInProcess(1),groupWait(0),numNeededSem(0),group(group),printer(printer),pics(0),statue(0){}

TallyVotes::Tour TallyVotes::vote( unsigned int id, Tour ballot ){

    if(oneGroupInProcess.counter()<=0 and !groupWait.empty()){
        printer.print(id,Voter::States::Barging);//Print barging message if any voter other than the blocked Voter tries to barge in
    }

    oneGroupInProcess.P();//To eliminate barging

    entry.P();//To provide Mutual Exclusion

    numNeededSem++;

    printer.print(id,Voter::States::Vote,ballot);
    if(ballot==TallyVotes::Tour::Picture){
        pics++;
    }
    else{
        statue++;
    }

    if(numNeededSem!=group){//Means more tasks needed for the group
        printer.print(id,Voter::States::Block,numNeededSem);
        oneGroupInProcess.V();//Allow more tasks
        entry.V();//Remove Mutual Exclusion
        groupWait.P();//Block the task
        numNeededSem--;
        entry.P();//Reacquire the lock to ensure Mutual Exclusion
        printer.print(id,Voter::States::Unblock,numNeededSem);
    }
    else{//Means one group has completed Voting, so we can calculate the result
         printer.print(id,Voter::States::Complete);
         numNeededSem--;
         winner=statue>pics; //Bool Value to store the winner

    }
    //NOw release other tasks which might be waiting to get the result
    if(!groupWait.empty()){
        //Means we have waiting tasks
        groupWait.V();
        //Here we do not V the oneGroupInProcess, since we want all the voters in a group to get their results first
    }
    else{
        //Allow other group to Vote
        pics=0;
        statue=0;
        oneGroupInProcess.V();
    }
    entry.V();
     return static_cast<TallyVotes::Tour>(winner);
}
