#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define INF 0x7fffffff
using namespace std;

int n,s,t;
int h[300],a[300],d[300],p[300];
bool vis[300];
struct Edge{int from,to,capa,cost,flow,next;} e[200000];
int sum=-1;

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

bool BellmanFord_Min(int& flow,int& cost)
{
	for(int i=s;i<=t;i++) d[i]=INF;
	memset(vis,0,sizeof(vis));
	memset(a,0,sizeof(a));
	d[s]=0;
	vis[s]=1;
	a[s]=INF;
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
				if(!vis[e[tmp].to]) vis[e[tmp].to]=1,q.push(e[tmp].to);
			}
		}
		q.pop();
		vis[o]=0;
	}
	if(d[t]==INF) return false;
	flow+=a[t];
	cost+=a[t]*d[t];
	for(int i=t;i!=s;i=e[p[i]].from)
	{
		e[p[i]].flow+=a[t];
		e[p[i]^1].flow-=a[t];
	}
	return true;
}

int MincostMaxflow()
{
	int flow=0,cost=0;
	while(BellmanFord_Min(flow,cost));
	return cost;
}

bool BellmanFord_Max(int& flow,int& cost)
{
	for(int i=s;i<=t;i++) d[i]=-INF;
	memset(vis,0,sizeof(vis));
	memset(a,0,sizeof(a));
	d[s]=0;
	vis[s]=1;
	a[s]=INF;
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
				p[e[tmp].to]=tmp;
				a[e[tmp].to]=min(a[o],e[tmp].capa-e[tmp].flow);
				if(!vis[e[tmp].to]) vis[e[tmp].to]=1,q.push(e[tmp].to);
			}
		}
		q.pop();
		vis[o]=0;
	}
	if(d[t]==-INF) return false;
	flow+=a[t];
	cost+=a[t]*d[t];
	for(int i=t;i!=s;i=e[p[i]].from)
	{
		e[p[i]].flow+=a[t];
		e[p[i]^1].flow-=a[t];
	}
	return true;
}

int MaxcostMaxflow()
{
	int flow=0,cost=0;
	while(BellmanFord_Max(flow,cost));
	return cost;
}

int main()
{
	int x;
	cin>>n;
	s=0;
	t=2*n+1;
	for(int i=s;i<=t;i++) h[i]=-1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			scanf("%d",&x);
			add_edge(i,j+n,1,x);
			add_edge(j+n,i,0,-x);
		}
	for(int i=1;i<=n;i++)
	{
		add_edge(s,i,1,0);
		add_edge(i,s,0,0);
		add_edge(i+n,t,1,0);
		add_edge(t,i+n,0,0);
	}
	printf("%d\n",MincostMaxflow());
	for(int i=0;i<=10*n*n;i++) e[i].flow=0;
	printf("%d\n",MaxcostMaxflow());
	return 0;
}
