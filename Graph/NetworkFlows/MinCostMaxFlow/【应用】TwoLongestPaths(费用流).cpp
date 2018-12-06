#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define INF 0x7fffffff
using namespace std;

struct Edge{int from,to,capa,next,flow,cost;} e[2000000];
int h[5000];
int a[5000];
int d[5000];
int p[5000];
bool vis[5000];
int sum,s,t;

void AddEdge(int u,int v,int w,int c)
{
	sum++;
	e[sum].from=u;
	e[sum].to=v;
	e[sum].next=h[u];
	e[sum].capa=w;
	e[sum].flow=0;
	e[sum].cost=c;
	h[u]=sum;
}

void add_edge(int u,int v,int w,int c)
{
	AddEdge(u,v,w,c);
	AddEdge(v,u,0,-c);
}

bool BellmanFord(int &flow,int &cost)
{
	memset(vis,0,sizeof(vis));
	memset(a,0,sizeof(a));
	memset(p,0,sizeof(p));
	for(int i=s;i<=t+5;i++) d[i]=INF;
	a[s]=INF;d[s]=0;vis[s]=1;
	queue<int> q;
	q.push(s);
	while(!q.empty())
	{
		int o=q.front();
		for(int tmp=h[o];tmp!=-1;tmp=e[tmp].next)
			if(e[tmp].capa>e[tmp].flow&&d[o]+e[tmp].cost<d[e[tmp].to])
			{
				d[e[tmp].to]=d[o]+e[tmp].cost;
				a[e[tmp].to]=min(a[o],e[tmp].capa-e[tmp].flow);
				p[e[tmp].to]=tmp;
				if(!vis[e[tmp].to]) vis[e[tmp].to]=1,q.push(e[tmp].to);
			}
		q.pop();
		vis[o]=0;
	}
	if(a[t]==0) return 0;
	flow+=a[t];
	cost+=a[t]*d[t];
	for(int u=t;u!=s;u=e[p[u]].from)
	{
		e[p[u]].flow+=a[t];
		e[p[u]^1].flow-=a[t];
	}
	return 1;
}

int MCMF()
{
	int flow=0,cost=0;
	while(BellmanFord(flow,cost));
	return cost;
}

int main()
{
	int n,m,T,x,y;
	for(cin>>T;T;T--)
	{
		scanf("%d%d",&n,&m);
		sum=-1;
		s=0;t=2*n+1;
		for(int i=s;i<=t+5;i++) h[i]=-1;
		for(int i=1;i<=m;i++)
		{
			scanf("%d%d",&x,&y);
			add_edge(n+x,y,1,0);
		}
		for(int i=1;i<=n;i++)
		{
			add_edge(i,n+i,1,-1);
			add_edge(2*n+2,i,1,0);
			add_edge(n+i,t,1,0);
		}
		add_edge(s,2*n+2,2,0);
		printf("%d\n",-MCMF());
	}
	return 0;
}
