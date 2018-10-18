#include<bits/stdc++.h>
#define Mod 1000000009
using namespace std;

typedef long long LL;
LL a[2010],b[2010];
LL fac[2010],C[2010][2010];
LL f[2010][2010];
int n,k;

void Init()
{
	for(int i=0;i<=n;i++)
	{
		C[i][0]=1;
		for(int j=1;j<=i;j++)
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%Mod;
	}
	fac[0]=1;
	for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%Mod;
}

int main()
{
	cin>>n>>k;
	if((n+k)&1){puts("0");return 0;}
	k=(n+k)/2;
	for(int i=1;i<=n;i++) scanf("%lld",a+i);
	for(int i=1;i<=n;i++) scanf("%lld",b+i);
	sort(a+1,a+1+n);sort(b+1,b+1+n);Init();
	for(int i=0;i<=n;i++) f[i][0]=1;
	for(int i=1,r=0;i<=n;i++)
	{
		while(r<n&&b[r+1]<a[i])r++;
		for(int j=1;j<=i;j++)
			f[i][j]=(f[i-1][j]+f[i-1][j-1]*max((r-j+1),0))%Mod;
	}
	for(int i=n;i>=k;i--)
	{
		f[n][i]=f[n][i]*fac[n-i]%Mod;
		for(int j=i+1;j<=n;j++)
			f[n][i]=(f[n][i]-f[n][j]*C[j][i]%Mod+Mod)%Mod;
	}
	cout<<(f[n][k]+Mod)%Mod<<endl;
	return 0;
}
