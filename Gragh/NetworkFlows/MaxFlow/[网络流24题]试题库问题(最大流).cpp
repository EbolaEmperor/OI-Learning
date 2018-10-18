#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define INF 0x7fffffff
using namespace std;

struct Edge{int from,to,capa,flow,next;} e[2000000];
int h[5000],d[5000],cur[5000];
bool vis[5000];
int cnt[25];
int result[25][1010];
int n,k,s,t;
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

int BFS()
{
	memset(vis,0,sizeof(vis));
	d[s]=0;
	vis[s]=1;
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

void Dinic()
{
	int flow=0;
	while(BFS())
	{
		for(int i=s;i<=t;i++) cur[i]=h[i];
		flow+=DFS(s,INF);
	}
}

int main()
{
	cin>>k>>n;
	s=0;
	t=k+n+1;
	for(int i=s;i<=t;i++) h[i]=-1;
	for(int i=1;i<=n;i++)
	{
		add_edge(s,i,1);
		add_edge(i,s,0);
	}
	int tmp,tmp2;
	for(int i=1;i<=k;i++)
	{
		scanf("%d",&tmp);
		add_edge(n+i,t,tmp);
		add_edge(t,n+i,0);
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&tmp);
		for(int j=1;j<=tmp;j++)
		{
			scanf("%d",&tmp2);
			add_edge(i,n+tmp2,1);
			add_edge(n+tmp2,i,0);
		}
	}
	Dinic();
	memset(cnt,0,sizeof(cnt));
	for(int i=0;i<=sum;i++)
	{
		if(e[i].flow>0&&e[i].from>s&&e[i].from<=n&&e[i].to>n&&e[i].to<t)
		{
			cnt[e[i].to-n]++;
			result[e[i].to-n][cnt[e[i].to-n]]=e[i].from;
		}
	}
	for(int i=1;i<=k;i++)
	{
		printf("%d: ",i);
		for(int j=1;j<=cnt[i];j++)
			printf("%d ",result[i][j]);
		printf("\n");
	}
	return 0;
}
