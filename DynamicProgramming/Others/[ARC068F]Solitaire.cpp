#include<bits/stdc++.h>
#define ha 1000000007
using namespace std;

const int N=2010;
int n,k,f[N][N];

int Pow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=1ll*a*a%ha)
		if(b&1) ans=1ll*ans*a%ha;
	return ans;
}

int main()
{
	scanf("%d%d",&n,&k);
	for(int i=2;i<=n;i++) f[1][i]=1;
	for(int i=1;i<k-1;i++)
	{
		f[i+1][n-i+1]=f[i][n-i+1];
		for(int j=n-i;j>=2;j--)
			f[i+1][j]=(f[i+1][j+1]+f[i][j])%ha;
	}
	int ans=0;
	for(int i=2;i<=n-k+2;i++)
		ans=(ans+f[k-1][i])%ha;
	if(k==1) ans=1;
	if(n-k<=0) printf("%d",ans);
	else printf("%d",1ll*ans*Pow(2,n-1-k)%ha);
	return 0;
}
