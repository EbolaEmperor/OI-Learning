#include<bits/stdc++.h>
#define double long double
#define INF 1e11
using namespace std;

const double eps=5*1e-8;
struct Edge{int to,next;double capa;} e[20010];
int h[110],sum=0,n,m,K;
double dis[110][110];
double buy[110][1010],sell[110][1010];
double cap[20010],val[20010],earn[110][110];
double d[110];bool vis[110],flag;

void add_edge(int u,int v)
{
	e[++sum].to=v;
	cap[sum]=dis[u][v];
	val[sum]=earn[u][v];
	e[sum].next=h[u];
	h[u]=sum;
}

void dfs(int u)
{
	if(flag) return;
	vis[u]=1;
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
		if(d[u]+e[tmp].capa<d[e[tmp].to])
		{
			if(vis[e[tmp].to]||flag){flag=1;return;}
			d[e[tmp].to]=d[u]+e[tmp].capa;
			dfs(e[tmp].to);
		}
	vis[u]=0;
}

bool chk(double x)
{
	for(int i=1;i<=sum;i++)
		e[i].capa=x*cap[i]-val[i];
	memset(vis,0,sizeof(vis));
	memset(d,0,sizeof(d));
	flag=0;
	for(int i=1;i<=n;i++)
		if(!flag) dfs(i);
	return flag;
}

int main()
{
	int u,v;double w;
	scanf("%d%d%d",&n,&m,&K);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=K;j++)
			scanf("%Lf%Lf",&buy[i][j],&sell[i][j]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			dis[i][j]=(i==j)?0:INF;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%Lf",&u,&v,&w);
		dis[u][v]=min(dis[u][v],w);
	}
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(i!=j&&dis[i][j]<INF-eps)
			{
				for(int k=1;k<=K;k++)
					if(fabs(buy[i][k]+1)>eps&&fabs(sell[j][k]+1)>eps)
						earn[i][j]=max(earn[i][j],sell[j][k]-buy[i][k]);
				add_edge(i,j);
			}
	double l=0,r=1e9,mid;
	while(r-l>eps)
	{
		mid=(l+r)/2;
		if(chk(mid)) l=mid;
		else r=mid;
	}
	printf("%d\n",(int)floor(r));
	return 0;
}
