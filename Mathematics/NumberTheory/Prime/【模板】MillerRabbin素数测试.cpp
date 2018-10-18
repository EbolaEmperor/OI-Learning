#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
LL QuickMul(LL a,LL b,LL mod)
{
	LL ans=0;
	while(b)
	{
		if(b&1) ans=(ans+a)%mod;
		b>>=1;
		a=(a+a)%mod;
	}
	return ans;
}

LL QuickPow(LL a,LL b,LL mod)
{
	LL ans=1;
	while(b)
	{
		if(b&1) ans=QuickMul(ans,a,mod);
		b>>=1;
		a=QuickMul(a,a,mod);
	}
	return ans;
}

bool MillerRabbin(LL n)
{
	if(n==2) return true;
	if(n<2||!(n&1)) return false;
	int t=0;
	LL a,x,y,u=n-1;
	while(!(u&1)) t++,u>>=1;
	for(int i=0;i<10;i++)
	{
		a=rand()%(n-1)+1;
		x=QuickPow(a,u,n);
		for(int j=0;j<t;j++,x=y)
		{
			y=QuickMul(x,x,n);
			if(y==1&&x!=1&&x!=n-1) return false;
		}
		if (x!=1) return false;
	}
	return true;
}

int main()
{
	int T;LL n;
	for(scanf("%d",&T);T;T--)
	{
		scanf("%lld",&n);
		puts(MillerRabbin(n)?"Yes":"No");
	}
	return 0;
}
