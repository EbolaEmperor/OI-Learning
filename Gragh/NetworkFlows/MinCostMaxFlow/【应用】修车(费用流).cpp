#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define INF 0x7fffffff
using namespace std;

struct Edge{int from,to,capa,next,flow,cost;} e[2000000];
int h[5000],s,t,n,m,sum=-1;
int p[5000],a[5000],d[5000];
bool vis[5000];

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

bool BellmanFord(int &flow,int &cost)
{
	memset(vis,0,sizeof(vis));
	queue<int> q;
	q.push(s);
	for(int i=s;i<=t;i++) d[i]=INF;
	d[s]=0;vis[s]=1;a[s]=INF;
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
	if(d[t]==INF) return 0;
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

int getn(int x,int y){return (x-1)*n+y;}

int main()
{
	int x;
	cin>>m>>n;
	s=0;t=m*n+n+1;
	for(int i=s;i<=t;i++) h[i]=-1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&x);
			for(int k=1;k<=n;k++) add_edge(i,n+getn(j,k),1,x*k);
		}
	for(int i=1;i<=n;i++) add_edge(s,i,1,0);
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			add_edge(n+getn(i,j),t,1,0);
	printf("%.2lf\n",(double)MCMF()/n);
	return 0;
}
