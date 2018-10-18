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
int n,s,t;
int sum=-1;

void AddEdge(int u,int v,int w,int c)
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

void add_edge(int u,int v,int w,int c)
{
	AddEdge(u,v,w,c);
	AddEdge(v,u,0,-c);
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
	int tt,c,r,x,y;
	cin>>tt;
	for(int T=1;T<=tt;T++)
	{
		scanf("%d%d%d",&n,&c,&r);
		sum=-1;
		int cnt=0;
		s=0;t=2*n+5;
		for(int i=s;i<=t;i++) h[i]=-1;
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&x);
			add_edge(i,t,x,0);
			add_edge(s,i+n,x,0);
			cnt+=x;
		}
		for(int i=1;i<=c;i++)
		{
			scanf("%d%d",&x,&y);
			add_edge(s,1,x,y);
		}
		for(int i=1;i<n;i++) add_edge(i,i+1,INF,0);
		for(int i=1;i<=r;i++)
		{
			scanf("%d%d",&x,&y);
			for(int j=1;j<=n-x-1;j++) add_edge(j+n,j+x+1,INF,y);
		}
		int flow=0;
		long long cost=MincostMaxflow(flow);
		printf("Case %d: ",T);
		if(flow==cnt) printf("%lld\n",cost);
		else puts("impossible");
	}
	return 0;
}
