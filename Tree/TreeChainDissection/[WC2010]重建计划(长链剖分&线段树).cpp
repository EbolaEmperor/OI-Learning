#include<bits/stdc++.h>
using namespace std;

const double eps=1e-4;
const double INF=1e15;
const int N=100010;
struct Edge{int to,next;double capa;} e[N<<1];
int h[N],sum=0,n,L,R;
int fa[N],lson[N];
int mxdep[N],dep[N];
int dfn[N],dfc=0;
double val[N<<1];
double dis[N],ans,tans[N];
double mx[N<<2];
int idx[N];

void add_edge(int u,int v,double w)
{
    e[++sum].to=v;
    e[sum].capa=w;
    e[sum].next=h[u];
    val[sum]=w;
    h[u]=sum;
}

void dfs1(int u)
{
    mxdep[u]=dep[u]=dep[fa[u]]+1;
    for(int tmp=h[u];tmp;tmp=e[tmp].next)
    {
        int v=e[tmp].to;
        if(v==fa[u]) continue;
        fa[v]=u;dfs1(v);
        mxdep[u]=max(mxdep[u],mxdep[v]);
        if(mxdep[v]>mxdep[lson[u]]) lson[u]=v;
    }
}

void dfs2(int u)
{
    dfn[u]=++dfc;
    if(lson[u]) dfs2(lson[u]);
    for(int tmp=h[u];tmp;tmp=e[tmp].next)
        if(e[tmp].to!=fa[u]&&e[tmp].to!=lson[u])
            dfs2(e[tmp].to);
}

void build(int o,int l,int r)
{
    mx[o]=-INF;
    if(l==r){idx[l]=o;return;}
    int mid=(l+r)/2;
    build(o<<1,l,mid);
    build(o<<1|1,mid+1,r);
}

void update(int o,int l,int r,int k,double x)
{
    if(l==r){mx[o]=max(mx[o],x);return;}
    int mid=(l+r)/2;
    if(k<=mid) update(o<<1,l,mid,k,x);
    else update(o<<1|1,mid+1,r,k,x);
    mx[o]=max(mx[o<<1],mx[o<<1|1]);
}

double query(int o,int l,int r,int nl,int nr)
{
    if(l>=nl&&r<=nr) return mx[o];
    int mid=(l+r)/2;double res=-INF;
    if(nl<=mid) res=max(res,query(o<<1,l,mid,nl,nr));
    if(nr>mid) res=max(res,query(o<<1|1,mid+1,r,nl,nr));
    return res;
}

void dp(int u)
{
    update(1,1,n,dfn[u],dis[u]);
    for(int tmp=h[u];tmp;tmp=e[tmp].next)
        if(e[tmp].to==lson[u])
        {
            dis[e[tmp].to]=dis[u]+e[tmp].capa;
            dp(e[tmp].to);
        }
    for(int tmp=h[u];tmp;tmp=e[tmp].next)
    {
        int v=e[tmp].to;
        if(v==fa[u]||v==lson[u]) continue;
        dis[v]=dis[u]+e[tmp].capa;
        dp(v);
        for(int i=1;i<=mxdep[v]-dep[u];i++)
        {
            tans[i]=mx[idx[dfn[v]+i-1]];
            if(i<=R) ans=max(ans,query(1,1,n,max(dfn[u],dfn[u]+L-i),min(dfn[u]+mxdep[u]-dep[u],dfn[u]+R-i))+tans[i]-2*dis[u]);
        }
        for(int i=1;i<=mxdep[v]-dep[u];i++)
            update(1,1,n,dfn[u]+i,tans[i]);
    }
    ans=max(ans,query(1,1,n,dfn[u]+L,min(dfn[u]+R,dfn[u]+mxdep[u]-dep[u]))-dis[u]);
}

int main()
{
    int u,v;double w;
    scanf("%d%d%d",&n,&L,&R);
    for(int i=1;i<n;i++)
    {
        scanf("%d%d%lf",&u,&v,&w);
        add_edge(u,v,w);
        add_edge(v,u,w);
    }
    dfs1(1);dfs2(1);
    double l=0,r=1e6,mid;
    while(r-l>eps)
    {
        mid=(l+r)/2;
        for(int i=1;i<=sum;i++)
            e[i].capa=val[i]-mid;
        build(1,1,n);
        ans=-INF;dis[1]=0;dp(1);
        if(ans>=0) l=mid;
        else r=mid;
    }
    printf("%.3lf\n",l);
    return 0;
}