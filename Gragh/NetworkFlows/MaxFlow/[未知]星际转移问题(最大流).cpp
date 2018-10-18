#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define INF 0x7fffffff
using namespace std;

struct Edge{int from,to,capa,flow,next;} e[2000000];
int h[300000],d[300000],cur[300000];
int hp[30],T[30];
int map[30][500];
bool vis[300000];
int n,m,k,s,t;
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
	scanf("%d%d%d",&n,&m,&k);
	s=0;
	t=200000;
	for(int i=s;i<=t;i++) h[i]=-1;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",hp+i,T+i);
		for(int j=0;j<T[i];j++)
		{
			scanf("%d",&map[i][j]);
			map[i][j]+=2;
		}
	}
	n+=2;
	int cnt=0,day;
	for(day=0;day<=500;day++)
	{
		add_edge(n*day+1,t,INF);
		add_edge(s,n*day+2,INF);
		if(day>0)
		{
			for(int i=1;i<=n;i++)
				add_edge((day-1)*n+i,day*n+i,INF);
			for(int i=1;i<=m;i++)
			{
				int u=map[i][(day-1)%T[i]];
				int v=map[i][day%T[i]];
				add_edge(n*(day-1)+u,n*day+v,hp[i]);
			}
		}
		cnt+=Dinic();
		if(cnt>=k) break;
	}
	if(day==501) cout<<0<<endl;else cout<<day<<endl;
	return 0;
}
