#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define INF 0x7fffffff
using namespace std;

struct Edge{int from,to,capa,flow,cost,next;} e[2000000];
int h[300],a[300],p[300],d[300];
bool vis[300];
int sum=-1;
int n,m,s,t;

void add_edge(int u,int v,int capa,int cost)
{
	sum++;
	e[sum].from=u;
	e[sum].to=v;
	e[sum].capa=capa;
	e[sum].cost=cost;
	e[sum].flow=0;
	e[sum].next=h[u];
	h[u]=sum;
}

bool BellmanFord_Min(int& flow,long long& cost)
{
	memset(vis,0,sizeof(vis));
	memset(a,0,sizeof(a));
	a[s]=INF;
	vis[s]=1;
	for(int i=s;i<=t;i++) d[i]=INF;
	d[s]=0;
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
				a[e[tmp].to]=min(a[o],e[tmp].capa-e[tmp].flow);
				p[e[tmp].to]=tmp;
				if(!vis[e[tmp].to]) vis[e[tmp].to]=1,q.push(e[tmp].to);
			}
		}
		q.pop();
		vis[o]=0;
	}
	if(d[t]==INF) return false;
	flow+=a[t];
	cost+=(long long)a[t]*(long long)d[t];
	for(int i=t;i!=s;i=e[p[i]].from)
	{
		e[p[i]].flow+=a[t];
		e[p[i]^1].flow-=a[t];
	}
	return true;
}

long long MincostMaxflow()
{
	int flow=0;
	long long cost=0;
	while(BellmanFord_Min(flow,cost));
	return cost;
}

bool BellmanFord_Max(int& flow,long long& cost)
{
	memset(vis,0,sizeof(vis));
	memset(a,0,sizeof(a));
	a[s]=INF;
	vis[s]=1;
	for(int i=s;i<=t;i++) d[i]=-INF;
	d[s]=0;
	queue<int> q;
	q.push(s);
	while(!q.empty())
	{
		int o=q.front();
		for(int tmp=h[o];tmp!=-1;tmp=e[tmp].next)
		{
			if(e[tmp].capa>e[tmp].flow&&d[o]+e[tmp].cost>d[e[tmp].to])
			{
				d[e[tmp].to]=d[o]+e[tmp].cost;
				a[e[tmp].to]=min(a[o],e[tmp].capa-e[tmp].flow);
				p[e[tmp].to]=tmp;
				if(!vis[e[tmp].to]) vis[e[tmp].to]=1,q.push(e[tmp].to);
			}
		}
		q.pop();
		vis[o]=0;
	}
	if(d[t]==-INF) return false;
	flow+=a[t];
	cost+=(long long)a[t]*(long long)d[t];
	for(int i=t;i!=s;i=e[p[i]].from)
	{
		e[p[i]].flow+=a[t];
		e[p[i]^1].flow-=a[t];
	}
	return true;
}

long long MaxcostMaxflow()
{
	int flow=0;
	long long cost=0;
	while(BellmanFord_Max(flow,cost));
	return cost;
}

int main()
{
	int x;
	cin>>m>>n;
	s=0;
	t=m+n+1;
	for(int i=s;i<=t;i++) h[i]=-1;
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&x);
		add_edge(s,i,x,0);
		add_edge(i,s,0,0);
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		add_edge(m+i,t,x,0);
		add_edge(t,m+i,0,0);
	}
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
		{
			scanf("%d",&x);
			add_edge(i,m+j,INF,x);
			add_edge(m+j,i,0,-x);
		}
	printf("%lld\n",MincostMaxflow());
	for(int i=0;i<=10*n*m;i++) e[i].flow=0;
	printf("%lld\n",MaxcostMaxflow());
	return 0;
}
