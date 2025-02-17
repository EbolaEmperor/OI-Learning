#include<bits/stdc++.h>
using namespace std;

const int N=1010;
vector<int> G[N],ans;
int n,m,p;
bool vis[N];

void dfs(int u,int d)
{
    vis[u]=1;
    if(d&1) ans.push_back(u);
    for(int v : G[u])
        if(!vis[v]) dfs(v,d^1);
    if(~d&1) ans.push_back(u);
}

int main()
{
    scanf("%d%d%d",&n,&m,&p);
    for(int i=1,u,v;i<=m;i++)
    {
        scanf("%d%d",&u,&v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(1,1);
    for(int x : ans)
        printf("%d ",x);
    return 0;
}