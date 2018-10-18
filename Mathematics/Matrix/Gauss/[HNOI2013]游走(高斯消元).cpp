#include<bits/stdc++.h>
using namespace std;

void Gauss(double A[510][510],int n)
{
	for(int i=1;i<n;i++)
	{
		int pos=i;
		while(pos<n&&fabs(A[pos][i])<1e-9) pos++;
		if(pos>=n) continue;
		for(int j=1;j<=n;j++)
			swap(A[pos][j],A[i][j]);
		for(int j=i+1;j<n;j++)
		{
			double t=A[j][i]/A[i][i];
			for(int k=1;k<=n;k++)
				A[j][k]-=A[i][k]*t;
		}
	}
}

int G[510][510],deg[510];
double A[510][510],P[510];
struct Edge{int u,v;double w;} e[250010];
bool operator < (const Edge &a,const Edge &b){return a.w>b.w;}

int main()
{
	int n,m,u,v;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&u,&v);
		e[i]=Edge{u,v,0};
		G[u][v]++;G[v][u]++;
		deg[u]++;deg[v]++;
	}
	for(int i=1;i<n;i++)
	{
		A[i][i]=1.0;
		for(int j=1;j<=n;j++)
			if(G[j][i]) A[i][j]-=1.0/deg[j];
	}
	A[1][n+1]=A[n][n]=1.0;
	Gauss(A,n+1);
	for(int i=n;i>=1;i--)
	{
		double tmp=A[i][n+1];
		for(int j=i+1;j<=n;j++)
			tmp-=A[i][j]*P[j];
		P[i]=tmp/A[i][i];
	}
	for(int i=1;i<=m;i++)
	{
		int u=e[i].u,v=e[i].v;
		e[i].w=P[u]/deg[u]+P[v]/deg[v];
	}
	sort(e+1,e+1+m);
	double ans=0;
	for(int i=1;i<=m;i++)
		ans+=e[i].w*i;
	printf("%.3lf\n",ans);
	return 0;
}
