#ifndef PRINT_H
#include "q3printer.h"
#define PRINT_H
#endif

//Constructor for initializing the output and the states
Printer::Printer( unsigned int voters ){
    this->voters=voters;
    information=new Printer::Buffer[voters];
    unsigned int i;
    for(i=0;i<voters;i++){
        cout<<"Voter"<<to_string(i)<<"\t";
    }
    cout<<"\n";
    for(i=0;i<voters;i++){
        information[i].filled=false;

        cout<<"=======\t";
    }
    cout<<"\n";
}

Printer::~Printer(){

    //Delete all the information
    //unsigned int  i;
    //flushInformation();
    delete [] information;
    cout<<"=================\n";
    cout<<"All tours started\n";
}

void Printer::flushInformation(){
    unsigned int i;
    char ch1;

    for(i=0;i<voters;i++){
        if(information[i].filled==true){

            //Printing the state
            cout<<(char)information[i].state;
            //Printing the state relevant information if any
            switch(information[i].state){
                //In case of voting
              case Voter::States::Vote :
                (information[i].voted==TallyVotes::Tour::Picture)?(ch1='p'):(ch1='s');
                cout<<" "<<ch1;
                 if(i!=voters-1)
            cout<<"\t";
                break;
                //In case of Blocking
              case Voter::States::Block:
                cout<<" "<<information[i].numBlocked;
                 if(i!=voters-1)
            cout<<"\t";
                break;

                //In case of Unblocking
              case Voter::States::Unblock:
                cout<<" "<<information[i].numBlocked;
                 if(i!=voters-1)
            cout<<"\t";
                  break;
              default : cout<<"\t";
            }
        }
        else{
            if(i!=voters-1)
            cout<<"\t";
        }

        information[i].filled=false; //Reset the state after printing
    }
    //if(changed)
    cout<<"\n";
}

void Printer:: print( unsigned int id, Voter::States state ){

    if(information[id].filled==true){//If overwriting
        flushInformation();
    }
    information[id].filled=true;
    information[id].state=state;
}

void Printer::print( unsigned int id, Voter::States state, TallyVotes::Tour vote ){
    //If we are printing a finished state, then first flush out then print anyways
    unsigned int i;
    char ch1;
    if(state==Voter::States::Finished){
        //Here we need to check if any information is required to be printed or not.
        bool fl1=false;
        for(i=0;i<voters;i++){
        if(information[i].filled==true)
            fl1=true;
        }
        if(fl1)
        flushInformation();
        //Now print out anyways
        for(i=0;i<voters;i++){
            if(i==id){
                //If the voter is finishing
                (vote==TallyVotes::Tour::Picture)?(ch1='p'):(ch1='s');
                cout<<"F "<<ch1<<"\t";
            }
            else{
                cout<<"...\t";
            }
            information[i].filled=false;
        }
        cout<<"\n";
    }
    else{
        //if its not finished, only print if the task is being overwritten
        if(information[id].filled==true){
            flushInformation();
        }
        information[id].filled=true;
        information[id].state=state;
        information[id].voted=vote;
    }

}


void Printer::print( unsigned int id, Voter::States state, unsigned int blocked ){

    if(information[id].filled==true){
        flushInformation();
    }
    information[id].filled=true;
    information[id].state=state;
    information[id].numBlocked=blocked;
}
