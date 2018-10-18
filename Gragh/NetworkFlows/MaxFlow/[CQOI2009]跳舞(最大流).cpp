#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define INF 0x7fffffff
using namespace std;

struct Edge{int from,to,capa,flow,next;} e[2000000];
int h[5000];
int n,k,s,t,sum;
int d[5000],cur[5000];
bool vis[5000];
bool like[100][100];

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

void build(int f)
{
	for(int i=s;i<=t;i++) h[i]=-1;
	sum=-1;
	for(int i=1;i<=n;i++)
	{
		add_edge(s,i,f);
		add_edge(n+i,t,f);
		add_edge(i,2*n+i,k);
		add_edge(3*n+i,n+i,k);
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(like[i][j]) add_edge(i,n+j,1);else add_edge(2*n+i,3*n+j,1);
}

int main()
{
	cin>>n>>k;
	s=0;t=4*n+1;
	char c;
	memset(like,0,sizeof(like));
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			cin>>c;
			if(c=='Y') like[i][j]=1;
		}
	int l=0,r=n,mid;
	while(l<=r)
	{
		mid=(l+r)/2;
		build(mid);
		int f=Dinic();
		if(f==mid*n) l=mid+1;
		else r=mid-1;
	}
	printf("%d\n",r);
	return 0;
}
