#include<bits/stdc++.h>
#define Mod 1000000007
using namespace std;

typedef long long LL;
const int N=7000000;
int prime[N/10],tot=0;
int u[N+10];
bool mark[N+10];
map<int,int> su;

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
			else{u[i*prime[j]]=0;break;}
		}
	}
	for(int i=1;i<=N;i++) u[i]+=u[i-1];
}

int Su(int n)
{
	if(n<=N) return u[n];
	if(su.count(n)) return su[n];
	int div,ans=1;
	for(int i=2;i<=n;i=div+1)
	{
		div=n/(n/i);
		ans-=(div-i+1)*Su(n/i);
	}
	su[n]=ans;
	return ans;
}

int QuickPow(int a,int b)
{
	int ans=1;
	while(b)
	{
		if(b&1) ans=1ll*ans*a%Mod;
		a=1ll*a*a%Mod;
		b>>=1;
	}
	return ans;
}

int main()
{
	Init();
	int n,k,l,h;
	cin>>n>>k>>l>>h;
	int a=h/k,b=(l-1)/k,div,tmp;
	LL ans=0;
	for(int i=1;i<=a;i=div+1)
	{
		if(b/i) div=min(a/(a/i),b/(b/i));
		else div=a/(a/i);
		tmp=Su(div)-Su(i-1);
		ans=(ans+1ll*tmp*QuickPow(a/i-b/i,n))%Mod;
	}
	ans=(ans%Mod+Mod)%Mod;
	cout<<ans<<endl;
	return 0;
}
