#define TALLY_H
#ifndef SEM_H
#include <uSemaphore.h>
#define SEM_H
#endif

#ifndef BAR_H
#include <uBarrier.h>
#define BAR_H
#endif
 _Monitor Printer;


#if defined( IMPLTYPE_MC )            // mutex/condition solution
// includes for this kind of vote-tallier
class TallyVotes {


    bool barging; //flag to indicate barging
    uCondLock notFull; //Condition lock to block when a group has not yet voted
    uCondLock barge; //Barging queue
    uOwnerLock mutex; //For Mutual Exclusion
    unsigned int numBlocked; //Number of blocked tasks
    unsigned int numNeeded;


    /*--------------------EOD for MC-------------------*/

    // private declarations for this kind of vote-tallier
#elif defined( IMPLTYPE_SEM )         // semaphore solution
// includes for this kind of vote-tallier

    class TallyVotes {
    // private declarations for this kind of vote-tallier
    uSemaphore entry;//For mutual Exclusion
    uSemaphore oneGroupInProcess;//For blocking barging
    uSemaphore groupWait;//For waiting on the group

    unsigned int numNeededSem;//Number of tasks needed to complete a group
    bool bargingSem;//Barging Flag


        /*-----------------EOD FOR SEM----------------*/




#elif defined( IMPLTYPE_BAR )         // barrier solution
// includes for this kind of vote-tallier
_Cormonitor TallyVotes : public uBarrier {
    // private declarations for this kind of vote-tallier
    unsigned int numNeededBar;//
    void block(); // to block the task
    void resetBarrier();
    unsigned int getWaiters(); //to get the number of waiting tasks
      /*-----------------EOD FOR BAR----------------*/

#else
    #error unsupported voter type
#endif
    // common declarations
    unsigned int group;
    Printer &printer;
    unsigned int pics,statue;
    bool winner;
  public:                             // common interface
    TallyVotes( unsigned int group, Printer &printer );
    enum Tour { Picture, Statue };
    Tour vote( unsigned int id, Tour ballot );
};
