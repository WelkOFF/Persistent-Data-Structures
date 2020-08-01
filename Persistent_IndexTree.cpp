//Persistent Index Tree - Dimitar Karev & Petar Velkov
#include<iostream>
#include<cmath>
#include<algorithm>
#include<fstream>
#include<climits>
using namespace std;
struct Vertex
{
    int val;
    Vertex *Left,*Right;
};
Vertex *Roots[100005];
int N=1,Levels=1,Ans=0,Leaves[100005],p=1,Type,CntRoots=1,State,Ind,NewV,L,R;
void BuildTree(Vertex *Node,int lvl)
{
    if(lvl==Levels)
    {
        Node->val=Leaves[p];
        Node->Left=NULL; Node->Right=NULL;
        p++; return;
    }
    Node->Left= new Vertex;
    Node->Right= new Vertex;
    BuildTree(Node->Left,lvl+1);
    BuildTree(Node->Right,lvl+1);
    Node->val= Node->Left->val +Node->Right->val;
}
void Update(Vertex *NewNode,Vertex *OldNode,int x,int y)
{
    if(x==y && x==Ind)
    {
        NewNode->val=NewV;
        return;
    }
    int p=x,q=(x+y)/2;
    if(p<=Ind && q>=Ind)
    {
        NewNode->Left=new Vertex;
        Update(NewNode->Left,OldNode->Left,p,q);
        NewNode->Right=OldNode->Right;
    }
    else
    {
        p=(x+y)/2+1; q=y;
        NewNode->Right=new Vertex;
        Update(NewNode->Right,OldNode->Right,p,q);
        NewNode->Left=OldNode->Left;
    }
    NewNode->val=NewNode->Left->val+NewNode->Right->val;
}
void FindSum(Vertex *Node,int x,int y)
{
    if(x>R || y<L)return;
    if(x>=L && y<=R)
    {
        Ans+=Node->val;
        return;
    }
    FindSum(Node->Left,x,(x+y)/2);
    FindSum(Node->Right,(x+y)/2+1,y);
}
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    //ifstream cin("input.txt");
    //ofstream cout("output.txt");
    int n,k,Queries;
    cin>>n;
    while(N<n){N<<=1;Levels++;}
    for(int i=1;i<=n;i++)cin>>Leaves[i];
    Roots[1]=new Vertex;
    BuildTree(Roots[1],1);
    cin>>Queries;
    for(int i=1;i<=Queries;i++)
    {
        cin>>Type>>State;
        if(Type==1)
        {
            cin>>Ind>>NewV;
            CntRoots++;
            Roots[CntRoots]=new Vertex;
            Update(Roots[CntRoots],Roots[State],1,N);
        }
        if(Type==2)
        {
            Ans=0;
            cin>>L>>R;
            FindSum(Roots[State],1,N);
            cout<<Ans<<"\n";
        }
    }
    return 0;
}
/*
6
1 5 3 -2 1 3
5
2 1 2 4
1 1 4 0
1 2 5 5
2 2 1 6
2 3 1 6
*/
