#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;

long long a[300][300],f[300],n,m;

int main()
{
	int x,y;
	cin>>n>>m;
	for(int i=0;i<=n+5;i++) f[i]=0x7fffffff;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		for(int j=1;j<=n;j++)
			a[i][j]=(long long)x*(long long)(pow((double)j,y));
	}
	f[0]=0;
	for(int i=1;i<=m;i++)
		for(int j=n;j>=1;j--)
			for(int k=0;k<=j;k++)
				f[j]=min(f[j],f[j-k]+a[i][k]);
	cout<<f[n]<<endl;
	return 0;
}
