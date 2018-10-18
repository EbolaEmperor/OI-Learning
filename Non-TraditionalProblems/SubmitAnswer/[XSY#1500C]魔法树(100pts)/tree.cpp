#include<bits/stdc++.h>
using namespace std;

const int N=1010;
struct Edge{int to,next;} e[N<<1];
int h[N],esum,n,sz[N];
int sum,root,msz[N];
bool done[N];
int wrong=0;

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
    sz[u]=1;
    for(int t=h[u];t;t=e[t].next)
    {
        int v=e[t].to;
        if(v==fa||done[v]) continue;
        dfs(v,u);sz[u]+=sz[v];
    }
}

void solve(int u)
{
    done[u]=1;dfs(u,0);
    for(int t=h[u];t;t=e[t].next)
    {
        int v=e[t].to;
        if(done[v]) continue;
        sum=sz[v];root=0;find(v,u);
        if(msz[root]!=msz[v]) wrong++;
        solve(v);
    }
}

int main()
{
    int T,u,v;msz[0]=INT_MAX;
    for(scanf("%d%d",&T,&n);T;T--)
    {
        memset(h,0,sizeof(h));esum=0;
        memset(done,0,sizeof(done));
        for(int i=1;i<n;i++)
        {
            scanf("%d%d",&u,&v);
            add_edge(u,v);
            add_edge(v,u);
        }
        root=0;sum=n;find(1,0);
        wrong=0;solve(root);
        puts(wrong<0.1*n?"Yes":"No");
    }
    return 0;
}