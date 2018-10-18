#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define INF 0x3fffffff
using namespace std;

struct Edge{int from,to,capa,flow,next;} e[2000000];
int h[5000];
int n,m,s,t,sum;
int d[5000],cur[5000];
bool vis[5000];
int froms[5000],tos[5000];

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

int DFS(int u,int a)
{
	int flow=0,f;
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

int Dinic()
{
	int flow=0;
	while(BFS())
	{
		for(int i=0;i<2*n+5;i++) cur[i]=h[i];
		flow+=DFS(s,INF);
	}
	return flow;
}

int solve(int u,int v)
{
	s=u+n;t=v;
	for(int i=0;i<2*n+5;i++) h[i]=-1;
	sum=-1;
	for(int i=1;i<=m;i++)
	{
		add_edge(froms[i]+n,tos[i],INF);
		add_edge(tos[i]+n,froms[i],INF);
	}
	for(int i=0;i<n;i++) add_edge(i,i+n,1);
	return Dinic();
}

int main()
{
	while(scanf("%d%d",&n,&m)==2)
	{
		for(int i=1;i<=m;i++) scanf(" (%d,%d)",froms+i,tos+i);
		int ans=INF;
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				if(i!=j) ans=min(ans,solve(i,j));
		if(ans>n||ans<0) ans=n;
		printf("%d\n",ans);
	}
	return 0;
}
