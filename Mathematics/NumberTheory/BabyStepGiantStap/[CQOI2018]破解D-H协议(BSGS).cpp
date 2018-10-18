#include<bits/stdc++.h>
using namespace std;

typedef long long LL;

LL QuickPow(LL a,LL b,LL p)
{
	LL ans=1;
	while(b)
	{
		if(b&1) ans=ans*a%p;
		a=a*a%p;
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

LL BSGS(LL a,LL b,LL p)
{
	map<LL,LL> f;
	LL m=(LL)ceil(sqrt(p));
	LL base=1;
	for(LL i=0;i<m;i++)
	{
		f.insert(pair<LL,LL>(base,i));
		base=base*a%p;
	}
	LL d=1;
	for(LL i=0;i<m;i++)
	{
		LL x,y;
		ExGcd(d,p,x,y);
		x=(x*b%p+p)%p;
		if(f.count(x)!=0) return i*m+f[x];
		d=d*base%p;
	}
	return -1;
}

int main()
{
	LL g,P,T;
	cin>>g>>P;
	for(cin>>T;T;T--)
	{
		LL A,B;
		cin>>A>>B;
		LL b=BSGS(g,B,P);
		cout<<QuickPow(A,b,P)<<endl;
	}
	return 0;
}
