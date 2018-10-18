#include<bits/stdc++.h>
#define v e[tmp].to
using namespace std;

struct Edge{int to,next;double capa;} e[1000010];
int h[500010],sum=0,n;
double f1[500010],f2[500010];
int q[500010];
double ans=0;

const double eps=1e-9;
int dcmp(double x)
{
	if(fabs(x)<=eps) return 0;
	else if(x>0) return 1;
	else return -1;
}

void add_edge(int u,int y,double w)
{
	sum++;
	e[sum].to=y;
	e[sum].capa=w;
	e[sum].next=h[u];
	h[u]=sum;
}

void dfs1(int u,int fa)
{
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		if(v==fa) continue;
		dfs1(v,u);
		f1[u]=f1[u]+f1[v]*e[tmp].capa-f1[u]*f1[v]*e[tmp].capa;
	}
}

void dfs2(int u,int fa)
{
	ans+=f2[u];
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		if(v==fa) continue;
		if(dcmp(1-e[tmp].capa*f1[v])==0) f2[v]=1;
		else
		{
			double t=(f2[u]-e[tmp].capa*f1[v])/(1-e[tmp].capa*f1[v]);
			f2[v]=f1[v]+t*e[tmp].capa-f1[v]*t*e[tmp].capa;
		}
		dfs2(v,u);
	}
}

int main()
{
	int x,y,w;
	cin>>n;
	for(int i=1;i<n;i++)
	{
		scanf("%d%d%d",&x,&y,&w);
		add_edge(x,y,(double)w/100);
		add_edge(y,x,(double)w/100);
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%d",q+i);
		f1[i]=(double)q[i]/100;
	}
	dfs1(1,0);
	f2[1]=f1[1];
	dfs2(1,0);
	printf("%.6lf\n",ans);
	return 0;
}
