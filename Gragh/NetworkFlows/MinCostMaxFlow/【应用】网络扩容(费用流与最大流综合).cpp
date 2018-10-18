#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define INF 0x7fffffff
using namespace std;

struct Edge{int from,to,capa,next,flow,cost;} e[2000000],r[2000000];
int h[5000];
int deep[5000],cur[5000];     //Dinic相关
int d[5000],a[5000],p[5000];     //费用流相关
bool vis[5000];
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

bool BFS()
{
	memset(vis,0,sizeof(vis));
	queue<int> q;
	deep[s]=0;vis[s]=1;
	q.push(s);
	while(!q.empty())
	{
		int o=q.front();
		for(int tmp=h[o];tmp!=-1;tmp=e[tmp].next)
			if((!vis[e[tmp].to])&&e[tmp].capa>e[tmp].flow)
			{
				deep[e[tmp].to]=deep[o]+1;
				vis[e[tmp].to]=1;
				q.push(e[tmp].to);
			}
		q.pop();
	}
	return vis[t];
}

int DFS(int u,int a)
{
	if(u==t||a==0) return a;
	int flow=0,f;
	for(int &tmp=cur[u];tmp!=-1;tmp=e[tmp].next)
		if(deep[e[tmp].to]==deep[u]+1)
		{
			f=DFS(e[tmp].to,min(a,e[tmp].capa-e[tmp].flow));
			if(f>0)
			{
				flow+=f;
				a-=f;
				e[tmp].flow+=f;
				e[tmp^1].flow-=f;
				if(a==0) break;
			}
		}
	return flow;
}

int Dinic()
{
	int flow=0;
	while(BFS())
	{
		for(int i=s;i<=t;i++) cur[i]=h[i];
		flow+=DFS(s,INF);
	}
	return flow;
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
	int k;
	cin>>n>>m>>k;
	for(int i=1;i<=m;i++) scanf("%d%d%d%d",&r[i].from,&r[i].to,&r[i].capa,&r[i].cost);
	s=1;t=n;
	for(int i=s;i<=t;i++) h[i]=-1;
	for(int i=1;i<=m;i++) add_edge(r[i].from,r[i].to,r[i].capa,0);
	int flow=Dinic();
	for(int i=1;i<=m;i++) add_edge(r[i].from,r[i].to,k,r[i].cost);
	h[0]=-1;s=0;
	add_edge(s,1,k,0);
	int cost=MCMF();
	printf("%d %d\n",flow,cost);
	return 0;
}
