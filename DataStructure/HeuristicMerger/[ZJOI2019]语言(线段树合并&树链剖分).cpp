#include<bits/stdc++.h>
using namespace std;

const int N=100010;
int lc[N*400],rc[N*400],sum[N*400],rt[N],tot=0;
int dep[N],sz[N],hson[N],top[N],fa[N];
int idfn[N],odfn[N],idx[N],dfc=0;
vector<int> g[N],chg[N];
long long ans=0;
int n,m;

void modify(int &o,int l,int r,int nl,int nr)
{
    if(!o) o=++tot;
    if(sum[o]==r-l+1) return;
    if(l>=nl&&r<=nr){sum[o]=r-l+1;return;}
    int mid=(l+r)/2;
    if(nl<=mid) modify(lc[o],l,mid,nl,nr);
    if(nr>mid) modify(rc[o],mid+1,r,nl,nr);
    sum[o]=sum[lc[o]]+sum[rc[o]];
}

int query(int o,int l,int r,int nl,int nr)
{
    if(!o||nl>nr) return 0;
    if(sum[o]==r-l+1) return nr-nl+1;
    if(l>=nl&&r<=nr) return sum[o];
    int mid=(l+r)/2;
    if(nr<=mid) return query(lc[o],l,mid,nl,nr);
    else if(nl>mid) return query(rc[o],mid+1,r,nl,nr);
    else return query(lc[o],l,mid,nl,mid)+query(rc[o],mid+1,r,mid+1,nr);
}

int merge(int x,int y,int l,int r)
{
    if(sum[x]==r-l+1) return x;
    if(sum[y]==r-l+1) return y;
    if(!x||!y) return x|y;
    int mid=(l+r)/2;
    lc[x]=merge(lc[x],lc[y],l,mid);
    rc[x]=merge(rc[x],rc[y],mid+1,r);
    sum[x]=sum[lc[x]]+sum[rc[x]];
    return x;
}

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
    top[u]=tp;
    idx[idfn[u]=++dfc]=u;
    if(hson[u]) dfs2(hson[u],tp);
    for(int v : g[u])
        if(v!=fa[u]&&v!=hson[u])
            dfs2(v,v);
    odfn[u]=dfc;
}

void modify(int x,int u,int v)
{
    while(top[u]!=top[v])
    {
        if(dep[top[u]]<dep[top[v]]) swap(u,v);
        modify(rt[x],1,n,idfn[top[u]],idfn[u]);
        u=fa[top[u]];
    }
    if(dep[u]>dep[v]) swap(u,v);
    modify(rt[x],1,n,idfn[u],idfn[v]);
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

void gao(int u)
{
    for(int v : g[u])
    {
        if(v==fa[u]) continue;
        gao(v);
        rt[u]=merge(rt[u],rt[v],1,n);
    }
    for(int x : chg[u])
        if(idfn[x]<idfn[u]||idfn[x]>odfn[u]) modify(u,u,x);
    long long tmp=ans;
    ans+=query(rt[u],1,n,1,idfn[u]-1);
    ans+=query(rt[u],1,n,odfn[u]+1,n);
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1,u,v;i<n;i++)
    {
        scanf("%d%d",&u,&v);
        g[u].emplace_back(v);
        g[v].emplace_back(u);
    }
    dfs1(1);dfs2(1,1);
    for(int i=1,u,v;i<=m;i++)
    {
        scanf("%d%d",&u,&v);
        if(idfn[u]>idfn[v]) swap(u,v);
        chg[u].emplace_back(v);
        chg[v].emplace_back(lca(u,v));
    }
    gao(1);
    cout<<ans<<endl;
    return 0;
}