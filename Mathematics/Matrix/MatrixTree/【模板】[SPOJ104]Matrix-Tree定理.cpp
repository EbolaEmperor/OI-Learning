#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;

double G[105][105];
const double eps=1e-9;
int dcmp(double x)
{
	if(fabs(x)<=eps) return 0;
	else if(x>0) return 1;
	else return -1;
}

double Gauss(int n)
{
	n--;
	for(int i=1;i<=n;i++)
	{
		int pos=i;
		for(int j=i+1;j<=n;j++)
			if(dcmp(G[j][i]-G[pos][i])>0) pos=j;
		if(dcmp(G[pos][i])==0) return 0;
		if(pos!=i)
			for(int j=1;j<=n+1;j++) swap(G[i][j],G[pos][j]);
		for(int j=i+1;j<=n;j++)
		{
			if(dcmp(G[j][i])==0) continue;
			double t=G[j][i]/G[i][i];
			for(int k=1;k<=n+1;k++)
				G[j][k]-=t*G[i][k];
		}
	}
	double ans=1;
	for(int i=1;i<=n;i++) ans*=G[i][i];
	return fabs(ans);
}

int main()
{
	int T;
	for(cin>>T;T;T--)
	{
		int n,m,a,b;
		cin>>n>>m;
		memset(G,0,sizeof(G));
		for(int i=1;i<=m;i++)
		{
			scanf("%d%d",&a,&b);
			G[a][a]++;
			G[b][b]++;
			G[a][b]--;
			G[b][a]--;
		}
		printf("%.0lf\n",Gauss(n));
	}
	return 0;
}
