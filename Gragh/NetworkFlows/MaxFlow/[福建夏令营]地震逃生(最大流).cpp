#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;

int n,m,x,s,t;
struct Edge{int from,to,capa,flow,next;} e[5000];
int h[300],d[300],cur[300];
bool vis[300];
int sum=-1;

void add_edge(int u,int v,int c)
{
	sum++;
	e[sum].from=u;
	e[sum].to=v;
	e[sum].capa=c;
	e[sum].flow=0;
	e[sum].next=h[u];
	h[u]=sum;
}

bool BFS()
{
	memset(vis,0,sizeof(vis));
	vis[s]=1;
	d[s]=0;
	queue<int> q;
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
	if(u==t||a==0) return a;
	int flow=0,f;
	for(int& tmp=cur[u];tmp!=-1;tmp=e[tmp].next)
	{
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
	}
	return flow;
}

int Maxflow()
{
	int flow=0;
	while(BFS())
	{
		for(int i=1;i<=n;i++) cur[i]=h[i];
		flow+=DFS(s,0x7fffffff);
	}
	return flow;
}

int main()
{
	int u,v,c;
	cin>>n>>m>>x;
	for(int i=1;i<=n;i++) h[i]=-1;
	s=1;
	t=n;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&u,&v,&c);
		add_edge(u,v,c);
		add_edge(v,u,0);
	}
	int maxflow=Maxflow();
	if(maxflow==0)
		printf("Orz Ni Jinan Saint Cow!\n");
	else
	{
		int group=x/maxflow;
		if(x%maxflow!=0) group++;
		printf("%d %d\n",maxflow,group);
	}
	return 0;
}
