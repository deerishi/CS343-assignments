#include "bits/stdc++.h"
using namespace std;
//geek for geeks 
#define blank putc_unlocked('\n',stdout);
#define ForIter(it,name) for(it=name.begin();it!=name.end();it++)
#define Forall(i,start,end) for(i=start;i<=end;i++)
#define For(i,start,end) for(i=start;i<end;i++)

regex reg1("thi*s");

int main()
{
    std::ios::sync_with_stdio(false);
    string str;
    cin>>str;
    sregex_iterator it(str.begin(),str.end(),reg1);
    sregex_iterator it_end;
    while(it!=it_end)
    {
        cout<<"Pattern found is "<<(*it)<<"\n";
    }
    return 0;
}
