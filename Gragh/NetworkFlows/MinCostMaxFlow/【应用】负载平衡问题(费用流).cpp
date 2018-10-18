#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define INF 0x7fffffff
using namespace std;

struct Edge{int from,to,capa,flow,cost,next;} e[200000];
int h[300],d[300],p[300],a[300];
bool vis[300];
int v[105];
int sum=-1;
int n,s,t;

void add_edge(int from,int to,int capa,int cost)
{
	sum++;
	e[sum].from=from;
	e[sum].to=to;
	e[sum].capa=capa;
	e[sum].cost=cost;
	e[sum].flow=0;
	e[sum].next=h[from];
	h[from]=sum;
}

bool BellmanFord(int& flow,int& cost)
{
	for(int i=s;i<=t;i++) d[i]=INF;
	d[s]=0;
	memset(a,0,sizeof(a));
	a[s]=INF;
	queue<int> q;
	q.push(s);
	memset(vis,0,sizeof(vis));
	vis[s]=1;
	while(!q.empty())
	{
		int o=q.front();
		for(int tmp=h[o];tmp!=-1;tmp=e[tmp].next)
		{
			if(d[o]+e[tmp].cost<d[e[tmp].to]&&e[tmp].capa>e[tmp].flow)
			{
				d[e[tmp].to]=d[o]+e[tmp].cost;
				a[e[tmp].to]=min(a[o],e[tmp].capa-e[tmp].flow);
				p[e[tmp].to]=tmp;
				if(!vis[e[tmp].to]) vis[e[tmp].to]=1,q.push(e[tmp].to);
			}
		}
		q.pop();
		vis[o]=0;
	}
	if(d[t]==INF) return false;
	flow+=a[t];
	cost+=a[t]*d[t];
	for(int i=t;i!=s;i=e[p[i]].from)
	{
		e[p[i]].flow+=a[t];
		e[p[i]^1].flow-=a[t];
	}
	return true;
}

int MincostMaxflow()
{
	int flow=0,cost=0;
	while(BellmanFord(flow,cost));
	return cost;
}

int main()
{
	cin>>n;
	s=0;
	t=2*n+1;
	for(int i=s;i<=t;i++) h[i]=-1;
	int average=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",v+i);
		average+=v[i];
	}
	average/=n;
	for(int i=1;i<=n;i++)
	{
		if(v[i]>average) add_edge(s,i,v[i]-average,0),add_edge(i,s,0,0);
		if(v[i]<average) add_edge(i+n,t,average-v[i],0),add_edge(t,i+n,0,0);
		if(i!=1)
		{
			add_edge(i,i-1,INF,1),add_edge(i-1,i,0,-1);
			add_edge(i,i-1+n,INF,1),add_edge(i-1+n,i,0,-1);
		}
		if(i!=n)
		{
			add_edge(i,i+1,INF,1),add_edge(i+1,i,0,-1);
			add_edge(i,i+1+n,INF,1),add_edge(i+1+n,i,0,-1);
		}
	}
	add_edge(1,n,INF,1),add_edge(n,1,0,-1);
	add_edge(1,n+n,INF,1),add_edge(n+n,1,0,-1);
	add_edge(n,1,INF,1),add_edge(1,n,0,-1);
	add_edge(n,n+1,INF,1),add_edge(n+1,n,0,-1);
	printf("%d\n",MincostMaxflow());
	return 0;
}
