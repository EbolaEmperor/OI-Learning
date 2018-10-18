#include<bits/stdc++.h>
#define INF 0x7fffffff
#define LINF (1ll<<62)
using namespace std;

typedef long long LL;
struct Edge{int from,to,capa,flow,next;LL cost;} e[2000000];
int h[1000],sum=-1,s,t;
int a[210],b[210];
LL c[210],n;
int cnt[210];
bool vis[1000];
LL dist[1000];
int able[1000],p[1000];

void AddEdge(int u,int v,int w,LL c)
{
	sum++;
	e[sum].from=u;
	e[sum].to=v;
	e[sum].capa=w;
	e[sum].cost=c;
	e[sum].flow=0;
	e[sum].next=h[u];
	h[u]=sum;
}

void add_edge(int u,int v,int w,LL c)
{
	AddEdge(u,v,w,c);
	AddEdge(v,u,0,-c);
}

bool BellmanFord(int &flow,LL &cost)
{
	memset(vis,0,sizeof(vis));
	vis[s]=1;
	queue<int> q;
	q.push(s);
	for(int i=s;i<=t;i++) dist[i]=-LINF;
	dist[s]=0;
	able[s]=INF;
	while(!q.empty())
	{
		int o=q.front();
		for(int tmp=h[o];tmp!=-1;tmp=e[tmp].next)
			if(e[tmp].capa>e[tmp].flow&&dist[o]+e[tmp].cost>dist[e[tmp].to])
			{
				dist[e[tmp].to]=dist[o]+e[tmp].cost;
				able[e[tmp].to]=min(able[o],e[tmp].capa-e[tmp].flow);
				p[e[tmp].to]=tmp;
				if(!vis[e[tmp].to]) q.push(e[tmp].to),vis[e[tmp].to]=1;
			}
		q.pop();
		vis[o]=0;
	}
	if(dist[t]==-LINF) return 0;
	LL delta=(LL)able[t]*dist[t];
	if(cost+delta<0){flow+=cost/(-dist[t]);return 0;}
	cost+=delta;
	flow+=able[t];
	for(int u=t;u!=s;u=e[p[u]].from)
	{
		e[p[u]].flow+=able[t];
		e[p[u]^1].flow-=able[t];
	}
	return 1;
}

int MCMF()
{
	int flow=0;
	LL cost=0;
	while(BellmanFord(flow,cost));
	return flow;
}

int decompose(int n)
{
	int s=sqrt(n),tot=0;
	for(int i=2;i<=s;i++)
		while(n%i==0) n/=i,tot++;
	if(n>1) tot++;
	return tot;
}

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) scanf("%d",a+i);
	for(int i=1;i<=n;i++) scanf("%d",b+i);
	for(int i=1;i<=n;i++) scanf("%lld",c+i);
	for(int i=1;i<=n;i++) cnt[i]=decompose(a[i]);
	s=0;t=n+1;
	for(int i=s;i<=t;i++) h[i]=-1;
	for(int i=1;i<=n;i++)
		if(cnt[i]&1) add_edge(s,i,b[i],0);
		else add_edge(i,t,b[i],0);
	for(int i=1;i<=n;i++)
		if(cnt[i]&1)
			for(int j=1;j<=n;j++)
				if((a[i]%a[j]==0&&cnt[i]==cnt[j]+1)||(a[j]%a[i]==0&&cnt[j]==cnt[i]+1))
					add_edge(i,j,INF,c[i]*c[j]);
	cout<<MCMF()<<endl;
	return 0;
}
