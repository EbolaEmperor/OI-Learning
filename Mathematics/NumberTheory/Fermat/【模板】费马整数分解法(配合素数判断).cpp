#include<bits/stdc++.h>
using namespace std;

typedef long long LL;

vector<LL> ans;

LL Init(LL n)
{
	while(n%2==0) n/=2,ans.push_back(2);
	return n;
}

pair<LL,LL> Fermat(LL n)
{
	LL a=(LL)ceil(sqrt(n));
	LL b2=a*a-n;
	while((LL)ceil(sqrt(b2))*(LL)ceil(sqrt(b2))!=b2)
	{
		a++;
		b2=a*a-n;
	}
	LL b=(LL)sqrt(b2);
	return make_pair(a-b,a+b);
}

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

void work(LL n)
{
	if(n==1) return;
	else if(FermatPrime(n)) ans.push_back(n);
	else
	{
		pair<LL,LL> x=Fermat(n);
		work(x.first);work(x.second);
	}
}

int main()
{
	printf("Input an integer:  ");
	LL n;
	cin>>n;
	printf("%lld",n);
	if(n%2==0)
	{
		n=Init(n);
		work(n);
	}
	else work(n);
	sort(ans.begin(),ans.end());
	printf(" = %lld",ans[0]);
	for(int i=1;i<(int)ans.size();i++) printf(" * %lld",ans[i]);
	putchar('\n');
	return 0;
}
