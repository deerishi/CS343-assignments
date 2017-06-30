
#define VOTER_H

#ifndef TALLY_H
#include "q3tallyVotes.h"
#define TALLY_H
#endif

_Monitor Printer;

_Task Voter {
    unsigned int id;
    TallyVotes &voteTallier; Printer &printer;
    void main();
  public:
    enum States { Start = 'S', Vote = 'V', Block = 'B', Unblock = 'U', Barging = 'b',Complete = 'C', Finished = 'F' };

    Voter( unsigned int id, TallyVotes &voteTallier, Printer &printer );
};


/*-------End of Voter Header*/
