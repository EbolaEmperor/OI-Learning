#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<queue>
using namespace std;

const double eps=1e-6;
int dcmp(double x)
{
	if(fabs(x)<=eps) return 0;
	else if(x>0) return 1;
	else return -1;
}

namespace MF
{
	#define INF 1e9
	struct Edge{int to,next;double capa,flow;} e[2000000];
	int h[5000],sum=-1,s,t,n,m;
	int cur[5000],d[5000];
	bool vis[5000];
	void init()
	{
		sum=-1;
		for(int i=s;i<=t;i++) h[i]=-1;
	}
	void AddEdge(int u,int v,double w)
	{
		sum++;
		e[sum].to=v;
		e[sum].capa=w;
		e[sum].flow=0;
		e[sum].next=h[u];
		h[u]=sum;
	}
	void add_edge(int u,int v,double w)
	{
		AddEdge(u,v,w);
		AddEdge(v,u,0);
	}
	double DFS(int u,double a)
	{
		if(u==t||dcmp(a)==0) return a;
		double flow=0,f;
		for(int &tmp=cur[u];tmp!=-1;tmp=e[tmp].next)
			if(d[e[tmp].to]==d[u]+1)
			{
				f=DFS(e[tmp].to,min(a,e[tmp].capa-e[tmp].flow));
				if(dcmp(f)>0)
				{
					flow+=f;
					a-=f;
					e[tmp].flow+=f;
					e[tmp^1].flow-=f;
					if(dcmp(a)==0) break;
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
				if(dcmp(e[tmp].capa-e[tmp].flow)>0&&vis[e[tmp].to]==0)
				{
					vis[e[tmp].to]=1;
					d[e[tmp].to]=d[o]+1;
					q.push(e[tmp].to);
				}
			q.pop();
		}
		return vis[t];
	}
	double Dinic()
	{
		double flow=0;
		while(BFS())
		{
			for(int i=s;i<=t;i++) cur[i]=h[i];
			flow+=DFS(s,INF);
		}
		return flow;
	}
}

using namespace MF;

int froms[5000],tos[5000];
double capas[5000];
double maxflow=0;

bool checker(double limit)
{
	init();
	for(int i=1;i<=m;i++) add_edge(froms[i],tos[i],min(capas[i],limit));
	double flow=Dinic();
	return dcmp(maxflow-flow)==0;
}

int main()
{
	int p;
	cin>>n>>m>>p;
	s=1;t=n;
	for(int i=s;i<=t;i++) h[i]=-1;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%lf",froms+i,tos+i,capas+i);
		add_edge(froms[i],tos[i],capas[i]);
	}
	maxflow=Dinic();
	printf("%.4lf\n",maxflow);
	double l=0,r=1e5,mid;
	while(dcmp(l-r)<0)
	{
		mid=(l+r)/2;
		if(checker(mid)) r=mid;
		else l=mid;
	}
	double cost=0;
	for(int i=0;i<=sum;i++)
		if(dcmp(e[i].capa)>0) cost=max(cost,e[i].flow);
	cost*=p;
	printf("%.4lf\n",cost);
	return 0;
}
