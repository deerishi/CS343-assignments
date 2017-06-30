#include<cctype>
#include<cstdio>
#include<vector>
#include<queue>
#include <fstream>
#include <sys/types.h>
#include "string.h"
#include <unistd.h>
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

MPRNG mprng;
bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}
void uMain::main(){
    cout<<"hello world\n";
    //Checking for the validity of the command line parameters
    unsigned int voters=6,group=3,seed=getpid(),i;
    //Checking the validity of the arguments
    string usage="Usage: ./voteMC  Voters (> 0 & V mod G = 0, default 6)  Group (> 0 & odd, default 3)  Seed (> 0)";
    if(argc>4){
        cout<<usage<<"\n";
        exit(0);
    }
     switch(argc){
       case 1: voters=6;group=3;seed=getpid();break;
        case 2 :
        if(!is_number(argv[1])){ cout<<usage<<"\n";exit(0);}
        voters=atoi(argv[1]);
        break;
        case 3 :
        if(!is_number(argv[1]) or !is_number(argv[2])){
            cout<<usage<<"\n";
            exit(0);
        }
         voters=atoi(argv[1]); group=atoi(argv[2]);break;
        case 4 :
         if(!is_number(argv[1]) or !is_number(argv[2]) or !is_number(argv[3]) or atoi(argv[3])<=0){ cout<<usage<<"\n";exit(0);}
        voters=atoi(argv[1]); group=atoi(argv[2]);seed=atoi(argv[3]);break;
     }
     if(group%2==0 or voters%group!=0 or group>=voters){ cout<<usage<<"\n";exit(0);}

     //----------------------VALIDITY CHECKING DONE
     mprng.set_seed(seed);
     Printer printer(voters);
     TallyVotes voteTallier(group,printer);
     Voter *Voters[voters];
     for(i=0;i<voters;i++){
        Voters[i]=new Voter(i,voteTallier,printer);
     }
     for(i=0;i<voters;i++){
        delete Voters[i];
     }

}
