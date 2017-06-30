#include<iostream>
#include<cctype>
#include<cstdio>
#include <fstream>
#include<vector>
#include<map>
#include <utility> 
#include<unistd.h>
#include "PRNG.h"
using namespace std;
#define CHECK 1
PRNG prng;
typedef unsigned int ui;

class Potato {
    // YOU ADD MEMBERS HERE
    unsigned int ticks;
  public:
    _Event Explode {}; //exception that would be thrown
    Potato( unsigned int maxTicks = 10 ) 
    {
        Potato::ticks=(unsigned int)prng(1,maxTicks);
        if(Potato::ticks>1) cout<<"\n  POTATO goes off after "<<ticks<<" tosses\n";
        else cout<<"\n  POTATO goes off after "<<ticks<<" toss\n";
        //Potato::ticks=maxTicks;
    }
    void reset( unsigned int maxTicks = 10 )
    {
        Potato::ticks=(unsigned int)prng(1,maxTicks); //setting the ticks for the hot potato
        if(Potato::ticks>1)   cout<<"  POTATO goes off after "<<ticks<<" tosses\n";
        else  cout<<"  POTATO goes off after "<<ticks<<" toss\n";
    }
    void countdown()
    {
        ticks--;
        if(ticks==0)
        {
           
            _Throw Explode(); ///exception thrown, to be catched later in order to handle it.
            
        } 
    }
};

/*--------------Start of class declerations for Umpire and player-------------------*/

_Coroutine Player; //Forward Decleration of the Coroutine

_Coroutine Umpire {
    // YOU ADD MEMBERS HERE
    map<unsigned int,Player*> &map1;
    //Potato potato;
    int sizeMap;
    unsigned int  playerToBeDeleted;
    unsigned int getRandPlayerToTossTo();
    void main();
  public:
    Umpire( map<unsigned int,Player*> &players ): map1(players),sizeMap(players.size()){}
    void set( unsigned int player );
    void printMap();
    
};

_Coroutine Player {
    // YOU ADD MEMBERS HERE
    Umpire &ump;
    unsigned int Id;
    Potato *playerPotato;
    map<unsigned int,Player*> &playersMap;
    unsigned int getRandPlayerToTossTo2();
    void main();
  public:
    typedef map<unsigned int,Player*> PlayerList; // container type of your choice
    Player( Umpire &umpire, unsigned int Id, PlayerList &players ):ump(umpire),Id(Id),playersMap(players){}
    void toss( Potato &potato );
    void pprintMap();
};

/*--------------Start of routines for Umpire-------------------*/
void Umpire:: set(ui player)
{
    playerToBeDeleted=player;
    resume();
}

void Umpire::printMap()
{
    for(auto it=map1.begin();it!=map1.end();it++)
    {
        cout<<it->first<<","<<it->second<<"\n";
    }
}

ui Umpire:: getRandPlayerToTossTo()
{
    ui rn=prng(0,map1.size()-1);
    ui idToReturn,i;
    i=0;
    for(auto it=map1.begin();it!=map1.end(),i<=rn;i++,it++)
    {
        idToReturn=it->first;i=i;
    }
    return idToReturn;
}

/*--------------End of routines for Umpire-------------------*/
    
/*--------------Start of routines for Player-------------------*/

void Player::pprintMap()
{
    for(auto it=playersMap.begin();it!=playersMap.end();it++)
    {
        cout<<it->first<<","<<it->second<<"\n";
    }
}

ui Player::getRandPlayerToTossTo2()
{
    ui rn=prng(0,playersMap.size()-1);
    ui idToReturn,i=0;
    for(auto it=playersMap.begin();it!=playersMap.end(),i<=rn;it++,i++)
    {
        idToReturn=it->first;i=i;
    }
    if(idToReturn!=Id)
    {
        return idToReturn;
    }
    rn=(rn+1)%playersMap.size();
    i=0;
    for(auto it=playersMap.begin();it!=playersMap.end(),i<=rn;it++,i++)
    {
        idToReturn=it->first;
    }
    return idToReturn;
}

void Player::toss(Potato &potato)
{
    playerPotato=&potato;
    resume();
}

/*--------------End of routines for Player-------------------*/

bool checkString(char *str)
{
    int i;
    for(i=0;str[i]!='\0';i++)
    {
        //cout<<"str["<<i<<"] is  "<<str[i]<<"\n";
        if(!isdigit(str[i]))
        {
            return false;
        }
    }
    return true;
}
/*--------------helper function to check the validity for argv[1]-------------------*/

