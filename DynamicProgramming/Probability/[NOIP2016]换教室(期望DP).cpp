#include<bits/stdc++.h>
#define RINF (1<<20)
#define gc getchar
using namespace std;

double dis[310][310];
int c[2010],d[2010];
double k[2010];
double f[2010][2010][2];
int n,m,v,e;

int main()
{
	int x,y;
	double w,w1,w2,w3,w4;
	cin>>n>>m>>v>>e;
	for(int i=1;i<=n;i++) scanf("%d",c+i);
	for(int i=1;i<=n;i++) scanf("%d",d+i);
	for(int i=1;i<=n;i++) scanf("%lf",k+i);
	for(int i=1;i<=v;i++)
		for(int j=1;j<i;j++)
			dis[i][j]=dis[j][i]=RINF;
	for(int i=1;i<=e;i++)
	{
		scanf("%d%d%lf",&x,&y,&w);
		dis[x][y]=dis[y][x]=min(dis[x][y],w);
	}
	for(int i=1;i<=v;i++)
		for(int j=1;j<=v;j++)
			for(int l=1;l<j;l++)
				if(dis[j][i]+dis[i][l]<dis[j][l])
					dis[j][l]=dis[l][j]=dis[j][i]+dis[i][l];
	for(int i=0;i<=n;i++)
		for(int j=0;j<=m;j++)
			f[i][j][0]=f[i][j][1]=RINF;
	f[1][0][0]=f[1][1][1]=0;
	for(int i=2;i<=n;i++)
	{
		w1=dis[c[i-1]][c[i]];
		w2=dis[d[i-1]][c[i]]*k[i-1]+dis[c[i-1]][c[i]]*(1-k[i-1]);
		w3=dis[c[i-1]][d[i]]*k[i]+dis[c[i-1]][c[i]]*(1-k[i]);
		w4=dis[d[i-1]][d[i]]*k[i-1]*k[i]+dis[d[i-1]][c[i]]*k[i-1]*(1-k[i])+dis[c[i-1]][d[i]]*(1-k[i-1])*k[i]+dis[c[i-1]][c[i]]*(1-k[i-1])*(1-k[i]);
		int ed=min(i,m);
		for(int j=0;j<=ed;j++)
		{
			f[i][j][0]=min(f[i-1][j][0]+w1,f[i-1][j][1]+w2);
			if(j>0) f[i][j][1]=min(f[i-1][j-1][0]+w3,f[i-1][j-1][1]+w4);
		}
	}
	double ans=RINF;
	for(int i=0;i<=m;i++)
		for(int j=0;j<2;j++)
			ans=min(ans,f[n][i][j]);
	printf("%.2lf\n",ans);
	return 0;
}
