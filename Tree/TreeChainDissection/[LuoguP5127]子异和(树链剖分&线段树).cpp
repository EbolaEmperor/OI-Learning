#include<bits/stdc++.h>
using namespace std;

const int ha=1e9+7;
const int N=200010;
unsigned sand[N<<2],sor[N<<2],lazy[N<<2];
int dfn[N],idx[N],dfc=0;
int fa[N],hson[N],top[N];
int dep[N],siz[N];
vector<int> g[N];
int n,m,val[N],pw2[N];

void update(int o,unsigned c)
{
    unsigned a=sor[o],b=sand[o];
    sor[o]=(a&~c)|(c&~b);
    sand[o]=(b&~c)|(c&~a);
    lazy[o]^=c;
}

void pushdown(int o)
{
    if(!lazy[o]) return;
    update(o<<1,lazy[o]);
    update(o<<1|1,lazy[o]);
    lazy[o]=0;
}

void build(int o,int l,int r)
{
    if(l==r){sand[o]=sor[o]=val[idx[l]];return;}
    int mid=(l+r)/2;
    build(o<<1,l,mid);
    build(o<<1|1,mid+1,r);
    sand[o]=sand[o<<1]&sand[o<<1|1];
    sor[o]=sor[o<<1]|sor[o<<1|1];
}

void cxor(int o,int l,int r,int nl,int nr,unsigned c)
{
    if(l>=nl&&r<=nr){update(o,c);return;}
    int mid=(l+r)/2;pushdown(o);
    if(nl<=mid) cxor(o<<1,l,mid,nl,nr,c);
    if(nr>mid) cxor(o<<1|1,mid+1,r,nl,nr,c);
    sand[o]=sand[o<<1]&sand[o<<1|1];
    sor[o]=sor[o<<1]|sor[o<<1|1];
}

unsigned qor(int o,int l,int r,int nl,int nr)
{
    if(l>=nl&&r<=nr) return sor[o];
    int mid=(l+r)/2;unsigned res=0;pushdown(o);
    if(nl<=mid) res|=qor(o<<1,l,mid,nl,nr);
    if(nr>mid) res|=qor(o<<1|1,mid+1,r,nl,nr);
    return res;
}

void dfs1(int u)
{
    siz[u]=1;
    for(int v : g[u])
    {
        if(v==fa[u]) continue;
        dep[v]=dep[u]+1;
        fa[v]=u;dfs1(v);
        siz[u]+=siz[v];
        if(siz[v]>siz[hson[u]]) hson[u]=v;
    }
}

void dfs2(int u,int tp)
{
    top[u]=tp;
    idx[dfn[u]=++dfc]=u;
    if(hson[u]) dfs2(hson[u],tp);
    for(int v : g[u])
        if(v!=fa[u]&&v!=hson[u])
            dfs2(v,v);
}

void pathxor(int u,int v,unsigned c)
{
    while(top[u]!=top[v])
    {
        if(dep[top[u]]<dep[top[v]]) swap(u,v);
        cxor(1,1,n,dfn[top[u]],dfn[u],c);
        u=fa[top[u]];
    }
    if(dep[u]>dep[v]) swap(u,v);
    cxor(1,1,n,dfn[u],dfn[v],c);
}

int query(int u,int v)
{
    unsigned orsum=0,cnt=0;
    while(top[u]!=top[v])
    {
        if(dep[top[u]]<dep[top[v]]) swap(u,v);
        orsum|=qor(1,1,n,dfn[top[u]],dfn[u]);
        cnt+=dfn[u]-dfn[top[u]]+1;
        u=fa[top[u]];
    }
    if(dep[u]>dep[v]) swap(u,v);
    orsum|=qor(1,1,n,dfn[u],dfn[v]);
    cnt+=dfn[v]-dfn[u]+1;
    return 1ll*orsum*pw2[cnt-1]%ha;
}

int main()
{
    scanf("%d%d",&n,&m);
    pw2[0]=1;
    for(int i=1;i<=n;i++)
        pw2[i]=(pw2[i-1]<<1)%ha;;
    for(int i=1,u,v;i<n;i++)
    {
        scanf("%d%d",&u,&v);
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    for(int i=1;i<=n;i++)
        scanf("%d",val+i);
    dfs1(1);dfs2(1,1);
    build(1,1,n);
    int opt,u,v;unsigned c;
    while(m--)
    {
        scanf("%d%d%u",&opt,&u,&v);
        if(opt==1) printf("%d\n",query(u,v));
        else scanf("%u",&c),pathxor(u,v,c);
    }
    return 0;
}