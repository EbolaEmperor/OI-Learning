#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=10000000;
int u[N+10],f[N+10],sum[N+10];
int prime[N+10],tot=0;
bool mark[N+10];

void Init()
{
	memset(mark,0,sizeof(mark));
	u[1]=1;f[1]=0;
	for(int i=2;i<=N;i++)
	{
		if(!mark[i])
		{
			prime[++tot]=i;
			u[i]=-1;f[i]=1;
		}
		for(int j=1;j<=tot&&i*prime[j]<=N;j++)
		{
			mark[i*prime[j]]=1;
			if(i%prime[j]) u[i*prime[j]]=-u[i],f[i*prime[j]]=u[i]-f[i];
			else {u[i*prime[j]]=0,f[i*prime[j]]=u[i];break;}
		}
	}
	sum[0]=0;
	for(int i=1;i<=N;i++) sum[i]=sum[i-1]+f[i];
}

int main()
{
	Init();
	int T,n,m,j;
	scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m);
		if(n>m) swap(n,m);
		LL ans=0;
		for(int k=1;k<=n;k=j+1)
		{
			j=min(n/(n/k),m/(m/k));
			ans+=(LL)(sum[j]-sum[k-1])*(n/k)*(m/k);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
