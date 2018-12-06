#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define INF 0x7fffffff
using namespace std;

struct Edge{int from,to,capa,flow,next;} e[2000000];
int h[40010],d[40010],cur[40010];
bool vis[40010];
int n1,n2,n3,s,t;
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
	sum++;
	e[sum].from=v;
	e[sum].to=u;
	e[sum].capa=0;
	e[sum].flow=0;
	e[sum].next=h[v];
	h[v]=sum;
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
			if(vis[e[tmp].to]==0&&e[tmp].capa>e[tmp].flow)
			{
				d[e[tmp].to]=d[o]+1;
				vis[e[tmp].to]=1;
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
				a-=f;
				flow+=f;
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
	cin>>n1>>n2>>n3;
	s=0;
	t=2*n1+n2+n3+1;
	for(int i=s;i<=t;i++) h[i]=-1;
	int like;
	for(int i=1;i<=n1;i++)
		for(int j=1;j<=n2;j++)
		{
			scanf("%d",&like);
			if(like) add_edge(j,n2+i,1);
		}
	for(int i=1;i<=n1;i++)
		for(int j=1;j<=n3;j++)
		{
			scanf("%d",&like);
			if(like) add_edge(n1+n2+i,2*n1+n2+j,1);
		}
	for(int i=1;i<=n2;i++) add_edge(s,i,1);
	for(int i=1;i<=n3;i++) add_edge(2*n1+n2+i,t,1);
	for(int i=1;i<=n1;i++) add_edge(n2+i,n1+n2+i,1);
	cout<<Dinic()<<endl;
	return 0;
}
