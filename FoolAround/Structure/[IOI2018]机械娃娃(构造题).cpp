#include<bits/stdc++.h>
#include "doll.h"
using namespace std;

const int N=210010;

void create_circuit(int m,vector<int> A)
{
    static bool stu[N];
    static int deep[N];
    vector<int> C,X,Y;
    C.resize(m+1);C[0]=-1;A.push_back(0);
    int n=A.size(),dep=ceil(log2(n)),tot=1<<dep,S=1;
    X.push_back(0);Y.push_back(0);deep[0]=dep;
    for(int x : A)
    {
        int u=0;
        while(true)
        {
            int d=deep[u];
            stu[u]^=1;
            int &v=stu[u]?X[u]:Y[u];
            if(!v)
            {
                if((1<<d-1)<=tot-n) tot-=1<<d-1,v=-1;
                else if(d==1){v=x;C[x]=-1;break;}
                else deep[S]=d-1,v=-S-1,S++,X.push_back(0),Y.push_back(0);
            }
            u=-(stu[u]?X[u]:Y[u])-1;
        }
    }
    answer(C,X,Y);
}