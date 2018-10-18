#include<iostream>
#include<cstdio>
#include<cmath>
#include<map>
using namespace std;

typedef long long LL;

LL QuickPow(LL a,LL b,LL p)
{
	LL ans=1;
	while(b)
	{
		if(b&1) ans=ans*a%p;
		b>>=1;
		a=a*a%p;
	}
	return ans;
}

LL ExGcd(LL a,LL b,LL &x,LL &y)
{
	if(b==0){x=1;y=0;return a;}
	LL g=ExGcd(b,a%b,x,y);
	LL t=x;
	x=y;
	y=t-(a/b)*y;
	return g;
}

LL BSGS(LL a,LL b,LL p)
{
	map<LL,LL> f;
	LL base=1;
	LL m=(LL)ceil(sqrt(p));
	for(LL i=0;i<m;i++)
	{
		f.insert(pair<LL,LL>(base,i));
		base=base*a%p;
	}
	LL d=1;
	for(LL i=0;i<m;i++)
	{
		LL x,tmp;
		LL gcd=ExGcd(d,p,x,tmp);
		if(b%gcd!=0) continue;
		x=(x*b%p+p)%p;
		if(f.count(x)!=0) return i*m+f[x];
		d=d*base%p;
	}
	return -1;
}

int main()
{
	int t,k;
	cin>>t>>k;
	for(int i=1;i<=t;i++)
	{
		LL y,z,p;
		cin>>y>>z>>p;
		if(k==1) cout<<QuickPow(y,z,p)<<endl;
		if(k==2)
		{
			LL x,tmp;
			LL gcd=ExGcd(y,p,x,tmp);
			x=(x%p+p)%p;
			if(z%gcd!=0) {puts("Orz, I cannot find x!");continue;}
			x=x*z%p;
			cout<<x<<endl;
		}
		if(k==3)
		{
			LL ans=BSGS(y,z,p);
			if(ans==-1) puts("Orz, I cannot find x!");
			else cout<<ans<<endl;
		}
	}
	return 0;
}
