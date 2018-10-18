#include<bits/stdc++.h>
using namespace std;

struct Edge{int to,next;double capa;} e[5010];
int h[1010],sum=0,n,m;
double cap[5010],d[1010],w[1010];
bool flag,vis[1010];

void add_edge(int u,int v,double w)
{
	e[++sum].to=v;
	cap[sum]=w;
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
		e[i].capa=x*cap[i]-w[e[i].to];
	memset(vis,0,sizeof(vis));
	memset(d,0,sizeof(d));
	flag=0;
	for(int i=1;i<=n;i++)
		if(!flag) dfs(i);
	return flag;
}

int main()
{
	int u,v;double c;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%lf",w+i);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%lf",&u,&v,&c);
		add_edge(u,v,c);
	}
	double l=0,r=1e3,mid;
	while(r-l>1e-3)
	{
		//printf("%lf %lf\n",l,r);
		mid=(l+r)/2;
		if(chk(mid)) l=mid;
		else r=mid;
	}
	printf("%.2lf\n",l);
	return 0;
}
