#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define INF 0x7fffffff
using namespace std;

struct Edge{int from,to,capa,flow,next;} e[5000000];
int h[15000];
int n,m,k,s,t,sum=-1;
int d[15000],cur[15000];
bool vis[15000];

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

int r[60][60],c[60][60];
char map[60][60];

int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
			cin>>map[i][j];
		map[i][0]='#';
	}
	for(int i=1;i<=m;i++) map[0][i]='#';
	int cnt=0;
	s=0;t=8000;
	for(int i=s;i<=t;i++) h[i]=-1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			if(map[i][j]=='#') continue;
			if(map[i][j-1]=='#') cnt++,add_edge(s,cnt,1);
			r[i][j]=cnt;
		}
	for(int j=1;j<=m;j++)
		for(int i=1;i<=n;i++)
		{
			if(map[i][j]=='#') continue;
			if(map[i-1][j]=='#') cnt++,add_edge(cnt,t,1);
			c[i][j]=cnt;
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(map[i][j]=='*') add_edge(r[i][j],c[i][j],1);
	printf("%d\n",Dinic());
	return 0;
}
