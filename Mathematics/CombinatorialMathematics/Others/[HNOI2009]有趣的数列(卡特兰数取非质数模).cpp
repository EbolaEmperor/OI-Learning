#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

typedef long long LL;

bool mark[2000010];
int prime[2000010],tot=0;

void Prime(int n)
{
	memset(mark,0,sizeof(mark));
	for(int i=2;i<=n;i++)
	{
		if(!mark[i]) prime[++tot]=i;
		for(int j=1;j<=tot&&i*prime[j]<=n;j++)
		{
			mark[i*prime[j]]=1;
			if(i%prime[j]==0) break;
		}
	}
}

LL QuickPow(LL a,LL b,LL Mod)
{
	LL ans=1;
	while(b)
	{
		if(b&1) ans=ans*a%Mod;
		a=a*a%Mod;
		b>>=1;
	}
	return ans;
}

LL Catalan(LL n,LL Mod)
{
	Prime(2*n);
	LL ans=1;
	for(int i=1;i<=tot;i++)
	{
		LL x=2*n;
		LL b=0;
		while(x>0) x/=prime[i],b+=x;
		x=n;
		while(x>0) x/=prime[i],b-=x;
		x=n+1;
		while(x>0) x/=prime[i],b-=x;
		ans=ans*QuickPow(prime[i],b,Mod)%Mod;
	}
	return ans;
}

int main()
{
	LL n,p;
	cin>>n>>p;
	cout<<Catalan(n,p)<<endl;
	return 0;
}
