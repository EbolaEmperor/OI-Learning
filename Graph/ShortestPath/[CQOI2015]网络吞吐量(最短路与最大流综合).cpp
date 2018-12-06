#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;

const long long INF=(long long)1e15;
struct Edge{int from,to,next;long long capa,flow;} e[2000000],e_spfa[2000000];
int h[15000],hh[15000];
int n,m,s,t,sum=-1,sum_spfa=-1;
int d[15000],cur[15000];
bool vis[15000];
long long dist[15000],z;
bool link[1000][1000];

void AddEdge(int u,int v,long long w)
{
	sum++;
	e[sum].from=u;
	e[sum].to=v;
	e[sum].capa=w;
	e[sum].flow=0;
	e[sum].next=h[u];
	h[u]=sum;
}

void add_edge(int u,int v,long long w)
{
	AddEdge(u,v,w);
	AddEdge(v,u,0);
}

void add_edge_spfa(int u,int v,long long w)
{
	sum_spfa++;
	e_spfa[sum_spfa].from=u;
	e_spfa[sum_spfa].to=v;
	e_spfa[sum_spfa].capa=w;
	e_spfa[sum_spfa].next=h[u];
	h[u]=sum_spfa;
}

bool BFS()
{
	queue<int> q;
	memset(vis,0,sizeof(vis));
	vis[s]=1;
	d[s]=0;
	q.push(s);
	while(!q.empty())
	{
		int o=q.front();
		for(int tmp=h[o];tmp!=-1;tmp=e[tmp].next)
		{
			if(e[tmp].capa>e[tmp].flow&&vis[e[tmp].to]==0)
			{
				vis[e[tmp].to]=1;
				d[e[tmp].to]=d[o]+1;
				q.push(e[tmp].to);
			}
		}
		q.pop();
	}
	return vis[t];
}

long long DFS(int u,long long a)
{
	long long flow=0,f;
	if(u==t||a==0) return a;
	for(int &tmp=cur[u];tmp!=-1;tmp=e[tmp].next)
	{
		if(d[e[tmp].to]==d[u]+1)
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
	}
	return flow;
}

long long Dinic()
{
	long long flow=0;
	while(BFS())
	{
		for(int i=s;i<=t;i++) cur[i]=h[i];
		flow+=DFS(s,INF);
	}
	return flow;
}

void SPFA()
{
	for(int i=s;i<=t;i++) dist[i]=INF;
	dist[1]=0;
	memset(vis,0,sizeof(vis));
	vis[1]=1;
	queue<int> q;
	q.push(1);
	while(!q.empty())
	{
		int o=q.front();
		for(int tmp=h[o];tmp!=-1;tmp=e_spfa[tmp].next)
		{
			if(dist[o]+e_spfa[tmp].capa<dist[e_spfa[tmp].to])
			{
				dist[e_spfa[tmp].to]=dist[o]+e_spfa[tmp].capa;
				if(!vis[e_spfa[tmp].to]) vis[e_spfa[tmp].to]=1,q.push(e_spfa[tmp].to);
			}
		}
		q.pop();
		vis[o]=0;
	}
}

int main()
{
	int x,y;
	cin>>n>>m;
	s=1;t=2*n;
	for(int i=s;i<=t;i++) h[i]=-1;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%lld",&x,&y,&z);
		add_edge_spfa(x,y,z);
		add_edge_spfa(y,x,z);
	}
	SPFA();
	memset(link,0,sizeof(link));
	for(int i=s;i<=t;i++) hh[i]=h[i],h[i]=-1;
	for(int i=1;i<=n;i++)
		for(int tmp=hh[i];tmp!=-1;tmp=e_spfa[tmp].next)
			if(dist[i]+e_spfa[tmp].capa==dist[e_spfa[tmp].to])
				add_edge(i+n,e_spfa[tmp].to,INF);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&z);
		if(i!=1&&i!=n) add_edge(i,i+n,z);
		else add_edge(i,i+n,INF);
	}
	printf("%lld\n",Dinic());
	return 0;
}
