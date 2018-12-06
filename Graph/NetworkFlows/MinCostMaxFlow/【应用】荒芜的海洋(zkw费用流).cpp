#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define INF 0x7fffffff
using namespace std;

struct Edge{int to,flow,cost,next;} e[2000000];
bool vis[5000];
int dist[5000];
int n,m,s,t,ans=0;
int sum=-1;
int h[5000];

inline void add_edge(int x,int y,int z,int zz)
{
	sum++;
    e[sum].to=y;
	e[sum].flow=z;
	e[sum].cost=zz;
	e[sum].next=h[x];
	h[x]=sum;
}

bool spfa(int s,int t)
{
    memset(vis,0,sizeof(vis));
    for(int i=s;i<=t;i++) dist[i]=INF;
	dist[t]=0;
	vis[t]=1;
    deque<int>q;
	q.push_back(t);
    while(!q.empty())
	{
        int o=q.front();
		q.pop_front();
        for(int k=h[o];k!=-1;k=e[k].next)
			if(e[k^1].flow&&dist[e[k].to]>dist[o]-e[k].cost)
			{
				dist[e[k].to]=dist[o]-e[k].cost;
				if(!vis[e[k].to])
				{
					vis[e[k].to]=1;
					if(!q.empty()&&dist[e[k].to]<dist[q.front()]) q.push_front(e[k].to);
					else q.push_back(e[k].to);
				}
			}
        vis[o]=0;
    }
    return dist[s]<INF;
}

int dfs(int x,int low)
{
    if(x==t){vis[t]=1;return low;}
    int used=0,a;vis[x]=1;
    for(int k=h[x];k!=-1;k=e[k].next)
		if(!vis[e[k].to]&&e[k].flow&&dist[x]-e[k].cost==dist[e[k].to])
			{
				a=dfs(e[k].to,min(e[k].flow,low-used));
				if(a) ans+=a*e[k].cost,e[k].flow-=a,e[k^1].flow+=a,used+=a;
				if(used==low)break;
			}
    return used;
}

int ZkwCostFlow()
{
    int flow=0;
    while(spfa(s,t))
	{
        vis[t]=1;
        while(vis[t])
		{
            memset(vis,0,sizeof(vis));
            flow+=dfs(s,INF);
        }
    }
    return flow;
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
	int flow=ZkwCostFlow();
	if(flow==b) printf("Yes\n%lld\n",sum-ans);else printf("No\n%d\n",flow);
	return 0;
}
