#include<bits/stdc++.h>
using namespace std;

const int N=100010;
typedef long long LL;
struct Edge{int to,next;} e[N<<1];
int h[N],esum=0,n,a[N],g[N];
int mxsz[N],sz[N],root,sum;
bool done[N];
int cnt[N],rec[N],cc=0;
LL ans=0;
vector<int> p[N];

void add_edge(int u,int v)
{
    e[++esum].to=v;
    e[esum].next=h[u];
    h[u]=esum;
}

void prework(int n)
{
    for(int i=1;i<=n;i++)
    {
        int x=i;
        for(int j=2;j*j<=x;j++)
        {
            if(x%j==0) p[i].push_back(j);
            while(x%j==0) x/=j;
        }
        if(x>1) p[i].push_back(x);
    }
}

void find(int u,int la)
{
    mxsz[u]=0;sz[u]=1;
    for(int t=h[u];t;t=e[t].next)
    {
        int v=e[t].to;
        if(v==la||done[v]) continue;
        find(v,u);sz[u]+=sz[v];
        mxsz[u]=max(mxsz[u],sz[v]);
    }
    mxsz[u]=max(mxsz[u],sum-sz[u]);
    if(mxsz[u]<mxsz[root]) root=u;
}

void gao1(int u,int la)
{
    int sz=p[g[u]].size();
    for(int s=1;s<(1<<sz);s++)
    {
        int cur=1,ccc=0;
        for(int i=0;i<sz;i++)
            if(s&(1<<i)) ccc++,cur*=p[g[u]][i];
        if(ccc&1) ans+=cnt[cur];
        else ans-=cnt[cur];
    }
    for(int t=h[u];t;t=e[t].next)
    {
        int v=e[t].to;
        if(v==la||done[v]) continue;
        g[v]=__gcd(g[u],a[v]);
        gao1(v,u);
    }
}

void gao2(int u,int la)
{
    int sz=p[g[u]].size();
    for(int s=1;s<(1<<sz);s++)
    {
        int cur=1;
        for(int i=0;i<sz;i++)
            if(s&(1<<i)) cur*=p[g[u]][i];
        if(!cnt[cur]) rec[++cc]=cur;
        cnt[cur]++;
    }
    for(int t=h[u];t;t=e[t].next)
    {
        int v=e[t].to;
        if(v==la||done[v]) continue;
        gao2(v,u);
    }
}

void solve(int u)
{
    done[u]=1;cc=0;g[u]=a[u];
    int siz=p[a[u]].size();
    for(int s=1;s<(1<<siz);s++)
    {
        int cur=1;
        for(int i=0;i<siz;i++)
            if(s&(1<<i)) cur*=p[a[u]][i];
        if(!cnt[cur]) rec[++cc]=cur;
        cnt[cur]++;
    }
    for(int t=h[u];t;t=e[t].next)
    {
        int v=e[t].to;
        if(done[v]) continue;
        g[v]=__gcd(g[u],a[v]);
        gao1(v,u);gao2(v,u);
    }
    for(int i=1;i<=cc;i++) cnt[rec[i]]=0;
    for(int t=h[u];t;t=e[t].next)
    {
        int v=e[t].to;
        if(done[v]) continue;
        sum=sz[u];root=0;find(v,u);
        solve(root);
    }
}

int main()
{
    prework(100000);
    scanf("%d",&n);
    for(int i=1,u,v;i<n;i++)
    {
        scanf("%d%d",&u,&v);
        add_edge(u,v);
        add_edge(v,u);
    }
    for(int i=1;i<=n;i++) scanf("%d",a+i);
    mxsz[root=0]=n+1;sum=n;
    find(1,0);solve(root);
    printf("%lld\n",1ll*n*(n-1)/2-ans);
    return 0;
}