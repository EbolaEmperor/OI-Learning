#include<bits/stdc++.h>
#define INF 0x7fffffff
#define LINF (1ll<<60)
using namespace std;

const int M=100010;
const double eps=1e-7;
typedef long long LL;
int from[M],vt[M],capa[M],flow[M],nxt[M];
double cost[M];
int h[210],sum,s,t,n;
int able[210],pre[210];
bool vis[210];
double d[210];
double a[110][110],b[110][110];

void AddEdge(int u,int v,int w,double c)
{
	sum++;
	from[sum]=u;
	vt[sum]=v;
	capa[sum]=w;
	flow[sum]=0;
	cost[sum]=c;
	nxt[sum]=h[u];
	h[u]=sum;
}

void add_edge(int u,int v,int w,double c)
{
	AddEdge(u,v,w,c);
	AddEdge(v,u,0,-c);
}

void Build(double x)
{
	memset(h,-1,sizeof(h));
	sum=-1;s=0;t=2*n+1;
	for(int i=1;i<=n;i++)
	{
		add_edge(s,i,1,0);
		add_edge(i+n,t,1,0);
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			add_edge(i,j+n,1,a[i][j]-x*b[i][j]);
}

bool SPFA(int &fl,double &co)
{
	for(int i=s;i<=t;i++) d[i]=-1e9;
	memset(vis,0,sizeof(vis));
	memset(able,0,sizeof(able));
	queue<int> q;q.push(s);
	able[s]=INF;d[s]=0;vis[s]=1;
	while(!q.empty())
	{
		int o=q.front();
		for(int tmp=h[o];~tmp;tmp=nxt[tmp])
			if(flow[tmp]<capa[tmp]&&d[o]+cost[tmp]>d[vt[tmp]])
			{
				d[vt[tmp]]=d[o]+cost[tmp];
				able[vt[tmp]]=min(able[o],capa[tmp]-flow[tmp]);
				pre[vt[tmp]]=tmp;
				if(!vis[vt[tmp]]) vis[vt[tmp]]=1,q.push(vt[tmp]);
			}
		vis[o]=0;q.pop();
	}
	if(able[t]==0) return false;
	fl+=able[t];
	co+=(double)able[t]*d[t];
	for(int u=t;u!=s;u=from[pre[u]])
	{
		flow[pre[u]]+=able[t];
		flow[pre[u]^1]-=able[t];
	}
	return true;
}

double MinCost(double x)
{
	Build(x);
	int flow=0;double cost=0;
	while(SPFA(flow,cost));
	return cost;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%lf",&a[i][j]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%lf",&b[i][j]);
	double l=0,r=1e4,mid;
	while(r-l>eps)
	{
		mid=(l+r)/2;
		if(MinCost(mid)>0) l=mid;
		else r=mid;
	}
	printf("%lf\n",l);
	return 0;
}
