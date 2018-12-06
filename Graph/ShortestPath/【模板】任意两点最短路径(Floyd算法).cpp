#include<bits/stdc++.h>
#define INF int(1e9)
using namespace std;

int d[610][610];

int main()
{
	int n,m,u,v,w,Q;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			d[i][j]=INF;
	for(int i=1;i<=n;i++) d[i][i]=0;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&u,&v,&w);
		d[u][v]=min(d[u][v],w);
		d[v][u]=min(d[v][u],w);
	}
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				d[i][j]=min(d[i][j],d[i][k]+d[k][j]);
	scanf("%d",&Q);
	while(Q--)
	{
		scanf("%d%d",&u,&v);
		printf("%d\n",(d[u][v]==INF)?0x7fffffff:d[u][v]);
	}
	return 0;
}
