#include<bits/stdc++.h>
using namespace std;

double G[110][110];
double ans[110];
int n;
const double eps=1e-9;
int dcmp(double x)
{
	if(fabs(x)<=eps) return 0;
	else if(x>0) return 1;
	else return -1;
}

bool Gauss()
{
	for(int i=1;i<=n;i++)
	{
		int pos=i;
		while(G[pos][i]==0&&pos<n) pos++;
		if(dcmp(G[pos][i])==0) return false;
		if(pos!=i)
			for(int j=1;j<=n+1;j++) swap(G[i][j],G[pos][j]);
		for(int j=i+1;j<=n;j++)
		{
			double t=G[j][i]/G[i][i];
			if(dcmp(G[j][i])==0) continue;
			for(int k=1;k<=n+1;k++)
				G[j][k]-=G[i][k]*t;
		}
	}
	return true;
}

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n+1;j++)
			scanf("%lf",&G[i][j]);
	if(Gauss())
	{
		for(int i=n;i>=1;i--)
		{
			for(int j=i+1;j<=n;j++)
				G[i][n+1]-=G[i][j]*ans[j];
			ans[i]=G[i][n+1]/G[i][i];
		}
		for(int i=1;i<=n;i++) printf("%.2lf\n",ans[i]);
	}
	else puts("No Solution");
	return 0;
}
