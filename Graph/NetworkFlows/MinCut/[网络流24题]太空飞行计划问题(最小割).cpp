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
		for(int i=s;i<=t;i++) d[i]=INF;
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

int tmm[100][100];
int tn[100];

int main()
{
	int x,sum=0;
	cin>>m>>n;
	s=0;t=m+n+1;
	init();
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&x);
		sum+=x;
		add_edge(s,i,x);
		char tools[10000];
		memset(tools,0,sizeof tools);
		cin.getline(tools,10000);
		int ulen=0,tool;
		while (sscanf(tools+ulen,"%d",&tool)==1)
		{
			tmm[i][++tn[i]]=tool;
			if (tool==0)  ulen++;
			else while (tool) tool/=10,ulen++;
			ulen++;
		}
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		add_edge(m+i,t,x);
	}
	for(int i=1;i<=m;i++)
		for(int j=1;j<=tn[i];j++)
			add_edge(i,m+tmm[i][j],INF);
	int flow=Dinic();
	for(int i=1;i<=m;i++)
		if(d[i]!=INF) printf("%d ",i);
	putchar('\n');
	for(int i=1;i<=n;i++)
		if(d[i+m]!=INF) printf("%d ",i);
	putchar('\n');
	cout<<(sum-flow)<<endl;
}
