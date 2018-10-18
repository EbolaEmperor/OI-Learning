#include<bits/stdc++.h>
#define ha 1234567891
using namespace std;

typedef long long LL;
LL Pow(LL a,LL b)
{
	LL ans=1;
	for(;b;b>>=1,a=a*a%ha)
		if(b&1) ans=ans*a%ha;
	return ans;
}

LL Lagrange(LL *x,LL *y,int n,LL k)
{
	LL ans=0;
	for(int i=0;i<n;i++)
	{
		if(x[i]==k) return y[i];
		LL t1=1,t2=1;
		for(int j=0;j<n;j++)
		{
			if(i==j) continue;
			t1=t1*(k-x[j])%ha;
			t2=t2*(x[i]-x[j])%ha;
		}
		ans=(ans+y[i]*t1%ha*Pow(t2,ha-2))%ha;
	}
	return (ans+ha)%ha;
}

LL f[150],g[150],h[150],arrx[150];

int main()
{
	int T;LL k,a,n,d;
	for(scanf("%d",&T);T;T--)
	{
		scanf("%lld%lld%lld%lld",&k,&a,&n,&d);
		for(int i=0;i<=k+5;i++) arrx[i]=i;
		for(int i=1;i<=k+3;i++) f[i]=(f[i-1]+Pow(i,k))%ha;
		for(int i=1;i<=k+3;i++) g[i]=(g[i-1]+f[i])%ha;
		h[0]=Lagrange(arrx+1,g+1,k+3,a);
		for(int i=1;i<=k+4;i++)
			h[i]=(h[i-1]+Lagrange(arrx+1,g+1,k+3,(a+1ll*i*d)%ha))%ha;
		printf("%lld\n",Lagrange(arrx,h,k+5,n));
	}
	return 0;
}
