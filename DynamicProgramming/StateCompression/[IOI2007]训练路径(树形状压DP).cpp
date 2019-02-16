#include<bits/stdc++.h>
using namespace std;

const int N=1050,M=5010;
struct Edge{int u,v,w;} e[M];
vector<int> g[N],son[N];
vector<Edge> nte[N];
int fa[N],dep[N],f[N][N],idx[N];
int n,m,sum=0;

void dfs(int u)
{
    for(int v : g[u])
    {
        if(v==fa[u]) continue;
        son[u].emplace_back(v);
        idx[v]=son[u].size()-1;
        dep[v]=dep[u]+1;
        fa[v]=u;dfs(v);
    }
}

int lca(int x,int y)
{
    if(dep[x]<dep[y]) swap(x,y);
    while(dep[x]>dep[y]) x=fa[x];
    while(x!=y) x=fa[x],y=fa[y];
    return x;
}

void dp(int u)
{
    for(int v : son[u]) dp(v);
    for(int s=0;s<1<<son[u].size();s++)
    {
        assert(f[u][s]==0);
        for(int i=0;i<son[u].size();i++)
            if(!(s&(1<<i))) f[u][s]+=f[son[u][i]][0];
    }
    for(Edge e : nte[u])
    {
        int val=(e.u!=u?f[e.u][0]:0)+(e.v!=u?f[e.v][0]:0)+e.w,x=0,y=0;
        if(e.u!=u) for(x=e.u;fa[x]!=u;x=fa[x]) val+=f[fa[x]][1<<idx[x]];
        if(e.v!=u) for(y=e.v;fa[y]!=u;y=fa[y]) val+=f[fa[y]][1<<idx[y]];
        int t=(x?1<<idx[x]:0)|(y?1<<idx[y]:0);
        for(int s=0;s<1<<son[u].size();s++)
            if((s&t)==0) f[u][s]=max(f[u][s],f[u][s|t]+val);
    }
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1,u,v,w;i<=m;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        e[i]=(Edge){u,v,w};sum+=w;
        if(e[i].w) continue;
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    dep[1]=1;dfs(1);
    for(int i=1;i<=m;i++)
    {
        int u=e[i].u,v=e[i].v,w=e[i].w;
        if(!w||(dep[u]&1)!=(dep[v]&1)) continue;
        nte[lca(u,v)].emplace_back((Edge){u,v,w});
    }
    dp(1);
    printf("%d\n",sum-f[1][0]);
    return 0;
}