#include<bits/stdc++.h>
using namespace std;

const int N=50000;
int prime[N],tot=0;
bool mark[N+10];
int u[N+10];

void Init()
{
	memset(mark,0,sizeof(mark));
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
	for(int i=1;i<=N;i++) u[i]+=u[i-1];
}

int main()
{
	Init();int T,n,m,d,div;
	for(cin>>T;T;T--)
	{
		scanf("%d%d%d",&n,&m,&d);
		n/=d;m/=d;
		if(n>m) swap(n,m);
		long long ans=0;
		for(int i=1;i<=n;i=div+1)
		{
			div=min(n/(n/i),m/(m/i));
			ans+=1ll*(u[div]-u[i-1])*(n/i)*(m/i);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
