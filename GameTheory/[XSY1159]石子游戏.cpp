#include<bits/stdc++.h>
using namespace std;

const int N=1000000;
int prm[N+5],sg[N+5],tot=0;
bool mark[N+5];

void Init()
{
    sg[0]=0;sg[1]=1;
    for(int i=2;i<=N;i++)
    {
        if(!mark[i]){prm[++tot]=i;sg[i]=tot+1;}
        for(int j=1;j<=tot&&i*prm[j]<=N;j++)
        {
            mark[i*prm[j]]=1;
            sg[i*prm[j]]=sg[prm[j]];
            if(i%prm[j]==0) break;
        }
    }
}

int main()
{
    int T,n;Init();
    scanf("%d",&T);
    while(T--)
    {
        int ans=0,x;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)
        {
            scanf("%d",&x);
            ans^=sg[x];
        }
        puts(ans?"Alice":"Bob");
    }
    return 0;
}