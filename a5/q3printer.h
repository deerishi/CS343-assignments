#ifndef PRINT_H
#define PRINT_H
#endif

#ifndef TALLY_H
#include "q3tallyVotes.h"
#define TALLY_H
#endif

#ifndef VOTER_H
#include "q3voter.h"
#define VOTER_H
#endif

#ifndef STD
#include<iostream>
using namespace std;
#define STD
#endif


_Monitor Printer {      // chose one of the two kinds of type constructor
     unsigned int voters;
     //Defining a
     struct Buffer{ //Buffer which hold the state of a task during voting
         bool filled; //Is state beging overwrittern
         Voter::States state; //Current state to update
         TallyVotes::Tour voted;//voted tour
         unsigned int numBlocked;//number of blocked tasks


     };

     Buffer *information; //Array of voter states
     void  flushInformation(); //To print the buffer when overwritten
  public:
     Printer( unsigned int voters );
    void print( unsigned int id, Voter::States state );
    void print( unsigned int id, Voter::States state, TallyVotes::Tour vote );
    void print( unsigned int id, Voter::States state, unsigned int blocked );

    ~Printer();
};
