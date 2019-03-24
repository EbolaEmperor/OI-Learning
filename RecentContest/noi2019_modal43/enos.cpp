#include<bits/stdc++.h>
using namespace std;

const int N=100010;
int cnt[N<<2][3],sum[N<<2][3],tag[N<<2];
int dfn[N],dfc=0;
int top[N],btm[N],hson[N];
int fa[N],sz[N],dep[N],lst[N];
vector<int> g[N];
int n,m;

void mdf(int o,int l,int r,int c)
{
    sum[o][0]=sum[o][1]=sum[o][2]=0;
    sum[o][c]=r-l+1;
    tag[o]=c;
}

void maintain(int o)
{
    for(int i=0;i<3;i++)
    {
        cnt[o][i]=cnt[o<<1][i]+cnt[o<<1|1][i];
        sum[o][i]=sum[o<<1][i]+sum[o<<1|1][i];
    }
}

void pushdown(int o,int l,int r)
{
    if(tag[o]<0) return;
    int mid=(l+r)/2;
    mdf(o<<1,l,mid,tag[o]);
    mdf(o<<1|1,mid+1,r,tag[o]);
    tag[o]=-1;
}

void build(int o,int l,int r)
{
    tag[o]=-1;
    if(l==r){sum[o][0]=1;return;}
    int mid=(l+r)/2;
    build(o<<1,l,mid);
    build(o<<1|1,mid+1,r);
    maintain(o);
}

void upcol(int o,int l,int r,int nl,int nr,int c)
{
    if(l>=nl&&r<=nr){mdf(o,l,r,c);return;}
    int mid=(l+r)/2;pushdown(o,l,r);
    if(nl<=mid) upcol(o<<1,l,mid,nl,nr,c);
    if(nr>mid) upcol(o<<1|1,mid+1,r,nl,nr,c);
    maintain(o);
}

void upcnt(int o,int l,int r,int k,int c,int x)
{
    if(l==r){cnt[o][c]+=x;return;}
    int mid=(l+r)/2;pushdown(o,l,r);
    if(k<=mid) upcnt(o<<1,l,mid,k,c,x);
    else upcnt(o<<1|1,mid+1,r,k,c,x);
    maintain(o);
}

int qcol(int o,int l,int r,int k)
{
    if(l==r)
    {
        if(sum[o][0]) return 0;
        if(sum[o][1]) return 1;
        if(sum[o][2]) return 2;
    }
    int mid=(l+r)/2;pushdown(o,l,r);
    if(k<=mid) return qcol(o<<1,l,mid,k);
    else return qcol(o<<1|1,mid+1,r,k);
}

int qcnt(int o,int l,int r,int nl,int nr,int c)
{
    if(l>=nl&&r<=nr) return cnt[o][c];
    int mid=(l+r)/2,res=0;pushdown(o,l,r);
    if(nl<=mid) res+=qcnt(o<<1,l,mid,nl,nr,c);
    if(nr>mid) res+=qcnt(o<<1|1,mid+1,r,nl,nr,c);
    return res;
}

int findr(int o,int l,int r,int nl,int nr,int c)
{
    if(l>=nl&&r<=nr&&sum[o][c]==r-l+1) return r;
    if(!sum[o][c]) return 0;
    int mid=(l+r)/2;pushdown(o,l,r);
    if(nr<=mid) return findr(o<<1,l,mid,nl,nr,c);
    else if(nl>mid) return findr(o<<1|1,mid+1,r,nl,nr,c);
    else
    {
        int res1=findr(o<<1,l,mid,nl,nr,c);
        if(res1!=mid) return res1;
        int res2=findr(o<<1|1,mid+1,r,nl,nr,c);
        return res2?res2:res1;
    }
}

int findl(int o,int l,int r,int nl,int nr,int c)
{
    if(l>=nl&&r<=nr&&sum[o][c]==r-l+1) return l;
    if(!sum[o][c]) return 0;
    int mid=(l+r)/2;pushdown(o,l,r);
    if(nr<=mid) return findl(o<<1,l,mid,nl,nr,c);
    else if(nl>mid) return findl(o<<1|1,mid+1,r,nl,nr,c);
    else
    {
        int res1=findl(o<<1|1,mid+1,r,nl,nr,c);
        if(res1!=mid+1) return res1;
        int res2=findl(o<<1,l,mid,nl,nr,c);
        return res2?res2:res1;
    }
}

void dfs1(int u)
{
    sz[u]=1;
    for(int v : g[u])
    {
        dep[v]=dep[u]+1;
        dfs1(v);sz[u]+=sz[v];
        if(sz[v]>sz[hson[u]]) hson[u]=v;
    }
}

void dfs2(int u,int tp)
{
    top[u]=tp;
    dfn[u]=++dfc;
    if(hson[u]) dfs2(hson[u],tp),btm[u]=btm[hson[u]];
    else btm[u]=u;
    for(int v : g[u])
    {
        if(v==hson[u]) continue;
        dfs2(v,v);lst[v]=sz[v];
        upcnt(1,1,n,dfn[u],0,sz[v]);
    }
}

void update(int x,int y,int c)
{
    while(top[x]!=top[y])
    {
        if(dep[top[x]]<dep[top[y]]) swap(x,y);
        int lstcol=qcol(1,1,n,dfn[top[x]]);
        upcol(1,1,n,dfn[top[x]],dfn[x],c);
        upcnt(1,1,n,dfn[fa[top[x]]],lstcol,-lst[top[x]]);
        int r=findr(1,1,n,dfn[x],dfn[btm[x]],c);
        lst[top[x]]=qcnt(1,1,n,dfn[top[x]],r,c)+r-dfn[top[x]]+1;
        upcnt(1,1,n,dfn[fa[top[x]]],c,lst[top[x]]);
        x=fa[top[x]];
    }
    if(dep[x]>dep[y]) swap(x,y);
    int lstcol=qcol(1,1,n,dfn[top[x]]),u=x;
    upcol(1,1,n,dfn[x],dfn[y],c);
    while(top[u]!=1)
    {
        int color=(top[u]==x)?c:lstcol;
        upcnt(1,1,n,dfn[fa[top[u]]],lstcol,-lst[top[u]]);
        int r=findr(1,1,n,dfn[top[u]],dfn[btm[u]],color);
        lst[top[u]]=qcnt(1,1,n,dfn[top[u]],r,color)+r-dfn[top[u]]+1;
        upcnt(1,1,n,dfn[fa[top[u]]],color,lst[top[u]]);
        u=fa[top[u]];
        if(top[u]!=1) lstcol=qcol(1,1,n,dfn[top[u]]);
    }
}

int query(int x)
{
    int c=qcol(1,1,n,dfn[x]),l,r;
    while(1)
    {
        l=findl(1,1,n,dfn[top[x]],dfn[x],c);
        if(fa[top[x]]&&l==dfn[top[x]]&&qcol(1,1,n,dfn[fa[top[x]]])==c) x=fa[top[x]];
        else break;
    }
    r=findr(1,1,n,dfn[x],dfn[btm[x]],c);
    return r-l+1+qcnt(1,1,n,l,r,c);
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=2;i<=n;i++)
    {
        scanf("%d",fa+i);
        g[fa[i]].emplace_back(i);
    }
    dfs1(1);dfs2(1,1);
    build(1,1,n);
    int opt,x,y,c;
    while(m--)
    {
        scanf("%d%d",&opt,&x);
        if(opt==2) printf("%d\n",query(x));
        else scanf("%d%d",&y,&c),update(x,y,c);
    }
    return 0;
}