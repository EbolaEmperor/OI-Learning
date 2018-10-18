#include<bits/stdc++.h>
#define ha 998244353
using namespace std;

const int N=1010,M=10010;
int p[N],f[2][M][15];

int Pow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=1ll*a*a%ha)
		if(b&1) ans=1ll*ans*a%ha;
	return ans;
}

int main()
{
	int n,k,m;
	scanf("%d%d%d",&n,&k,&m);
	k=n-k+1;
	for(int i=1;i<=n;i++) scanf("%d",p+i);
	int falun=0;
	for(int i=1;i<=k;i++) f[1][0][i]=-1;
	for(int i=1;i<=n;i++,falun^=1)
		for(int j=0;j<=m;j++)
			for(int l=1;l<=k;l++)
			{
				f[falun][j][l]=f[falun^1][j][l];
				if(j>=p[i]) f[falun][j][l]=(1ll*f[falun][j][l]+f[falun^1][j-p[i]][l-1]-f[falun^1][j-p[i]][l])%ha;	
			}
	int ans=0;
	for(int i=1;i<=m;i++)
		ans=(ans+1ll*m*Pow(i,ha-2)%ha*f[falun^1][i][k])%ha;
	printf("%d\n",(ans+ha)%ha);
	return 0;
}
