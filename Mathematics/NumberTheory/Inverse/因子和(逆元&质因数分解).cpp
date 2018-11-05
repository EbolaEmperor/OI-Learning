#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<vector>
#include<cstdlib>
#include<algorithm>
using namespace std;

typedef long long LL;

vector<LL> ans;

LL Gcd(LL x,LL y){return y==0?x:Gcd(y,x%y);}

LL QuickMul(LL a,LL b,LL p)
{
	LL ans=0;
	while(b)
	{
		if(b&1) ans=(ans+a)%p;
		a=(a+a)%p;
		b>>=1;
	}
	return ans;
}

LL QuickPow(LL a,LL b,LL p)
{
	LL ans=1;
	while(b)
	{
		if(b&1) ans=QuickMul(ans,a,p);
		a=QuickMul(a,a,p);
		b>>=1;
	}
	return ans;
}

bool FermatPrime(LL n)
{
	if(n==2) return 1;
	for(int i=1;i<=10;i++)
	{
		LL a=rand()%(n-2)+2;
		if(QuickPow(a,n,n)!=a) return 0;
	}
	return 1;
}

LL PollardRho(LL n,LL c)
{
	LL i=1,k=2;
	LL x=rand()%(n-1)+1;
	LL y=x;
	while(true)
	{
		i++;
		LL x=(QuickMul(x,x,n)+c)%n;
		LL d=Gcd((y-x+n)%n,n);
		if(d>1&&d<n) return d;
		if(y==x) return n;
		if(i==k){y=x;k<<=1;}
	}
	return -1;
}

void work(LL n,LL c)
{
	if(n==1) return;
	else if(FermatPrime(n)) ans.push_back(n);
	else
	{
		LL k=c,p=n;
		while(p>=n) p=PollardRho(p,c),c--;
		work(p,k);work(n/p,k);
	}
}

void ExGcd(LL a,LL b,LL &x,LL &y)
{
	if(b==0) {x=1,y=0;return;}
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
	srand(19260817);
	LL a,b;
	cin>>a>>b;
	work(a,120);
	sort(ans.begin(),ans.end());
	LL pre=0;
	vector<pair<LL,LL> > p;
	for(int i=0;i<ans.size();i++)
	{
		if(i==0||ans[i]!=ans[i-1])
		{
			p.push_back(pair<LL,LL>(ans[i],1));
			pre=ans[i];
		}
		else if(ans[i]==ans[i-1]) p[p.size()-1]=pair<LL,LL>(ans[i],p[p.size()-1].second+1);
	}
	LL s=1;
	for(int i=0;i<p.size();i++)
		s=s*((QuickPow(p[i].first,p[i].second*b+1,9901)-1)*inv(p[i].first-1,9901)%9901)%9901;
	cout<<s<<endl;
	return 0;
}
