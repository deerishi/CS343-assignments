#ifndef AUTOMATIC_SIGNAL
#define AUTOMATIC_SIGNAL \
    uCondition autoBench

#define WAITUNTIL(pred,before,after) \
    if(!(pred)) {\
        before;\
        while(!autoBench.empty()) {autoBench.signal();}\
        do{\
            autoBench.wait();\
            }while(!(pred));\
         after;\
      }
      
      
#define RETURN(expr) \
    while(!autoBench.empty()) {autoBench.signal();}\
    return expr;
    
#endif
