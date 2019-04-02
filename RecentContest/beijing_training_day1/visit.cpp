#include<bits/stdc++.h>
#define fr first
#define se second
using namespace std;

typedef long long LL;
typedef pair<LL,int> pli;
typedef pair<int,int> pii;
const LL INF=0x3f3f3f3f3f3f3f3fll;
const int N=100010;
vector<pii> g[N];
int n,m,s,t;
LL d1[N],d2[N],f[N];
int fa[N],hson[N],dep[N],top[N],sz[N];
int dfn[N],dfc=0;
LL tag[N<<2];

void dijkstra1()
{
    static bool vis[N];
    priority_queue<pli> pq;
    memset(vis,0,sizeof(vis));
    memset(d1,0x3f,sizeof(d1));
    pq.push(pli(0,t));d1[t]=0;
    while(!pq.empty())
    {
        int u=pq.top().se;pq.pop();
        if(vis[u]) continue;vis[u]=1;
        for(pii e : g[u])
            if(d1[u]+e.se<d1[e.fr])
            {
                d1[e.fr]=d1[u]+e.se;
                pq.push(pli(-d1[e.fr],e.fr));
            }
    }
}

LL dijkstra2()
{
    static bool vis[N];
    priority_queue<pli> pq;
    memset(vis,0,sizeof(vis));
    memset(d2,0x3f,sizeof(d2));
    pq.push(pli(0,t));d2[t]=0;
    while(!pq.empty())
    {
        int u=pq.top().se;pq.pop();
        if(vis[u]) continue;vis[u]=1;
        for(pii e : g[u])
            if(max(d2[u]+e.se,f[e.fr])<d2[e.fr])
            {
                d2[e.fr]=max(d2[u]+e.se,f[e.fr]);
                pq.push(pli(-d2[e.fr],e.fr));
            }
    }
    return d2[s]<1e15?d2[s]:-1;
}

void build_tree()
{
    queue<int> q;
    q.push(t);fa[t]=t;
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(pii e : g[u])
            if(!fa[e.fr]&&d1[e.fr]==d1[u]+e.se)
                fa[e.fr]=u,q.push(e.fr);
    }
    fa[t]=0;
}

void dfs1(int u)
{
    for(pii e : g[u])
    {
        if(fa[e.fr]!=u) continue;
        dep[e.fr]=dep[u]+1;
        dfs1(e.fr);
        sz[u]+=sz[e.fr];
        if(sz[e.fr]>sz[hson[u]]) hson[u]=e.fr;
    }
}

void dfs2(int u,int tp)
{
    top[u]=tp;
    dfn[u]=++dfc;
    if(hson[u]) dfs2(hson[u],tp);
    for(pii e : g[u])
        if(e.fr!=hson[u]&&fa[e.fr]==u)
            dfs2(e.fr,e.fr);
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

void update(int o,int l,int r,int nl,int nr,LL x)
{
    if(l>=nl&&r<=nr){tag[o]=min(tag[o],x);return;}
    int mid=(l+r)/2;
    if(nl<=mid) update(o<<1,l,mid,nl,nr,x);
    if(nr>mid) update(o<<1|1,mid+1,r,nl,nr,x);
}

LL qmin(int o,int l,int r,int k)
{
    if(l==r) return tag[o];
    int mid=(l+r)/2;LL res=tag[o];
    if(k<=mid) res=min(res,qmin(o<<1,l,mid,k));
    else res=min(res,qmin(o<<1|1,mid+1,r,k));
    return res;
}

void gao(int u,int v,LL w)
{
    int x=lca(u,v);w+=d1[u];
    while(top[u]!=top[x])
    {
        update(1,1,n,dfn[top[u]],dfn[u],d1[v]+w);
        u=fa[top[u]];
    }
    update(1,1,n,dfn[x]+1,dfn[u],d1[v]+w);
}

void get_f()
{
    memset(tag,0x3f,sizeof(tag));
    for(int u=1;u<=n;u++)
        for(pii e : g[u])
            if(fa[e.fr]!=u&&fa[u]!=e.fr)
                gao(u,e.fr,e.se);
    for(int i=1;i<=n;i++)
        f[i]=qmin(1,1,n,dfn[i])-d1[i];
}

int main()
{
    scanf("%d%d%d%d",&n,&m,&s,&t);
    for(int i=1,u,v,w;i<=m;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        g[u].emplace_back(v,w);
        g[v].emplace_back(u,w);
    }
    dijkstra1();
    build_tree();
    dfs1(t);
    dfs2(t,t);
    get_f();
    printf("%lld\n",dijkstra2());
    return 0;
}