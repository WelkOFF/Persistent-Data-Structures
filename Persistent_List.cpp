//Persistent List - Dimitar Karev & Petar Velkov
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
struct List
{
    int val;
    List *Next,*Prev;
};
int n,CntLists=1;
List *Beginings[10000];
void BuildList()
{
    List *CurrentList, *PrevList;
    CurrentList= new List;
    Beginings[1]= CurrentList;
    cin>>Beginings[1]->val;
    for(int i=2;i<=n;i++)
    {
        PrevList=CurrentList;
        CurrentList=new List;
        CurrentList->Prev=PrevList;
        PrevList->Next=CurrentList;
        cin>>CurrentList->val;
    }
    CurrentList->Next=NULL;
}
void UpdateVal(int Ind,int State,int NewVal)
{
    CntLists++;
    List *CurrentList=new List,*OldList=Beginings[State],*PrevList;
    CurrentList->val=Beginings[State]->val;
    Beginings[CntLists]= CurrentList;

    for(int i=1;i<Ind;i++)
    {
        PrevList=CurrentList;
        OldList=OldList->Next;
        CurrentList=new List;


        CurrentList->val=OldList->val;
        CurrentList->Prev=PrevList;
        PrevList->Next=CurrentList;
    }
    CurrentList->val=NewVal;
    CurrentList->Next=OldList->Next;
}
void Insert(int Ind,int State,int NewVal)
{
    CntLists++;
    List *CurrentList=new List,*OldList=Beginings[State],*PrevList;
    if(Ind==0)
    {
        CurrentList->val=NewVal;
        CurrentList->Next=OldList;
        CurrentList->Next->Prev=CurrentList;
        Beginings[CntLists]=CurrentList;
        return;
    }

    CurrentList->val=Beginings[State]->val;
    Beginings[CntLists]= CurrentList;

    for(int i=1;i<Ind;i++)
    {
        PrevList=CurrentList;
        OldList=OldList->Next;
        CurrentList=new List;


        CurrentList->val=OldList->val;
        CurrentList->Prev=PrevList;
        PrevList->Next=CurrentList;
    }
    CurrentList->Next=new List;
    CurrentList->Next->Prev=CurrentList;
    CurrentList->Next->val=NewVal;
    CurrentList->Next->Next=OldList->Next;
}
int FindElement(int Ind,int State)
{
    List *CurrentList=Beginings[State];

    for(int i=1;i<Ind;i++)
    {
        CurrentList=CurrentList->Next;
    }
    return CurrentList->val;
}
void PrintList(int State)
{
    List *CurrentList=Beginings[State];
    while(CurrentList->Next!=NULL)
    {
        cout<<CurrentList->val<<" ";
        CurrentList=CurrentList->Next;
    }
    cout<<"\n";
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int Type, State, Ind, NewVal;
    cin>>n;
    BuildList();
    int Queries;
    cin>>Queries;
    for(int i=1;i<=Queries;i++)
    {
        cin>>Type>>State;
        if(Type!=4)cin>>Ind;
        if(Type==1)
        {
            cin>>NewVal;
            UpdateVal(Ind,State,NewVal);
        }
        if(Type==2)
        {
            cin>>NewVal;
            Insert(Ind,State,NewVal);
        }
        if(Type==3)
        {
            cout<<FindElement(Ind,State)<<"\n";
        }
        if(Type==4)
        {
            PrintList(State);
        }
    }
    return 0;
}
