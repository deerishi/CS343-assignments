#include "q2hotpotato.h"
#ifndef CHECK
#define CHECK 1
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
#endif
#define blank putc_unlocked('\n',stdout);
#define ForIter(it,name) for(it=name.begin();it!=name.end();it++)
#define Forall(i,start,end) for(i=start;i<=end;i++)
#define For(i,start,end) for(i=start;i<end;i++)

void Umpire::main()
{
    ui setNum=1;
    Potato potato;
    //potato.reset();
    ui nextPlayerToTossTo=getRandPlayerToTossTo();
    //ui nextPlayerToTossTo=3;
    cout<<"Set "<<setNum<<":	U";
    setNum++;
    
    map1[nextPlayerToTossTo]->toss(potato);
    while(1)
    {
        cout<<" is eliminated\n";
        auto it=map1.find(playerToBeDeleted);
        Player *temp=it->second;
        delete temp;
        map1.erase(it);
        if(map1.size()==1)
        {
            cout<<map1.begin()->first<<" wins the Match!\n";
            Player *temp=map1.begin()->second;
            delete temp;
            map1.erase(map1.begin());
            break;
        }
        //nextPlayerToTossTo=getRandPlayerToTossTo();
        potato.reset();
        nextPlayerToTossTo=getRandPlayerToTossTo();
        cout<<"Set "<<setNum<<":	U";
        setNum++;
        map1[nextPlayerToTossTo]->toss(potato);
    }
}

void Player::main()
{
    while(1)
    {
        try
        {
            cout<<" -> "<<Id;
            //ui nextPlayerToTossTo=getRandPlayerToTossTo2();
            playerPotato->countdown();
            ui nextPlayerToTossTo=getRandPlayerToTossTo2();
            playersMap[nextPlayerToTossTo]->toss(*playerPotato);
        }
        catch(Potato::Explode &e)
        {
            ump.set(Id);
        }
    }
}



void uMain::main()
{
    

     unsigned int seed=getpid();
     unsigned int num;
     map<unsigned int,Player*> map1;
    Umpire ump1(map1);
      
    switch ( argc ) {
    case 1: 
            cout<<"Usage: ./hotpotato number-of-players (2 <= and <= 20) [ random-seed (>= 0) ]\n";
            //perror("Usage: ./hotpotato number-of-players (2 <= and <= 20) [ random-seed (>= 0) ]\n")
            exit(0);
    
       case 3: seed=atoi(argv[2]); 
                if(seed<0 or !checkString(argv[2]))
                {
                    cout<<"Usage: ./hotpotato number-of-players (2 <= and <= 20) [ random-seed (>= 0) ]\n";
                    exit(0);
                }
            
        case 2: num=atoi(argv[1]);
                if(num>=2 and num<=20 and checkString(argv[1]))
                break;
                else
                cout<<"Usage: ./hotpotato number-of-players (2 <= and <= 20) [ random-seed (>= 0) ]\n";
                exit(0);
    }
    prng.seed(seed);
    cout<<num<<" players in the match"; 
    Player *allplayers[num+2];
    unsigned int i;
    For(i,0,num)
    {
        allplayers[i]=new Player(ump1,i,map1);
        map1.insert(make_pair(i,allplayers[i]));
    }         
    //ui rn=prng(0,map1.size()-1);
    ump1.set(1);
  
}

