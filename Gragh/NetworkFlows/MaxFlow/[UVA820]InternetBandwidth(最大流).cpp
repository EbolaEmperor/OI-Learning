#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define INF 0x7fffffff
using namespace std;

struct Edge{int from,to,capa,next,flow;} e[2000000];
int h[5000],sum,n,s,t;
int d[5000],cur[5000];
bool vis[5000];

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
	vis[s]=1;d[s]=0;
	queue<int> q;
	q.push(s);
	while(!q.empty())
	{
		int o=q.front();
		for(int tmp=h[o];tmp!=-1;tmp=e[tmp].next)
			if((!vis[e[tmp].to])&&e[tmp].capa>e[tmp].flow)
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
				e[tmp].flow+=f;
				e[tmp^1].flow-=f;
				flow+=f;
				a-=f;
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
		for(int i=1;i<=n;i++) cur[i]=h[i];
		flow+=DFS(s,INF);
	}
	return flow;
}

int main()
{
	int m,x,y,z,T=0;
	while(~scanf("%d",&n)&&n)
	{
		sum=-1;
		for(int i=1;i<=n;i++) h[i]=-1;
		scanf("%d%d%d",&s,&t,&m);
		for(int i=1;i<=m;i++)
		{
			scanf("%d%d%d",&x,&y,&z);
			add_edge(x,y,z);
			add_edge(y,x,z);
		}
		printf("Network %d\nThe bandwidth is %d.\n\n",++T,Dinic());
	}
	return 0;
}
