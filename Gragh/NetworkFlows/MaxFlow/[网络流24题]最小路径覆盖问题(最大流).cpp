#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;

namespace MF
{
	#define INF 0x7fffffff
	struct Edge{int to,capa,next,flow;} e[2000000];
	int h[5000],sum=-1,s,t,n,m;
	int cur[5000],d[5000];
	bool vis[5000];
	void init()
	{
		sum=-1;
		for(int i=s;i<=t;i++) h[i]=-1;
	}
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
	bool BFS()
	{
		queue<int> q;
		q.push(s);
		memset(vis,0,sizeof(vis));
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
}

using namespace MF;

void dfs(int u)
{
	printf("%d ",u);
	for(int tmp=h[u];tmp!=-1;tmp=e[tmp].next)
	{
		if(e[tmp].flow==0||e[tmp].capa==0) continue;
		if(!vis[e[tmp].to-n]) vis[e[tmp].to-n]=1,dfs(e[tmp].to-n);
	}
}

int main()
{
	int x,y;
	cin>>n>>m;
	s=0;t=2*n+1;
	init();
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		add_edge(x,y+n,1);
	}
	for(int i=1;i<=n;i++)
	{
		add_edge(s,i,1);
		add_edge(i+n,t,1);
	}
	int ans=n-Dinic();
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++)
		if(!vis[i])
		{
			vis[i]=1;
			dfs(i);
			putchar('\n');
		}
	cout<<ans<<endl;
	return 0;
}
