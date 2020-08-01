//
#include<iostream>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<string>
#include<vector>
#include<iomanip>
#include<fstream>
#include<map>
#include<set>
#include<queue>
#include<climits>
#define lli long long
using namespace std;
struct Stack
{
    int val;
    Stack *Next;
};
Stack *Beginings[10000];
int n,CntStacks=1,Queries;
void BuildStack(Stack *Unit,int CntUnits)
{
    if(CntUnits==n)
    {
        cin>>Unit->val;
        Unit->Next=NULL;
        return;
    }
    Unit->Next = new Stack;
    BuildStack(Unit->Next ,CntUnits+1);
    cin>>Unit->val;
}
void Pop(int State)
{
    CntStacks++;
    Beginings[CntStacks]=Beginings[State]->Next;
}
void Push(int State,int NewVal)
{
    CntStacks++;
    Beginings[CntStacks]=new Stack;
    Beginings[CntStacks]->val=NewVal;
    Beginings[CntStacks]->Next=Beginings[State];
}
bool Empty(int State)
{
    if(Beginings[State]==NULL)return 1;
    return 0;
}
int Top(int State)
{
    return Beginings[State]->val;
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int Type,Value,State;
    cin>>n;
    Beginings[1]=new Stack;
    BuildStack(Beginings[1],1);
    cin>>Queries;
    for(int i=1;i<=Queries;i++)
    {
        cin>>Type>>State;
        if(Type==1){Pop(State);}
        if(Type==2){cin>>Value; Push(State,Value);}
        if(Type==3){cout<<Top(State)<<"\n";}
    }
    return 0;
}
