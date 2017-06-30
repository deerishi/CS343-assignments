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

//File for Java Monitor Internal Scheduling with Barging using Monitor

/*Custom wait and signal functions for uCondition variable*/
/*-------------------------------------------------------*/


void TallyVotes::wait() {
    bench.wait();                      // wait until signalled
    while ( rand() % 5 == 0 ) {        // multiple bargers allowed
        _Accept( vote ) {              // accept barging callers
        } _Else {                      // do not wait if no callers
        } // _Accept
    } // while
}

void TallyVotes::signalAll() {
    while ( ! bench.empty() ) bench.signal(); // drain the condition
}

/*EOD for Custom wait and signal functions for uCondition variable*/
/*-------------------------------------------------------*/



TallyVotes::TallyVotes( unsigned int group, Printer &printer ):numNeededIntB(0),counter(0),group(group),printer(printer),pics(0),statue(0){}

TallyVotes::Tour TallyVotes:: vote( unsigned int id, Tour ballot ){

    if(counter%group!=0){ //Barging condition
        printer.print(id,Voter::States::Barging,ballot);
        wait();
    }

    printer.print(id,Voter::States::Vote,ballot);//Print voting status
    if(ballot==TallyVotes::Tour::Picture){ //Tally the vote no matter what.
        pics++;
    }
    else{
        statue++;
    }
    numNeededIntB++;
    if(numNeededIntB==group){
        printer.print(id,Voter::States::Complete);
        winner=statue>pics;
        counter++;
        signalAll();
    }
    else{
        printer.print(id,Voter::States::Block,numNeededIntB);
        wait();//Block untill all the voters in the group have voted
        counter++;
    }
    numNeededIntB--;
    printer.print(id,Voter::States::Unblock,numNeededIntB);
    winner=statue>pics;
    if(numNeededIntB==0){
        pics=0;statue=0;
        signalAll();
    }




 return static_cast<TallyVotes::Tour>(winner); //Return winner
}
