#include<bits/stdc++.h>
using namespace std;

const int N=300010;
vector<int> g[N],g2[N];
int n,m,h[N],sum=0;
int col[N],trc[N];
bool vis[N];
stack<int> path;

void dfs(int u,int fa)
{
    vis[u]=1;
    for(int v : g[u])
    {
        if(v==fa||vis[v]) continue;
        col[v]=col[u]^1;
        dfs(v,u);
    }
}

void outloop(int v)
{
    vector<int> ans;
    while(path.top()!=v)
        ans.emplace_back(path.top()),path.pop();
    ans.emplace_back(v);
    printf("B %d ",ans.size());
    for(int x : ans) printf("%d ",x);
    exit(0);
}

void bitgraph(int u)
{
    vis[u]=1;
    path.push(u);
    for(int v : g2[u])
    {
        if(!vis[v])
        {
            col[v]=(col[u]+2)&3;
            bitgraph(v);
        }
        else if(col[u]==col[v]) outloop(v);
    }
    path.pop();
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1,u,v;i<=m;i++)
    {
        scanf("%d%d",&u,&v);
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    col[1]=0;dfs(1,0);
    memcpy(trc,col,sizeof(trc));
    for(int u=1;u<=n;u++)for(int v : g[u])
        if(trc[u]==trc[v]) g2[u].emplace_back(v);
    memset(vis,0,sizeof(vis));
    for(int u=1;u<=n;u++)
        if(!vis[u]) bitgraph(u);
    printf("A ");
    for(int i=1;i<=n;i++)
        printf("%d ",col[i]+1);
    return 0;
}