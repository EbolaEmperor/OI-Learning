#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=10000000;
LL phi[N+10];
int prime[N/10],tot=0;
bool mark[N+10];

void Init()
{
	phi[1]=1;
	for(int i=2;i<=N;i++)
	{
		if(!mark[i]) prime[++tot]=i,phi[i]=i-1;
		for(int j=1;j<=tot&&i*prime[j]<=N;j++)
		{
			mark[i*prime[j]]=1;
			if(i%prime[j]) phi[i*prime[j]]=phi[i]*(prime[j]-1);
			else{phi[i*prime[j]]=phi[i]*prime[j];break;}
		}
	}
	for(int i=1;i<=N;i++) phi[i]+=phi[i-1];
}

int main()
{
	Init();
	int T,n,div;
	for(scanf("%d",&T);T;T--)
	{
		scanf("%d",&n);
		LL ans=0;
		for(int d=1;d<=n;d=div+1)
		{
			div=n/(n/d);
			ans+=(phi[div]-phi[d-1])*(2*phi[n/d]-1);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
