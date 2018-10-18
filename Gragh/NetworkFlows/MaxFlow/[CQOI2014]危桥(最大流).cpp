#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define INF 0x7fffffff
using namespace std;

struct Edge{int from,to,capa,flow,next;} e[2000000];
int h[5000];
int n,s,t,sum;
int d[5000],cur[5000];
bool vis[5000];
char bridge[100][100];

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
		for(int i=0;i<=t;i++) cur[i]=h[i];
		flow+=DFS(s,INF);
	}
	return flow;
}

int main()
{
	int a1,a2,b1,b2,an,bn;
	while(~scanf("%d%d%d%d%d%d%d",&n,&a1,&a2,&an,&b1,&b2,&bn))
	{
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				cin>>bridge[i][j];
		sum=-1;
		s=n+1;t=n+2;
		for(int i=0;i<=t;i++) h[i]=-1;
		add_edge(s,a1,2*an);
		add_edge(s,b1,2*bn);
		add_edge(a2,t,2*an);
		add_edge(b2,t,2*bn);
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				if(bridge[i][j]=='O') add_edge(i,j,2);
				else if(bridge[i][j]=='N') add_edge(i,j,INF);
		int f=Dinic();
		if(f<2*(an+bn)) {puts("No");continue;}
		sum=-1;
		for(int i=0;i<=t;i++) h[i]=-1;
		add_edge(s,a1,2*an);
		add_edge(s,b2,2*bn);
		add_edge(a2,t,2*an);
		add_edge(b1,t,2*bn);
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				if(bridge[i][j]=='O') add_edge(i,j,2);
				else if(bridge[i][j]=='N') add_edge(i,j,INF);
		f=Dinic();
		if(f<2*(an+bn)) puts("No");
		else puts("Yes");
	}
	return 0;
}
