#include<bits/stdc++.h>
#define INF 0x7fffffff
using namespace std;

const int N=50010;
struct Edge{int to,capa,flow,next;} e[300010];
int h[N],sum=-1,s,t,tot,n,m,dafa=0;
int vis[N],d[N],cur[N];

void AddEdge(int u,int v,int w)
{
	e[++sum].to=v;
	e[sum].capa=w;
	e[sum].flow=0;
	e[sum].next=h[u];
	h[u]=sum;
}

void add_edge(int u,int v,int w)
{
	AddEdge(u,v,w);
	AddEdge(v,u,w);
}

bool BFS()
{
	memset(vis,0,sizeof(vis));
	queue<int> q;
	q.push(s);
	vis[s]=1;d[s]=0;
	while(!q.empty())
	{
		int u=q.front();
		for(int tmp=h[u];~tmp;tmp=e[tmp].next)
		{
			int v=e[tmp].to;
			if(!vis[v]&&e[tmp].capa>e[tmp].flow)
			{
				d[v]=d[u]+1;
				vis[v]=1;
				q.push(v);
			}
		}
		q.pop();
	}
	return vis[t];
}

int DFS(int u,int a)
{
	if(u==t||a==0) return a;
	int flow=0,f;
	for(int& tmp=cur[u];~tmp;tmp=e[tmp].next)
		if(d[e[tmp].to]==d[u]+1)
		{
			f=DFS(e[tmp].to,min(a,e[tmp].capa-e[tmp].flow));
			if(f>0)
			{
				flow+=f;a-=f;
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
		for(int i=s;i<=tot;i++) cur[i]=h[i];
		flow+=DFS(s,INF);
	}
	return flow;
}

inline int id(int x,int y){return (x-1)*n+y+1;}

void Build()
{
	scanf("%d%d",&n,&m);
	int x;tot=n*m+1;s=0;t=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&x);dafa+=x;
			add_edge(s,id(i,j),x);
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&x);dafa+=x;
			add_edge(id(i,j),t,x);
		}
	for(int i=1;i<n;i++)
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&x);
			dafa+=x;tot++;
			add_edge(s,tot,x);
			add_edge(tot,id(i,j),x);
			add_edge(tot,id(i+1,j),x);
		}
	for(int i=1;i<n;i++)
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&x);
			dafa+=x;tot++;
			add_edge(tot,t,x);
			add_edge(id(i,j),tot,x);
			add_edge(id(i+1,j),tot,x);
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<m;j++)
		{
			scanf("%d",&x);
			dafa+=x;tot++;
			add_edge(s,tot,x);
			add_edge(tot,id(i,j),x);
			add_edge(tot,id(i,j+1),x);
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<m;j++)
		{
			scanf("%d",&x);
			dafa+=x;tot++;
			add_edge(tot,t,x);
			add_edge(id(i,j),tot,x);
			add_edge(id(i,j+1),tot,x);
		}
}

int main()
{
	memset(h,-1,sizeof(h));
	Build();
	printf("%d\n",dafa-Dinic());
	return 0;
}
