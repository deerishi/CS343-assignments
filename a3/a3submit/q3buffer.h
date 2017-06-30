#include "MPRNG.h"
#include<iostream>
#include<cctype>
#include<cstdio>
#include<vector>
#include<queue>
#include <fstream>
using namespace std;
typedef unsigned int ui;
#define CHECK 1
MPRNG mprng;
#define ASSERT(condition) { if(!(condition)){ std::cerr << "ASSERT FAILED: " << #condition << " @ " << __FILE__ << " (" << __LINE__ << ")" << std::endl<<" WITH INUSE2 IS "<<inUse2<<" inUse is "<<inUse<<"\n"; } }

#ifdef BUSY
template<typename T> class BoundedBuffer {
    uOwnerLock block;
    //syncronization condition locks
    uCondLock full,empty;
    queue<T> buffer;
    ui maxSize;
  public:
    BoundedBuffer( const unsigned int size = 10 ) : maxSize(size){}
    void insert( T elem ){
        block.acquire();
        //LOck for the buffer
        while(buffer.size()==maxSize){
            //cout<<"waiting\n";
            full.wait(block);       //Busy waiting as we keep on a loop
        }
        //cout<<"pushing "<<elem<<"\n";
        assert(buffer.size()!=maxSize)
        buffer.push(elem);
        empty.signal();
        for(ui i=0;i<block.times();i++){
            block.release();
        }
    }
    T remove(){
        block.acquire();
        while(buffer.size()==0){
            empty.wait(block);
        }
        assert(buffer.size()!=0);
        T val=buffer.front();
        buffer.pop();
        full.signal();
        for(ui i=0;i<block.times();i++){
            block.release();
        }
        return val;
    }
};
#endif

#ifdef NOBUSY
template<typename T> class BoundedBuffer {
    uOwnerLock block;
    //syncronization condition locks
    uCondLock full,empty,barge,barge2;
    ui maxSize;
    bool inUse,inUse2;
    queue<T> buffer;

  public:
    BoundedBuffer( const unsigned int size = 10 ) : maxSize(size),inUse(false),inUse2(false){}
    void insert( T elem ){
        block.acquire();
        if(inUse){
            barge.wait(block);

        }
        if(buffer.size()==maxSize){
            if(!barge.empty()) {
                barge.signal();
            }
            else{
                inUse=false;
            }
            full.wait(block);
        }

        assert(buffer.size()!=maxSize);
        buffer.push(elem);

        if(!empty.empty()){
            //osacquire(cout)<<"insert empty release\n";
            inUse=true;
            empty.signal();
            //osacquire(cout)<<"empty signal \n";
        }
        else if(!barge.empty()){
            barge.signal();

        }
        else{
            inUse=false;
        }
        for(ui i=0;i<block.times();i++){
            block.release();
        }

    }
    T remove(){
        block.acquire();
        if(inUse){
            barge.wait(block);

        }
        if(buffer.size()==0){
             if(!barge.empty()) {
                barge.signal();
            }
            else{
                inUse=false;
            }
            empty.wait(block);
        }

        assert(buffer.size()!=0);
        T val=buffer.front();
        buffer.pop();


        if(!full.empty()){
            //osacquire(cout)<<"remove full release\n";
            inUse=true;
            full.signal();
            // osacquire(cout)<<"full signal \n";
        }
         else if(!barge.empty()){
            barge.signal();

        }
        else{
            inUse=false;
        }

        for(ui i=0;i<block.times();i++){
            block.release();
        }
        return val;

    }

};
#endif
_Task Producer {
    BoundedBuffer<int> &buffer;
    int produce,delay;
    void main(){
        int i;
        //cout<<"in producer\n";
        for(i=1;i<=produce;i++){
            ui times=mprng(0,delay-1);
            yield(times);
            buffer.insert(i);
        }
        //cout<<"returning from produce\n";
    }
  public:
    Producer( BoundedBuffer<int> &buffer, const int Produce, const int Delay ): buffer(buffer),produce(Produce),delay(Delay){}
};

_Task Consumer {
    BoundedBuffer<int> &buffer;
    int delay;
    int &sum;
    int sentinal;
    void main(){
        ui times;
        int val;
        while(1){
            times=mprng(0,delay-1);
            yield(times);
            val=buffer.remove();
            if(val==-1) break;
            sum+=val;

        }

    }
  public:
    Consumer( BoundedBuffer<int> &buffer, const int Delay, const int Sentinel, int &sum ) : buffer(buffer),delay(Delay),sum(sum),sentinal(Sentinel){}
};
