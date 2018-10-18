#include<bits/stdc++.h>
#define Mod 1000000007
using namespace std;

typedef long long LL;
const int N=7000000;
int u[N+10];
int prime[650000],tot=0;
bool mark[N+10];
map<int,int> mu;

void Init()
{
	u[1]=1;
	for(int i=2;i<=N;i++)
	{
		if(!mark[i]) prime[++tot]=i,u[i]=-1;
		for(int j=1;j<=tot&&i*prime[j]<=N;j++)
		{
			mark[i*prime[j]]=1;
			if(i%prime[j]) u[i*prime[j]]=-u[i];
			else u[i*prime[j]]=0;
		}
	}
	for(int i=2;i<=N;i++) u[i]+=u[i-1];
}

int Su(int n)
{
	if(n<=N) return u[n];
	if(mu.count(n)) return mu[n];
	int div,res=1;
	for(int i=2;i<=n;i=div+1)
	{
		div=n/(n/i);
		res-=(div-i+1)*Su(n/i);
	}
	mu[n]=res;
	return res;
}

int Sdiv(int n)
{
	int div;LL ans=0;
	for(int i=1;i<=n;i=div+1)
	{
		div=n/(n/i);
		ans=(ans+(div-i+1)*(n/i)%Mod)%Mod;
	}
	return ans;
}

int main()
{
	Init();
	int n,div;cin>>n;
	LL ans=0;
	for(int i=1;i<=n;i=div+1)
	{
		div=n/(n/i);
		int smu=Su(div)-Su(i-1);
		LL sf=Sdiv(n/i);
		sf=sf*sf%Mod;
		ans=(ans+(LL)smu*sf%Mod+Mod)%Mod;
	}
	cout<<ans<<endl;
	return 0;
}
