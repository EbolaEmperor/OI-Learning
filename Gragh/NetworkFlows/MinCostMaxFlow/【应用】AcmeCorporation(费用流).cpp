#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define INF 0x7fffffff
using namespace std;

struct Edge{int from,to,capa,next,flow,cost;} e[2000000];
int h[5000];
int a[5000];
int d[5000];
int p[5000];
bool vis[5000];
int sum,s,t;

void AddEdge(int u,int v,int w,int c)
{
	sum++;
	e[sum].from=u;
	e[sum].to=v;
	e[sum].next=h[u];
	e[sum].capa=w;
	e[sum].flow=0;
	e[sum].cost=c;
	h[u]=sum;
}

void add_edge(int u,int v,int w,int c)
{
	AddEdge(u,v,w,c);
	AddEdge(v,u,0,-c);
}

bool BellmanFord(int &flow,long long &cost)
{
	memset(vis,0,sizeof(vis));
	memset(a,0,sizeof(a));
	memset(p,0,sizeof(p));
	for(int i=s;i<=t;i++) d[i]=INF;
	a[s]=INF;d[s]=0;vis[s]=1;
	queue<int> q;
	q.push(s);
	while(!q.empty())
	{
		int o=q.front();
		for(int tmp=h[o];tmp!=-1;tmp=e[tmp].next)
			if(e[tmp].capa>e[tmp].flow&&d[o]+e[tmp].cost<d[e[tmp].to])
			{
				d[e[tmp].to]=d[o]+e[tmp].cost;
				a[e[tmp].to]=min(a[o],e[tmp].capa-e[tmp].flow);
				p[e[tmp].to]=tmp;
				if(!vis[e[tmp].to]) vis[e[tmp].to]=1,q.push(e[tmp].to);
			}
		q.pop();
		vis[o]=0;
	}
	if(a[t]==0||d[t]>0) return 0;
	flow+=a[t];
	cost+=(long long)a[t]*(long long)d[t];
	for(int u=t;u!=s;u=e[p[u]].from)
	{
		e[p[u]].flow+=a[t];
		e[p[u]^1].flow-=a[t];
	}
	return 1;
}

long long MCMF()     //Min Cost Max Flow
{
	long long cost=0;
	int flow=0;
	while(BellmanFord(flow,cost));
	return cost;
}

int main()
{
	int tt,n,m;
	int pc,pl,sp,sl,mt;     //Produce Cost, Produce Limit, Sell Price, Sell Limit, Max Time 
	cin>>tt;
	for(int T=1;T<=tt;T++)
	{
		sum=-1;
		scanf("%d%d",&n,&m);
		s=0;t=2*n+1;
		for(int i=s;i<=t;i++) h[i]=-1;
		for(int i=1;i<=n;i++)
		{
			scanf("%d%d%d%d%d",&pc,&pl,&sp,&sl,&mt);
			add_edge(s,i,pl,pc);
			add_edge(n+i,t,sl,-sp);
			for(int j=0;j<=mt&&i+j<=n;j++) add_edge(i,n+i+j,INF,j*m);
		}
		printf("Case %d: %lld\n",T,-MCMF());
	}
	return 0;
}
