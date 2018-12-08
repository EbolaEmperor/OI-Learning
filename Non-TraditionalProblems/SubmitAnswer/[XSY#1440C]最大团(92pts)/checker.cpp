#include<bits/stdc++.h>
using namespace std;

int ansn,ans[550];
int e[1500][1500],n,m;

int main(int argv,char* argc[])
{
    freopen(argc[2],"r",stdin);
    cin>>ansn;
    for(int i=1;i<=ansn;i++) cin>>ans[i];
    freopen(argc[1],"r",stdin);
    scanf("%d%d",&n,&m);
    for(int i=1,u,v;i<=m;i++)
    {
        scanf("%d%d",&u,&v);
        e[u][v]=e[v][u]=1;
    }
    for(int i=1;i<=ansn;i++)
        for(int j=i+1;j<=ansn;j++)
            if(!e[ans[i]][ans[j]]) printf("%d and %d have no edge!\n",ans[i],ans[j]);
    return 0;
}