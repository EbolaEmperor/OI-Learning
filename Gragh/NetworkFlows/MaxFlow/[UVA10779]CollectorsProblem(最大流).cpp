#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define INF 0x7fffffff
using namespace std;

struct Edge{int from,to,capa,next,flow;} e[2000000];
int h[5000];
bool vis[5000];
int cur[5000];
int sum,n,m,s,t;
int d[5000];
int a[50];

void AddEdge(int u,int v,int w)
{
	sum++;
	e[sum].from=u;
	e[sum].to=v;
	e[sum].capa=w;
	e[sum].flow=0;
	e[sum].next=h[u];
	h[u]=sum;
}

void add_edge(int u,int v,int w)
{
	AddEdge(u,v,w);
	AddEdge(v,u,0);
}

bool BFS()
{
	memset(vis,0,sizeof(vis));
	d[s]=0;
	vis[s]=1;
	queue<int> q;
	q.push(s);
	while(!q.empty())
	{
		int o=q.front();
		for(int tmp=h[o];tmp!=-1;tmp=e[tmp].next)
			if(e[tmp].capa>e[tmp].flow&&vis[e[tmp].to]==0)
			{
				vis[e[tmp].to]=1;
				d[e[tmp].to]=d[o]+1;
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

int main()
{
	int tt,k,x;
	cin>>tt;
	for(int T=1;T<=tt;T++)
	{
		scanf("%d%d",&n,&m);
		s=0;t=n+m;
		for(int i=s;i<=t;i++) h[i]=-1;
		sum=-1;
		memset(a,0,sizeof(a));
		scanf("%d",&k);
		for(int i=1;i<=k;i++)
		{
			scanf("%d",&x);
			a[x]++;
		}
		for(int i=1;i<=m;i++)
			if(a[i]>0) add_edge(s,i,a[i]);
		for(int i=1;i<n;i++)
		{
			scanf("%d",&k);
			memset(a,0,sizeof(a));
			for(int j=1;j<=k;j++)
			{
				scanf("%d",&x);
				a[x]++;
			}
			for(int j=1;j<=m;j++)
				if(a[j]==0) add_edge(j,m+i,1);
				else add_edge(m+i,j,a[j]-1);
		}
		for(int i=1;i<=m;i++) add_edge(i,t,1);
		printf("Case #%d: %d\n",T,Dinic());
	}
	return 0;
}
