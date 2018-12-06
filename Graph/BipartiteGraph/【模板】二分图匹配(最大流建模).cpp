#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;

struct Edge{int from,to,capa,flow,next;} e[2000000];
int h[3000],d[3000],cur[3000];
int sum=-1;
bool vis[3000];
int n,m,e_num;
int s,t;

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
	queue<int> q;
	q.push(s);
	d[s]=0;
	vis[s]=1;
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
		if(d[u]+1==d[e[tmp].to])
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

int MaxFlow()
{
	int flow=0;
	while(BFS())
	{
		for(int i=0;i<=n+m+100;i++) cur[i]=h[i];
		flow+=DFS(s,0x7fffffff);
	}
	return flow;
}

int main()
{
	int u,v;
	cin>>n>>m>>e_num;
	for(int i=0;i<=n+m+100;i++) h[i]=-1;
	s=0;
	t=n+m+1;
	for(int i=1;i<=n;i++)
	{
		add_edge(0,i,1);
		add_edge(i,0,0);
	}
	for(int i=n+1;i<=n+m;i++)
	{
		add_edge(i,t,1);
		add_edge(t,i,0);
	}
	for(int i=1;i<=e_num;i++)
	{
		scanf("%d%d",&u,&v);
		if(u>n||v>m) continue;
		add_edge(u,n+v,1);
		add_edge(n+v,u,0);
	}
	printf("%d\n",MaxFlow());
	return 0;
}
