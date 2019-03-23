#include<bits/stdc++.h>
using namespace std;

const int INF=1e9;
const int N=100010,M=N*700;
vector<int> g[N];
int trdep[N],rt[20][N],dis[20][N];
int sz[N],root,sum=0,msz[N],n,m;
bool done[N],ins[N];

inline int upmin(int &x,const int &y){if(y<x) x=y;}
inline int upmax(int &x,const int &y){if(y>x) x=y;}

void find(int u,int la)
{
    sz[u]=1;msz[u]=0;
    for(int v : g[u])
    {
        if(v==la||done[v]) continue;
        find(v,u);sz[u]+=sz[v];
        upmax(msz[u],sz[v]);
    }
    upmax(msz[u],sum-sz[u]);
    if(msz[u]<msz[root]) root=u;
}

void getdis(int u,int la,int d,int r)
{
    rt[d][u]=r;sz[u]=1;
    for(int v : g[u])
    {
        if(v==la||done[v]) continue;
        dis[d][v]=dis[d][u]+1;
        getdis(v,u,d,r);
        sz[u]+=sz[v];
    }
}

void build(int u)
{
    done[u]=1;
    getdis(u,0,trdep[u],u);
    for(int v : g[u])
    {
        if(done[v]) continue;
        sum=sz[v];root=0;find(v,u);
        trdep[root]=trdep[u]+1;
        build(root);
    }
}

int rtrt[N],cur=0,rtc=0;
int lc[M],rc[M],val[M],tot=0;

int qrt(int o,int l,int r,int k)
{
    if(!o) return 0;
    if(l==r) return val[o];
    int mid=(l+r)/2;
    if(k<=mid) return qrt(lc[o],l,mid,k);
    else return qrt(rc[o],mid+1,r,k);
}

void uprt(int &o,int p,int l,int r,int k,int x)
{
    o=++tot;
    if(l==r){val[o]=x;return;}
    int mid=(l+r)/2;
    if(k<=mid) uprt(lc[o],lc[p],l,mid,k,x),rc[o]=rc[p];
    else uprt(rc[o],rc[p],mid+1,r,k,x),lc[o]=lc[p];
}

void upval(int &o,int p,int l,int r,int k,int x)
{
    o=++tot;
    if(l==r){val[o]=(val[p]==x?INF:x);return;}
    int mid=(l+r)/2;
    if(k<=mid) upval(lc[o],lc[p],l,mid,k,x),rc[o]=rc[p];
    else upval(rc[o],rc[p],mid+1,r,k,x),lc[o]=lc[p];
    val[o]=min(val[lc[o]],val[rc[o]]);
}

void update(int u)
{
    rtrt[++rtc]=rtrt[cur];
    for(int k=0;k<=trdep[u];k++)
    {
        int segrt=qrt(rtrt[rtc],1,n,rt[k][u]);
        upval(segrt,segrt,1,n,u,dis[k][u]);
        uprt(rtrt[rtc],rtrt[rtc],1,n,rt[k][u],segrt);
    }
    cur=rtc;
}

int query(int u)
{
    int ans=INF;
    for(int k=0;k<=trdep[u];k++)
    {
        int segrt=qrt(rtrt[cur],1,n,rt[k][u]);
        if(!segrt) continue;
        upmin(ans,dis[k][u]+val[segrt]);
    }
    return ans;
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
    msz[0]=n+1;sum=n;find(1,0);build(root);
    scanf("%d",&m);val[0]=INF;
    int opt,x,ans=0;
    while(m--)
    {
        scanf("%d%d",&opt,&x);x^=ans;
        if(opt==1) update(x);
        if(opt==2) printf("%d\n",ans=query(x));
        if(opt==3) cur=x;
    }
    return 0;
}