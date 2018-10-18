#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define INF 0x7fffffff
using namespace std;

struct Edge{int from,to,capa,flow,cost,next;} e[2000000];
int h[5100],a[5100],p[5100],d[5100];
bool vis[5100];
int n,s,t;
int sum=-1;

void add_edge(int u,int v,int c1,int c2)
{
	sum++;
	e[sum].from=u;
	e[sum].to=v;
	e[sum].capa=c1;
	e[sum].cost=c2;
	e[sum].flow=0;
	e[sum].next=h[u];
	h[u]=sum;
}

bool BellmanFord(int& flow,long long& cost)
{
	memset(vis,0,sizeof(vis));
	vis[s]=1;
	a[s]=INF;
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
	while(BellmanFord(flow,cost));
	return cost;
}

int main()
{
	cin>>n;
	s=0;
	t=2*n+1;
	for(int i=s;i<=t;i++) h[i]=-1;
	int tmp;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&tmp);
		add_edge(s,i,tmp,0);
		add_edge(i,s,0,0);
		add_edge(n+i,t,tmp,0);
		add_edge(t,n+i,0,0);
	}
	int prince,lowday,fastday,lowcost,fastcost;
	cin>>prince>>fastday>>fastcost>>lowday>>lowcost;
	for(int i=1;i<=n;i++)
	{
		if(i+lowday<=n)
		{
			add_edge(i,n+i+lowday,INF,lowcost);
			add_edge(n+i+lowday,i,0,-lowcost);
		}
		if(i+fastday<=n)
		{
			add_edge(i,n+i+fastday,INF,fastcost);
			add_edge(n+i+fastday,i,0,-fastcost);
		}
		if(i+1<=n)
		{
			add_edge(i,i+1,INF,0);
			add_edge(i+1,i,0,0);
		}
		add_edge(s,n+i,INF,prince);
		add_edge(n+i,s,0,-prince);
	}
	printf("%lld\n",MincostMaxflow());
	return 0;
}
