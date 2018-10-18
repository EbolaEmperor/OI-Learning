#include<bits/stdc++.h>
using namespace std;

const double eps=1e-9;
void gauss(double (*A)[405],int n)
{
	for(int i=1;i<n;i++)
	{
		int pos=i;
		while(pos<n&&fabs(A[pos][i])<eps) pos++;
		if(pos>=n) continue;
		for(int j=1;j<=n;j++)
			swap(A[i][j],A[pos][j]);
		for(int j=i+1;j<n;j++)
		{
			double t=A[j][i]/A[i][i];
			for(int k=1;k<=n;k++)
				A[j][k]-=A[i][k]*t;
		}
	}
}

int G[405][405];
int deg[25],n,m;
double P[25],go[25];
double f[405][405];
double ans[405];

int id(int x,int y){return (x-1)*n+y;}

int main()
{
	int a,b,u,v;
	scanf("%d%d%d%d",&n,&m,&a,&b);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&u,&v);
		G[u][v]=G[v][u]=1;
		deg[u]++;deg[v]++;
	}
	for(int i=1;i<=n;i++)
		scanf("%lf",P+i),go[i]=(1-P[i])/deg[i];
	for(int i=1;i<=n;i++) G[i][i]=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			f[id(i,j)][id(i,j)]=1.0;
			for(int x=1;x<=n;x++)
				for(int y=1;y<=n;y++)
					if(x!=y&&G[x][i]&&G[y][j])
					{
						double p1=go[x],p2=go[y];
						if(x==i) p1=P[x];
						if(y==j) p2=P[y];
						f[id(i,j)][id(x,y)]-=p1*p2;
					}
		}
	f[id(a,b)][n*n+1]+=1;
	gauss(f,n*n+1);
	for(int i=n*n;i>=1;i--)
	{
		double tmp=f[i][n*n+1];
		for(int j=i+1;j<=n*n;j++)
			tmp-=f[i][j]*ans[j];
		ans[i]=tmp/f[i][i];
	}
	for(int i=1;i<=n;i++)
		printf("%.6lf ",ans[id(i,i)]);
	return 0;
}
