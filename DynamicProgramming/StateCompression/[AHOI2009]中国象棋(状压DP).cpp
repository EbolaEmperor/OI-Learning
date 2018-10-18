#include<iostream>
#include<cstdio>
#include<cstring>
#define MOD 9999973
using namespace std;

long long f[110][110][110];//第i行，目前放1个的有j列，放2个的有k列
int n,m;
int C(int x){return (x-1)*x/2;}

int main()
{
	memset(f,0,sizeof(f));
	cin>>n>>m;
	f[0][0][0]=1;
	for(int i=0;i<n;i++)
		for(int j=0;j<=m;j++)
			for(int k=0;j+k<=m;k++)
			{
				f[i+1][j][k]=(f[i+1][j][k]+f[i][j][k])%MOD;//不放
				if(m-j-k>=1) f[i+1][j+1][k]=(f[i+1][j+1][k]+f[i][j][k]*(m-j-k))%MOD;//空位上放一个
				if(j>=1) f[i+1][j-1][k+1]=(f[i+1][j-1][k+1]+f[i][j][k]*j)%MOD;//有一个的地方放一个
				if(m-j-k>=2) f[i+1][j+2][k]=(f[i+1][j+2][k]+f[i][j][k]*C(m-j-k))%MOD;//空位上放两个
				if(j>=2) f[i+1][j-2][k+2]=(f[i+1][j-2][k+2]+f[i][j][k]*C(j))%MOD;//有一个的地方放两个
				if(m-j-k>=1&&j>=1) f[i+1][j][k+1]=(f[i+1][j][k+1]+f[i][j][k]*(m-j-k)*j)%MOD;//空位、有一个的地方各放一个
			}
	long long ans=0;
	for(int i=0;i<=m;i++)
		for(int j=0;i+j<=m;j++)
			ans=(ans+f[n][i][j])%MOD;
	cout<<ans<<endl;
	return 0;
}
