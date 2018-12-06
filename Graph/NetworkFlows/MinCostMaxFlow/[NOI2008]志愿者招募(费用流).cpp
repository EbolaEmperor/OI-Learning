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

long long MincostMaxflow()
{
    int flow=0;
    long long cost=0;
    while(BellmanFord(flow,cost));
    return cost;
}

int main()
{
    int x,y,z;
    cin>>n>>m;
    s=0;t=n+2;
    for(int i=s;i<=t;i++) h[i]=-1;
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&x);
        add_edge(i,i+1,INF-x,0);
        add_edge(i+1,i,0,0);
    }
    add_edge(s,1,INF,0);
    add_edge(1,s,0,0);
    add_edge(n+1,t,INF,0);
    add_edge(t,n+1,0,0);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&x,&y,&z);
        add_edge(x,y+1,INF,z);
        add_edge(y+1,x,0,-z);
    }
    printf("%lld\n",MincostMaxflow());
    return 0;
}
