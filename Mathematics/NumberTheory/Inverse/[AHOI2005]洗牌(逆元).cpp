#include<iostream>
#include<cstdio>
using namespace std;

typedef long long LL;

LL QuickPow(LL a,LL b,LL p)
{
	LL ans=1;
	while(b)
	{
		if(b&1) ans=(ans*a)%p;
		a=(a*a)%p;
		b>>=1;
	}
	return ans;
}

void ExGcd(LL a,LL b,LL &x,LL &y)
{
	if(b==0){x=1;y=0;return;}
	ExGcd(b,a%b,x,y);
	LL t=x;
	x=y;
	y=t-(a/b)*y;
}

LL inv(LL n,LL p)
{
	LL x,y;
	ExGcd(n,p,x,y);
	return (x%p+p)%p;
}

int main()
{
	LL n,m,l;
	cin>>n>>m>>l;
	LL ans=QuickPow(2,m,n+1);
	ans=inv(ans,n+1);
	ans=l*ans%(n+1);
	cout<<ans<<endl;
	return 0;
}
