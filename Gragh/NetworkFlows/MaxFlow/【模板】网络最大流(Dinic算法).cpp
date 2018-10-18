#include<bits/stdc++.h>
#define INF 0x7fffffff
using namespace std;

struct Edge{int from,to,flow,capa,next;} e[2000000];
int h[20000],sum=-1;
int deep[20000],cur[20000];
bool vis[20000];
int n,m,s,t;

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
	queue<int> f;
	f.push(s);
	memset(vis,0,sizeof(vis));
	vis[s]=1;
	deep[s]=0;
	while(!f.empty())
	{
		int o=f.front();
		for(int tmp=h[o];tmp!=-1;tmp=e[tmp].next)
		{
			if((!vis[e[tmp].to])&&e[tmp].capa>e[tmp].flow)
			{
				vis[e[tmp].to]=1;
				f.push(e[tmp].to);
				deep[e[tmp].to]=deep[o]+1;
			}
		}
		f.pop();
	}
	return vis[t];
}

int DFS(int u,int a)
{
	if(u==t||a==0) return a;
	int flow=0,f;
	for(int &tmp=cur[u];tmp!=-1;tmp=e[tmp].next)
		if(deep[u]+1==deep[e[tmp].to])
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
		for(int i=0;i<=n;i++) cur[i]=h[i];
		flow+=DFS(s,INF);
	}
	return flow;
}

int main()
{
	int a,b,c;
	cin>>n>>m>>s>>t;
	for(int i=0;i<=n;i++) h[i]=-1;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		add_edge(a,b,c);
	}
	cout<<Dinic()<<endl;
	return 0;
}
