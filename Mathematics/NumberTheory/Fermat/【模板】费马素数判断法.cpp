#include<bits/stdc++.h>
using namespace std;

typedef long long LL;

LL QuickMul(LL a,LL b,LL mod)
{
	LL ans=0;
	a%=mod;
	while(b)
	{
		if(b&1) ans=(ans+a)%mod,b--;
		b>>=1;
		a=(a+a)%mod;
	}
	return ans;
}

LL QuickPow(LL a,LL b,LL mod)
{
	LL ans=1;
	a%=mod;
	while(b)
	{
		if(b&1) ans=QuickMul(ans,a,mod),b--;
		b>>=1;
		a=QuickMul(a,a,mod);
	}
	return ans;
}

bool FermatPrime(LL n)
{
	if(n==2) return true;
	for(int i=1;i<=10;i++)
	{
		LL a=rand()%(n-2)+2;
		if(QuickPow(a,n,n)!=a) return false;
	}
	return true;
}

int main()
{
	LL n;
	printf("Input an integer :  ");
	cin>>n;
	if(FermatPrime(n)) printf("%lld is a prime.\n",n);
	else printf("%lld is not a prime.\n",n);
	return 0;
}
