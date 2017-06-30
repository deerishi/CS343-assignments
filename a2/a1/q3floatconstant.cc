#include<iostream>
#include<cctype>
#include<cstdio>
#include <fstream>

using namespace std;

_Coroutine FloatConstant {
  public:
	enum Status { CONT, MATCH };		// possible status
  private:
	// YOU ADD MEMBERS HERE
	int parsedSoFar,digitsSoFar,mantissa,characteristic; //Private variables to help in identification of a valid string
	char ch;
	enum Status status;
	string passedSoFar,stringLeft;
	bool exponent,floatingSuffix,fractionalConstant,decimalPoint;
	void main(){
	    digitsSoFar=0;mantissa=0;characteristic=0;
	    floatingSuffix=false;fractionalConstant=false;exponent=false;decimalPoint=false;
	    //cout<<"Starting again\n";
	    for(;;)
	    {
	        if(ch=='\n') break; //Coroutine ends after processing one string
	        else if(isdigit(ch)){
	            status=Status::MATCH;digitsSoFar++;
	            if((exponent and (++characteristic)>3) or (!exponent and (++mantissa)>16) or floatingSuffix) _Throw Error();}
	        
	        else if(ch=='+' or ch=='-'){
	            status=Status::CONT;
	            if((exponent and characteristic!=0) or (!exponent and mantissa!=0))_Throw Error();}
	        
	        else if(ch=='.'){
	        if(decimalPoint) _Throw Error();
	        decimalPoint=true;status=Status::MATCH;
	        if(mantissa==0) status=Status::CONT;
	        }
	        
	        else if(char(tolower(ch))=='e'){
	        if(exponent) _Throw Error();
	        exponent=true;status=Status::CONT;
	        }
	        else if(char(tolower(ch))=='f' or char(tolower(ch))=='l'){
	        if(floatingSuffix) _Throw Error();
	        floatingSuffix=true;status=Status::MATCH;
	        }
	        else {
	            _Throw Error();
	        }
	        suspend(); //coroutine suspends after reading one character
        }
	}						// coroutine main
  public:
	_Event Error {};					// last character is invalid
	Status next( char c ) {
		ch = c;							// communication in
		resume();						// activate
		return status;					// communication out
	}
};

void uMain::main()
{   
    string str,str2;
    int status;
    //FloatConstant::Status s1;
    
    bool flag,fileInp=false;
    ifstream myfile; //For reading from file
    switch ( argc ) {
    case 1: break;
    case 2: 
            try{
            myfile.open(argv[1]);
                fileInp=true;
                break;
            }
            catch(...){
            cout << "Error! Could not open input file \""<<argv[1]<<"\"\n"; 
            exit(0);
            }
    };
    for(;;){
        FloatConstant fltc;
        //fltc.Status status;
        flag=true;
        if(fileInp){
            if(!getline(myfile, str)) break;}
        else{
             if(!getline(cin, str)) break;}
        str2=str;
        str=str+'\n'; //Explicit appending of a string with the newline to signal end of a coroutine
        for(unsigned int  i=0;i<str.length() and flag;i++){
            try{
               status=static_cast<int>(fltc.next(str[i]));}
            _CatchResume(uBaseCoroutine::UnhandledException){
                cout<<"\""<<str2<<"\" : \""<<str2.substr(0,i+1)<<"\" "<<"no";
                
                if(i+1<str2.length()){
                    cout<<" -- extraneous characters \""<<str2.substr(i+1,string::npos)<<"\"";}
                cout<<"\n";
                flag=false;}}
        if(flag){
        if(str.length()==1)
            cout<<"\"\" : Warning! Blank line.";
        else if(status==0){
            cout<<"\""<<str2<<"\" : \""<<str2<<"\" "<<"no";}
        else{
            cout<<"\""<<str2<<"\" : \""<<str2<<"\""<<" "<<"yes";}
        cout<<"\n";
        str.clear();}
    }
}
