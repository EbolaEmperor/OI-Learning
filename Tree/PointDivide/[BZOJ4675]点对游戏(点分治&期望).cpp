#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=50010;
struct Edge{int to,next;} e[N<<1];
int h[N],esum=0,n,m;
int root,msz[N],sum;
int mxd[N],sz[N],lim;
int lucky[15];LL luck;
bool done[N];
int f[N],g[N];

void add_edge(int u,int v)
{
    e[++esum].to=v;
    e[esum].next=h[u];
    h[u]=esum;
}

void find(int u,int fa)
{
    sz[u]=1;msz[u]=0;
    for(int t=h[u];t;t=e[t].next)
    {
        int v=e[t].to;
        if(v==fa||done[v]) continue;
        find(v,u);
        sz[u]+=sz[v];
        msz[u]=max(msz[u],sz[v]);
    }
    msz[u]=max(msz[u],sum-sz[u]);
    if(msz[u]<msz[root]) root=u;
}

void dfs(int u,int fa)
{
    mxd[u]=0;sz[u]=1;
    for(int t=h[u];t;t=e[t].next)
    {
        int v=e[t].to;
        if(v==fa||done[v]) continue;
        dfs(v,u);sz[u]+=sz[v];
        mxd[u]=max(mxd[u],mxd[v]+1);
    }
}

void solve(int u,int fa,int dep)
{
    g[dep]++;lim=max(lim,dep);
    for(int i=1;i<=m;i++)
        if(dep<=lucky[i]) luck+=f[lucky[i]-dep];
    for(int t=h[u];t;t=e[t].next)
    {
        int v=e[t].to;
        if(v==fa||done[v]) continue;
        solve(v,u,dep+1);
    }
}

void gao(int u)
{
    done[u]=1;dfs(u,0);f[0]=1;
    for(int t=h[u];t;t=e[t].next)
    {
        int v=e[t].to;
        if(done[v]) continue;
        lim=0;solve(v,u,1);
        for(int i=1;i<=lim;i++) f[i]+=g[i],g[i]=0;
    }
    memset(f,0,sizeof(int)*(mxd[u]+2));
    for(int t=h[u];t;t=e[t].next)
    {
        int v=e[t].to;
        if(done[v]) continue;
        sum=sz[v];root=0;
        find(v,u);gao(root);
    }
}

int main()
{
    int u,v;
    msz[0]=INT_MAX;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++) scanf("%d",lucky+i);
    for(int i=1;i<n;i++)
    {
        scanf("%d%d",&u,&v);
        add_edge(u,v);
        add_edge(v,u);
    }
    sum=n;root=0;find(1,0);gao(root);
    int k[3]={(n+2)/3,(n+1)/3,n/3};
    for(int i=0;i<3;i++)
    {
        double ans=1.0*luck*k[i]*(k[i]-1)/(1.0*n*(n-1));
        printf("%.2lf\n",ans);
    }
    return 0;
}