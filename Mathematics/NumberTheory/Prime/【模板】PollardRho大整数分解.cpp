#include<bits/stdc++.h>
using namespace std;

typedef long long LL;

vector<LL> ans;

LL Mul(LL a,LL b,LL p){return (__uint128_t)a*b%p;}

LL Pow(LL a,LL b,LL p)
{
	LL ans=1;
	for(;b;b>>=1,a=Mul(a,a,p))
		if(b&1) ans=Mul(ans,a,p);
	return ans;
}

LL Gcd(LL a,LL b){return (b==0)?a:Gcd(b,a%b);}

bool MillerRabbin(LL n)
{
	if(n==2) return true;
	if(n<2||!(n&1)) return false;
	int t=0;
	LL a,x,y,u=n-1;
	while(!(u&1)) t++,u>>=1;
	for(int i=1;i<=10;i++)
	{
		a=rand()%(n-1)+1;
		x=Pow(a,u,n);
		for(int j=0;j<t;j++,x=y)
		{
			y=Mul(x,x,n);
			if(y==1&&x!=1&&x!=n-1) return false;
		}
		if(x!=1) return false;
	}
	return true; 
}

LL PollardRho(LL n,LL c)
{
	LL i=1,k=2;
	LL x=rand()%(n-1)+1;
	LL y=x,d;
	while(true)
	{
		i++;
		x=(Mul(x,x,n)+c)%n;
		d=Gcd((y-x+n)%n,n);
		if(d>1&&d<n) return d;
		if(x==y) return n;
		if(i==k) y=x,k<<=1;
	}
}

void gao(LL n)
{
	if(n==1) return;
	if(MillerRabbin(n)){ans.push_back(n);return;}
	LL p=n,c=19260817;
	while(p>=n) p=PollardRho(p,c--);
	gao(p);gao(n/p);
}

int main()
{
	int T;LL n;
	for(scanf("%d",&T);T;T--)
	{
		ans.clear();
		cin>>n;gao(n);
		sort(ans.begin(),ans.end());
		for(int i=0;i<ans.size();i++) printf("%lld ",ans[i]);
		putchar('\n');
	}
	return 0;
}
