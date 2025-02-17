#include<iostream>
#include<cstdio>
#include<cmath>
#include<map>
using namespace std;

typedef long long LL;

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
	int T;
	for(cin>>T;T;T--)
	{
		LL p,a,b,x,t;
		cin>>p>>a>>b>>x>>t;
		if(x==t){cout<<1<<endl;continue;}
		if(a==0)
		{
			if(t==b) cout<<2<<endl;
			else cout<<-1<<endl;
			continue;
		}
		if(a==1)
		{
			if(b==0){cout<<-1<<endl;continue;}
			LL b_,tmpb;
			ExGcd(b,p,b_,tmpb);
			b_=(b_%p+p)%p;
			LL ans=(((t-x)%p+p)%p*b_)%p;
			cout<<(ans+1)<<endl;
			continue;
		}
		LL d_,tmp;
		ExGcd(a-1,p,d_,tmp);
		d_=(d_+p)%p;
		LL c=(t+b*d_%p)%p;
		LL k=(x+b*d_%p)%p,k_;
		ExGcd(k,p,k_,tmp);
		k_=(k_+p)%p;
		c=c*k_%p;
		LL ans=BSGS(a,c,p);
		if(ans==-1) cout<<-1<<endl;
		else cout<<(ans+1)<<endl;
	}
	//system("pause");
	return 0;
}
