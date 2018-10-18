#include<bits/stdc++.h>
#define pb push_back
using namespace std;

typedef long long LL;
const int N=1000000;
vector<LL> ans,b,c;
bool mark[N+10];
int prime[N/5],tot=0;

LL Gcd(LL x,LL y){return y==0?x:Gcd(y,x%y);}

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

void putd(int c)
{
	vector<int> ds;
	ds.push_back(1);
	while(c--)
	{
		int a=0;
		for (int i=0;i<ds.size();i++)
		{
			ds[i]=2*ds[i]+a;a=0;
			if(ds[i]>=10) ds[i]-=10,a=1;
    	}
		if(a) ds.push_back(a);
	}
	ds[0]--;int i=0;
	while(ds[i]<0) ds[i++]+=10,ds[i]--;
	for (int i=ds.size()-1;i>=0;i--)
		printf("%d",ds[i]);
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

void Init()
{
	for(int i=2;i<=N;i++)
	{
		if(!mark[i]) prime[++tot]=i;
		for(int j=1;j<=tot&&i*prime[j]<=N;j++)
		{
			mark[i*prime[j]]=1;
			if(i%prime[j]==0) break;
		}
	}
}

LL getsqrt(LL n)
{
	LL x=sqrt(n);
	for(LL i=x-2;i<=x+2;i++)
		if(i*i==n)return i;
	return 0;
}

void divide()
{
	LL n;scanf("%lld",&n);
	for(int i=1;i<=tot&&prime[i]<=n;i++)
		while(n%prime[i]==0)n/=prime[i],ans.pb(prime[i]);
	if(n==1) return;
	if(FermatPrime(n)){ans.pb(n);c.pb(n);return;}
	LL t=getsqrt(n);
	if(t){ans.pb(t);ans.pb(t);c.pb(t);return;}
	b.pb(n);
}

void solve(LL n)
{
	for(int i=0;i<c.size();i++)
		if(n%c[i]==0)
		{
			ans.pb(c[i]);
			ans.pb(n/c[i]);
			return;
		}
	for(int i=0;i<b.size();i++)
	{
		LL t=Gcd(n,b[i]);
		if(t==1||t==n)continue;
		ans.pb(t);ans.pb(n/t);
		return;
	}
	ans.pb(-n);
}

int main()
{
	int m;LL x;Init();
	for(scanf("%d",&m);m;m--) divide();
	for(int i=0;i<b.size();i++) solve(b[i]);
	sort(ans.begin(),ans.end());
	int k=0,d=0,t=0;
	for(int i=0;i<ans.size();i++)
	{
		if(i==0||ans[i]==ans[i-1]) t++;
		else t=1;
		if(t>k) k=t,d=(ans[i]<0)?2:1;
		else if(t==k) d+=(ans[i]<0)?2:1;
	}
	printf("%d\n",k);putd(d);
	return 0;
}
