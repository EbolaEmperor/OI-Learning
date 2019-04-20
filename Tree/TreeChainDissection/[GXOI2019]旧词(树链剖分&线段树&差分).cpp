#include<bits/stdc++.h>
using namespace std;

const int N=50010,ha=998244353;
int tag[N<<2],sum[N<<2],w[N<<2];
vector<int> g[N];
int fa[N],hson[N],top[N],dep[N],sz[N];
int dfn[N],idx[N],dfc=0;
int n,q,k,h[N],ans[N];
struct Qry{int u,id;};
vector<Qry> qry[N];

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
}

void push(int o,int v){sum[o]=(sum[o]+1ll*v*w[o])%ha;tag[o]+=v;}
void pushdown(int o)
{
    if(!tag[o]) return;
    push(o<<1,tag[o]);
    push(o<<1|1,tag[o]);
    tag[o]=0;
}

void build(int o,int l,int r)
{
    if(l==r){w[o]=h[dep[idx[l]]];return;}
    int mid=(l+r)/2;
    build(o<<1,l,mid);
    build(o<<1|1,mid+1,r);
    w[o]=(w[o<<1]+w[o<<1|1])%ha;
}

void modify(int o,int l,int r,int nl,int nr)
{
    if(l>=nl&&r<=nr){push(o,1);return;}
    int mid=(l+r)/2;pushdown(o);
    if(nl<=mid) modify(o<<1,l,mid,nl,nr);
    if(nr>mid) modify(o<<1|1,mid+1,r,nl,nr);
    sum[o]=(sum[o<<1]+sum[o<<1|1])%ha;
}

int query(int o,int l,int r,int nl,int nr)
{
    if(l>=nl&&r<=nr) return sum[o];
    int mid=(l+r)/2,res=0;pushdown(o);
    if(nl<=mid) res=(res+query(o<<1,l,mid,nl,nr))%ha;
    if(nr>mid) res=(res+query(o<<1|1,mid+1,r,nl,nr))%ha;
    return res;
}

void dfs1(int u)
{
    sz[u]=1;
    for(int v : g[u])
    {
        dep[v]=dep[u]+1;
        dfs1(v);sz[u]+=sz[v];
        if(sz[v]>sz[hson[u]])
            hson[u]=v;
    }
}

void dfs2(int u,int tp)
{
    top[u]=tp;
    idx[dfn[u]=++dfc]=u;
    if(hson[u]) dfs2(hson[u],tp);
    for(int v : g[u])
        if(v!=hson[u]) dfs2(v,v);
}

void update(int u)
{
    for(;u;u=fa[top[u]])
        modify(1,1,n,dfn[top[u]],dfn[u]);
}

int query(int u)
{
    int res=0;
    for(;u;u=fa[top[u]])
        res=(res+query(1,1,n,dfn[top[u]],dfn[u]))%ha;
    return res;
}

int main()
{
    scanf("%d%d%d",&n,&q,&k);
    for(int i=1;i<=n;i++) h[i]=Pow(i,k);
    for(int i=n;i>=1;i--) h[i]=(h[i]-h[i-1]+ha)%ha;
    for(int i=2;i<=n;i++)
        scanf("%d",fa+i),g[fa[i]].push_back(i);
    dep[1]=1;dfs1(1);dfs2(1,1);
    build(1,1,n);
    for(int i=1,x,y;i<=q;i++)
        scanf("%d%d",&x,&y),qry[x].push_back({y,i});
    for(int i=1;i<=n;i++)
    {
        update(i);
        for(auto p : qry[i])
            ans[p.id]=query(p.u);
    }
    for(int i=1;i<=q;i++)
        printf("%d\n",ans[i]);
    return 0;
}
