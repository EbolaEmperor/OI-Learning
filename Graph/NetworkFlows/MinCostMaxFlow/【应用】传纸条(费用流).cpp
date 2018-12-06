#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define INF 0x7fffffff
#define IN 1
#define OUT 0
using namespace std;

struct Edge{int from,to,capa,next,flow,cost;} e[2000000];
int h[10000];
int d[10000],a[10000],p[10000];
bool vis[10000];
int sum=-1,n,m,s,t;

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

int getn(int x,int y,bool Type)
{
	if(Type==IN) return x*n+y;
	else return x*n+y+m*(n+1);
}

bool BellmanFord(int &flow,int &cost)
{
	memset(vis,0,sizeof(vis));
	memset(a,0,sizeof(a));
	for(int i=s;i<=t;i++) d[i]=INF;
	a[s]=INF;vis[s]=1;d[s]=0;
	queue<int> q;
	q.push(s);
	while(!q.empty())
	{
		int o=q.front();
		for(int tmp=h[o];tmp!=-1;tmp=e[tmp].next)
			if(d[o]+e[tmp].cost<d[e[tmp].to]&&e[tmp].capa>e[tmp].flow)
			{
				a[e[tmp].to]=min(a[o],e[tmp].capa-e[tmp].flow);
				d[e[tmp].to]=d[o]+e[tmp].cost;
				p[e[tmp].to]=tmp;
				if(!vis[e[tmp].to]) vis[e[tmp].to]=1,q.push(e[tmp].to);
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

int MCMF()
{
	int flow=0,cost=0;
	while(BellmanFord(flow,cost));
	return cost;
}

int main()
{
	int x;
	cin>>m>>n;
	s=0;t=2*50*(50+1)+5;
	for(int i=s;i<=t;i++) h[i]=-1;
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
		{
			scanf("%d",&x);
			add_edge(getn(i,j,IN),getn(i,j,OUT),1,-x);
		}
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
		{
			if(i<m) add_edge(getn(i,j,OUT),getn(i+1,j,IN),2,0);
			if(j<n) add_edge(getn(i,j,OUT),getn(i,j+1,IN),2,0);
		}
	add_edge(s,getn(1,1,OUT),2,0);
	add_edge(getn(m,n,IN),t,2,0);
	printf("%d\n",-MCMF());
	return 0;
}
