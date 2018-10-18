#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define INF 0x7fffffff
using namespace std;

struct Edge{int from,to,capa,flow,cost,next;} e[2000000];
int h[5000];
bool vis[5000];
int a[5000];
int p[5000];
int d[5000];
int n,m,s,t;
int sum=-1;

void add_edge(int u,int v,int w,int c)
{
    sum++;
    e[sum].from=u;
    e[sum].to=v;
    e[sum].capa=w;
    e[sum].flow=0;
    e[sum].cost=c;
    e[sum].next=h[u];
    h[u]=sum;
}

bool BellmanFord(int &flow,long long &cost)
{
    for(int i=s;i<=t;i++) d[i]=INF;
    memset(vis,0,sizeof(vis));
    d[s]=0;vis[s]=1;p[s]=0;a[s]=INF;
    queue<int> q;
    q.push(s);
    while(!q.empty())
    {
        int o=q.front();
        for(int tmp=h[o];tmp!=-1;tmp=e[tmp].next)
        {
            if(e[tmp].capa>e[tmp].flow&&d[o]+e[tmp].cost<d[e[tmp].to])
            {
                d[e[tmp].to]=d[o]+e[tmp].cost;
                p[e[tmp].to]=tmp;
                a[e[tmp].to]=min(a[o],e[tmp].capa-e[tmp].flow);
                if(!vis[e[tmp].to]) q.push(e[tmp].to),vis[e[tmp].to]=1;
            }
        }
        q.pop();
        vis[o]=0;
    }
    if(d[t]==INF) return false;
    flow+=a[t];
    cost+=(long long)a[t]*(long long)d[t];
    for(int u=t;u!=s;u=e[p[u]].from)
    {
        e[p[u]].flow+=a[t];
        e[p[u]^1].flow-=a[t];
    }
    return true;
}

long long MincostMaxflow(int &flow)
{
    long long cost=0;
    while(BellmanFord(flow,cost));
    return cost;
}

int main()
{
    int a,b,x,y,z;
    scanf("%d%d%d%d",&n,&m,&a,&b);
    s=0;t=2*n+1;
    for(int i=s;i<=t;i++) h[i]=-1;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&x);
        add_edge(i,i+n,INF,x);
        add_edge(i+n,i,0,-x);
    }
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&x,&y,&z);
        add_edge(x+n,y,INF,z);
        add_edge(y,x+n,0,-z);
        add_edge(y+n,x,INF,z);
        add_edge(x,y+n,0,-z);
    }
    for(int i=1;i<=a;i++)
    {
        scanf("%d%d",&x,&y);
        add_edge(s,y,1,x);
        add_edge(y,s,0,-x);
    }
    long long sum=0;
    for(int i=1;i<=b;i++)
    {
        scanf("%d%d",&x,&y);
        sum+=(long long)x;
        add_edge(y+n,t,1,0);
        add_edge(t,y+n,0,0);
    }
    int flow=0;
    int cost=MincostMaxflow(flow);
    if(flow==b) printf("Yes\n%lld\n",sum-cost);else printf("No\n%d\n",flow);
    return 0;
}
