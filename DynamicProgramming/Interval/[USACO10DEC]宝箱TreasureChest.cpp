#include<iostream>
#include<cstdio>
using namespace std;

int n,c[5010];
int f[5010][5010];
int sum[5010];

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",c+i);
		f[i][i]=c[i];
		sum[i]=sum[i-1]+c[i];
	}
	for(int i=n-1;i>=1;i--)
		for(int j=i+1;j<=n;j++)
			f[i][j]=max(sum[j]-sum[i-1]-f[i+1][j],sum[j]-sum[i-1]-f[i][j-1]);
	cout<<f[1][n]<<endl;
	return 0;
}
