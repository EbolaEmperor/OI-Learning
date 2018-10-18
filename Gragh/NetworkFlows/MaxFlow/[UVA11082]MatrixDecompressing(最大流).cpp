//最大流：行列模型
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define INF 0x7fffffff
using namespace std;

struct Edge{int from,to,capa,flow,next;} e[2000000];
int h[5000];
int n,m,s,t,sum=-1;
int d[5000],cur[5000];
bool vis[5000];
int ans[200][200];

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
		for(int i=s;i<=t;i++) cur[i]=h[i];
		flow+=DFS(s,INF);
	} 
	return flow;
}

int main()
{
	int tt;
	cin>>tt;
	for(int T=1;T<=tt;T++)
	{
		int r,c,x,pre=0;
		sum=-1;
		scanf("%d%d",&r,&c);
		s=0;t=r+c+1;
		for(int i=s;i<=t;i++) h[i]=-1;
		for(int i=1;i<=r;i++)
		{
			scanf("%d",&x);
			add_edge(s,i,x-c-pre);
			pre=x;
		}
		pre=0;
		for(int i=1;i<=c;i++)
		{
			scanf("%d",&x);
			add_edge(i+r,t,x-r-pre);
			pre=x;
			//printf("%d %d %d mmm\n",i+r,t,x-r);
		}
		for(int i=1;i<=r;i++)
			for(int j=1;j<=c;j++)
				add_edge(i,j+r,19);
		Dinic();
		for(int i=0;i<=sum;i++)
			if(e[i].from>=1&&e[i].from<=r&&e[i].to>r&&e[i].to<=r+c)
				ans[e[i].from][e[i].to-r]=e[i].flow+1;
		printf("Matrix %d\n",T);
		for(int i=1;i<=r;i++)
		{
			for(int j=1;j<=c;j++)
				printf("%d ",ans[i][j]);
			printf("\n");
		}
	}
	return 0;
}
