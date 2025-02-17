#include<bits/stdc++.h>
using namespace std;

const int N=100010;
vector<int> G[N];
int n,m,Q,dep[N],fa[N],ffa[N];
int hson[N],top[N],sz[N],sum[N];
int dfn[N],dfc=0;
bool vis[N],ans[N];
int qu[N],qv[N];
int idx[N];

int find(int x){return ffa[x]==x?x:ffa[x]=find(ffa[x]);}

void dfs1(int u)
{
    vis[u]=1;sz[u]=1;
    for(int v : G[u])
    {
        if(vis[v]) continue;
        dep[v]=dep[u]+1;
        fa[v]=u;dfs1(v);
        sz[u]+=sz[v];
        if(sz[v]>sz[hson[u]]) hson[u]=v;
    }
}

void dfs2(int u,int tp)
{
    dfn[u]=++dfc;top[u]=tp;
    if(hson[u]) dfs2(hson[u],tp);
    for(int v : G[u])
        if(fa[v]==u&&v!=hson[u])
            dfs2(v,v);
}

int LCA(int x,int y)
{
    while(top[x]!=top[y])
    {
        if(dep[top[x]]<dep[top[y]]) swap(x,y);
        x=fa[top[x]];
    }
    return dep[x]<dep[y]?x:y;
}

bool query(int x,int y)
{
    if(find(x)!=find(y)) return 0;
    if((dep[x]&1)!=(dep[y]&1)) return 1;
    return sum[x]+sum[y]-2*sum[LCA(x,y)];
}

void build(int u)
{
    vis[u]=1;
    for(int v : G[u])
    {
        if(fa[v]==u||fa[u]==v) continue;
        if((dep[u]&1)!=(dep[v]&1)) continue;
        sum[u]++;sum[v]++;sum[LCA(u,v)]-=2;
    }
    for(int v : G[u])
        if(!vis[v]&&fa[v]==u) build(v);
}

void reduction1(int u)
{
    for(int v : G[u])
    {
        if(fa[v]!=u) continue;
        reduction1(v);
        sum[u]+=sum[v];
    }
}

void reduction2(int u)
{
    for(int v : G[u])
    {
        if(fa[v]!=u) continue;
        sum[v]+=sum[u];
        reduction2(v);
    }
}

void clear()
{
    memset(vis,0,sizeof(vis));
    memset(top,0,sizeof(top));
    memset(hson,0,sizeof(hson));
    memset(sz,0,sizeof(sz));
    memset(dep,0,sizeof(dep));
    memset(sum,0,sizeof(sum));
    memset(fa,0,sizeof(fa));
    dfc=0;memset(dfn,0,sizeof(dfn));
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) ffa[i]=i;
    for(int i=1,u,v;i<=m;i++)
    {
        scanf("%d%d",&u,&v);
        G[u].push_back(v);
        G[v].push_back(u);
        if(find(u)!=find(v))
            ffa[find(u)]=find(v);
    }
    scanf("%d",&Q);
    for(int i=1;i<=Q;i++)
        scanf("%d%d",qu+i,qv+i);
    for(int i=1;i<=n;i++) idx[i]=i;
    for(int tms=7;tms;tms--)
    {
        random_shuffle(idx+1,idx+1+n);
        for(int i=1;i<=n;i++) random_shuffle(G[i].begin(),G[i].end());
        clear();
        for(int i=1;i<=n;i++)
            if(!vis[idx[i]]) dfs1(idx[i]),dfs2(idx[i],idx[i]);
        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n;i++)
            if(!vis[idx[i]])
            {
                build(idx[i]);
                reduction1(idx[i]);
                reduction2(idx[i]);
            }
        for(int i=1;i<=Q;i++)
            if(!ans[i]) ans[i]=query(qu[i],qv[i]);
    }
    for(int i=1;i<=Q;i++)
        puts(ans[i]?"Yes":"No");
    return 0;
}