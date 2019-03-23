#include<bits/stdc++.h>
using namespace std;

const int N=100010;
struct Chain{int x,y,w;};
vector<Chain> chain[N];
vector<int> g[N];
int dep[N],fa[N],top[N],sz[N],hson[N];
int idfn[N],odfn[N],dfc=0;
int n,m,f[N],s[N];
int b[N];

inline int lowbit(const int &x){return x&-x;}
void add(int p,int x){for(;p<=n;p+=lowbit(p)) b[p]+=x;}
int sum(int p){int res=0;for(;p;p-=lowbit(p)) res+=b[p];return res;}

void dfs1(int u)
{
    sz[u]=1;
    for(int v : g[u])
    {
        if(v==fa[u]) continue;
        dep[v]=dep[u]+1;
        fa[v]=u;dfs1(v);
        sz[u]+=sz[v];
        if(sz[v]>sz[hson[u]]) hson[u]=v;
    }
}

void dfs2(int u,int tp)
{
    idfn[u]=++dfc;top[u]=tp;
    if(hson[u]) dfs2(hson[u],tp);
    for(int v : g[u])
        if(v!=fa[u]&&v!=hson[u])
            dfs2(v,v);
    odfn[u]=dfc;
}

int lca(int u,int v)
{
    while(top[u]!=top[v])
    {
        if(dep[top[u]]<dep[top[v]]) swap(u,v);
        u=fa[top[u]];
    }
    return dep[u]<dep[v]?u:v;
}

void dp(int u,int fa)
{
    for(int v : g[u])
    {
        if(v==fa) continue;
        dp(v,u);s[u]+=f[v];
    }
    f[u]=s[u];
    for(auto ch : chain[u])
    {
        int x=idfn[ch.x],y=idfn[ch.y],w=ch.w;
        int tmp=sum(x)+sum(y)+s[u];
        f[u]=max(f[u],tmp+w);
    }
    add(idfn[u],s[u]);
    add(odfn[u]+1,-s[u]);
    add(idfn[u],-f[u]);
    add(odfn[u]+1,f[u]);
}

int main()
{
    scanf("%d",&n);
    for(int i=1,u,v;i<n;i++)
    {
        scanf("%d%d",&u,&v);
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    dep[1]=1;dfs1(1);dfs2(1,1);
    scanf("%d",&m);
    for(int i=1,x,y,w;i<=m;i++)
    {
        scanf("%d%d%d",&x,&y,&w);
        chain[lca(x,y)].emplace_back((Chain){x,y,w});
    }
    dp(1,0);
    printf("%d\n",f[1]);
    return 0;
}