#include<bits/stdc++.h>
#define ha 10007
using namespace std;

int fac[ha+5],ifac[ha+5];

int Pow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=1ll*a*a%ha)
		if(b&1) ans=1ll*ans*a%ha;
	return ans;
}

void Init()
{
	fac[0]=1;
	for(int i=1;i<ha;i++)
		fac[i]=1ll*fac[i-1]*i%ha;
	ifac[ha-1]=Pow(fac[ha-1],ha-2);
	for(int i=ha-2;i>=0;i--)
		ifac[i]=1ll*ifac[i+1]*(i+1)%ha;
}

int C(int n,int m){return (n<m)?0:1ll*fac[n]*ifac[m]%ha*ifac[n-m]%ha;}
int Lucas(int n,int m)
{
	if(n<ha&&m<ha) return C(n,m);
	return 1ll*Lucas(n/ha,m/ha)*C(n%ha,m%ha)%ha;
}

int main()
{
	Init();
	int T,n,m;
	for(scanf("%d",&T);T;T--)
	{
		scanf("%d%d",&n,&m);
		printf("%d\n",Lucas(n,m));
	}
	return 0;
}
