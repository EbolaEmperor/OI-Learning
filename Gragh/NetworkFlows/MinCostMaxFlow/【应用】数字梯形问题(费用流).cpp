#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define INF 0x7fffffff
#define IN 0
#define OUT 1
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

int x[50][50];

int getn(int i,int j,bool ty)
{
	int gn=(i-1)*(m+n)+j;
	return gn+1500*ty;
}

int main()
{
	cin>>m>>n;
	s=0;t=3100;
	sum=-1;
	for(int i=s;i<=t;i++) h[i]=-1;
	for(int i=1;i<=m;i++) add_edge(s,getn(1,i,IN),1,0);
	for(int i=1;i<=n+m-1;i++) add_edge(getn(n,i,OUT),t,INF,0);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m+i-1;j++)
		{
			scanf("%d",&x[i][j]);
			add_edge(getn(i,j,IN),getn(i,j,	OUT),1,-x[i][j]);
			add_edge(getn(i,j,OUT),getn(i+1,j,IN),1,0);
			add_edge(getn(i,j,OUT),getn(i+1,j+1,IN),1,0);
		}
	printf("%d\n",-MCMF());
	sum=-1;
	for(int i=s;i<=t;i++) h[i]=-1;
	for(int i=1;i<=m;i++) add_edge(s,getn(1,i,IN),1,0);
	for(int i=1;i<=n+m-1;i++) add_edge(getn(n,i,OUT),t,INF,0);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m+i-1;j++)
		{
			add_edge(getn(i,j,IN),getn(i,j,	OUT),INF,-x[i][j]);
			add_edge(getn(i,j,OUT),getn(i+1,j,IN),1,0);
			add_edge(getn(i,j,OUT),getn(i+1,j+1,IN),1,0);
		}
	printf("%d\n",-MCMF());
	sum=-1;
	for(int i=s;i<=t;i++) h[i]=-1;
	for(int i=1;i<=m;i++) add_edge(s,getn(1,i,IN),1,0);
	for(int i=1;i<=n+m-1;i++) add_edge(getn(n,i,OUT),t,INF,0);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m+i-1;j++)
		{
			add_edge(getn(i,j,IN),getn(i,j,	OUT),INF,-x[i][j]);
			add_edge(getn(i,j,OUT),getn(i+1,j,IN),INF,0);
			add_edge(getn(i,j,OUT),getn(i+1,j+1,IN),INF,0);
		}
	printf("%d\n",-MCMF());
	return 0;
}
