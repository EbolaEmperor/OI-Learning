#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define INF 0x7fffffff
using namespace std;

struct Edge{long long from,to,capa,flow,next;} e[2000000],ee[2000000];
long long h[5000];
long long n,m,s,t,sum=-1,x;
long long d[5000],cur[5000];
bool vis[5000];

void AddEdge(long long u,long long v,long long w)
{
	sum++;
	e[sum].from=u;
	e[sum].to=v;
	e[sum].capa=w;
	e[sum].flow=0;
	e[sum].next=h[u];
	h[u]=sum;
}

void add_edge(long long u,long long v,long long w)
{
	AddEdge(u,v,w);
	AddEdge(v,u,0);
}

bool BFS()
{
	queue<long long> q;
	memset(vis,0,sizeof(vis));
	vis[s]=1;
	d[s]=0;
	q.push(s);
	while(!q.empty())
	{
		long long o=q.front();
		for(long long tmp=h[o];tmp!=-1;tmp=e[tmp].next)
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

long long DFS(long long u,long long a)
{
	long long flow=0,f;
	if(u==t||a==0) return a;
	for(long long &tmp=cur[u];tmp!=-1;tmp=e[tmp].next)
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

long long Dinic()
{
	long long flow=0;
	while(BFS())
	{
		for(long long i=s;i<=t;i++) cur[i]=h[i];
		flow+=DFS(s,INF);
	}
	return flow;
}

bool check(double mid)
{
	sum=-1;
	for(long long i=s;i<=t;i++) h[i]=-1;
	for(long long i=1;i<=m;i++) add_edge(ee[i].from,ee[i].to,(long long)((double)ee[i].capa/mid));
	return Dinic()>=x;
}

int main()
{
	cin>>n>>m>>x;
	s=1;t=n;
	for(long long i=1;i<=m;i++)
		scanf("%I64d%I64d%I64d",&ee[i].from,&ee[i].to,&ee[i].capa);
	double mid,l=0,r=1e9;
	for(long long i=1;i<=100;i++)
	{
		mid=(l+r)/2;
		if(check(mid)) l=mid;
		else r=mid;
	}
	printf("%.8lf\n",l*(double)x);
	return 0;
}
