#define TALLY_H

#include "AutomaticSignal.h"
 _Monitor Printer;

#include "uC++.h"


#if defined( IMPLTYPE_EXT )            // external scheduling monitor solution
// includes for this kind of vote-tallier
_Monitor TallyVotes {
    // private declarations for this kind of vote-tallier


    unsigned int numNeededExt; //Number of voters needed to complete a group



    /*-----------------------EOD FOR EXTernal Monitor---------------------------------------*/


#elif defined( IMPLTYPE_INT )          // internal scheduling monitor solution
// includes for this kind of vote-tallier
_Monitor TallyVotes {
    // private declarations for this kind of vote-tallier


    unsigned int numNeededInt; //Number of voters needed to complete a group
    uCondition internalQueue; //Internal Queue for scheduling


    /*-----------EOD for Internal Scheduling-----------------*/



#elif defined( IMPLTYPE_INTB )         // internal scheduling monitor solution with barging
// includes for this kind of vote-tallier
_Monitor TallyVotes {
    // private declarations for this kind of vote-tallier

    unsigned int numNeededIntB;
    unsigned int counter;
    uCondition bench;                  // only one condition variable (you may change the variable name)
    void wait();                       // barging version of wait
    void signalAll();                  // unblock all waiting tasks

    /*--------------EOD for INTB-------------------*/



#elif defined( IMPLTYPE_AUTO )         // automatic-signal monitor solution
// includes for this kind of vote-tallier
_Monitor TallyVotes {
    // private declarations for this kind of vote-tallier
    AUTOMATIC_SIGNAL; //uCondition queue
    unsigned int numNeededAUTO;
    bool flag;//Signalling flag

    /*---------------EOD for AUTOmatic SIGNALLING------------------*/

#elif defined( IMPLTYPE_TASK )         // internal/external scheduling task solution
_Task TallyVotes {
    // private declarations for this kind of vote-tallier
    unsigned int numNeededTask;
    uCondition bench;//Condition queue for blocking voters
    bool flag;//TO maximize the concurrency
    void main();


    /*----------------------EOD for TASK----------------------*/


#else
    #error unsupported voter type
#endif
    // common declarations
    unsigned int group; //Group Size
    Printer &printer;
    unsigned int pics,statue; //Current number of picture votes and statue votes
    bool winner; //To keep track of winner of each group

  public:                              // common interface
    TallyVotes( unsigned int group, Printer &printer );
    enum Tour { Picture, Statue };
    Tour vote( unsigned int id, Tour ballot );
};
