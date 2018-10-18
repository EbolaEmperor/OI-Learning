#include<bits/stdc++.h>
#define Mod 100000009
using namespace std;

typedef long long LL;
const int N=10000000;
int prime[664579+10],tot=0;
bool mark[N+10];
LL f[N+10],sum[N+10];

void Init()
{
	f[1]=1;
	for(int i=2;i<=N;i++)
	{
		if(!mark[i]) prime[++tot]=i,f[i]=((1-i)%Mod+Mod)%Mod;
		for(int j=1;j<=tot&&i*prime[j]<=N;j++)
		{
			mark[i*prime[j]]=1;
			if(i%prime[j]) f[i*prime[j]]=f[i]*f[prime[j]]%Mod;
			else f[i*prime[j]]=f[i];
		}
	}
	for(int i=1;i<=N;i++) f[i]=(f[i-1]+(LL)i*f[i]%Mod)%Mod;
	for(int i=1;i<=N;i++) sum[i]=(sum[i-1]+(LL)i)%Mod;
}

int main()
{
	Init();
	int n,m,j,t;
	cin>>t;
	while(t--)
	{
		scanf("%d%d",&n,&m);
		if(n>m) swap(n,m);
		LL ans=0;
		for(int i=1;i<=n;i=j+1)
		{
			j=min(n/(n/i),m/(m/i));
			ans=(ans+(sum[n/i]*sum[m/i]%Mod)*(f[j]-f[i-1]+Mod)%Mod)%Mod;
		}
		printf("%lld\n",ans);
	}
	return 0;
}
