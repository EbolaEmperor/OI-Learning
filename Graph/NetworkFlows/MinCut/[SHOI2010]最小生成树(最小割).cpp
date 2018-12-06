#include<bits/stdc++.h>
#define INF 0x7fffffff
using namespace std;

struct Edge{int from,to,capa,next,flow;} e[4000],e2[2000];
int h[510],sum=-1,n,s,t;
int cur[510];
bool vis[510];
int d[510];

void AddEdge(int u,int v,int w)
{
	sum++;
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
	queue<int> q;
	q.push(s);
	vis[s]=1;d[s]=0;
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
		for(int i=1;i<=n;i++) cur[i]=h[i];
		flow+=DFS(s,INF);
	}
	return flow;
}

int main()
{
	int m,lab;
	cin>>n>>m>>lab;
	for(int i=1;i<=m;i++) scanf("%d%d%d",&e2[i].from,&e2[i].to,&e2[i].capa);
	for(int i=1;i<=n;i++) h[i]=-1;
	s=e2[lab].from;t=e2[lab].to;
	for(int i=1;i<=m;i++)
		if(i!=lab&&e2[i].capa<=e2[lab].capa)
		{
			add_edge(e2[i].from,e2[i].to,e2[lab].capa-e2[i].capa+1);
			add_edge(e2[i].to,e2[i].from,e2[lab].capa-e2[i].capa+1);
		}
	cout<<Dinic()<<endl;
	return 0;
}
