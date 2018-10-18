#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=10000000;
int prime[664579+10],tot=0;
int e[N+10],g[N+10];
LL f[N+10];
bool mark[N+10];

void Init()
{
	memset(mark,0,sizeof(mark));
	for(int i=2;i<=N;i++)
	{
		if(!mark[i]) prime[++tot]=i,f[i]=e[i]=1,g[i]=i;
		for(int j=1;j<=tot&&i*prime[j]<=N;j++)
		{
			mark[i*prime[j]]=1;
			if(i%prime[j])
			{
				g[i*prime[j]]=prime[j];
				e[i*prime[j]]=1;
				f[i*prime[j]]=(e[i]==1)?-f[i]:0;
			}
			else
			{
				g[i*prime[j]]=g[i]*prime[j];
				e[i*prime[j]]=e[i]+1;
				int tmp=i/g[i];
				if(tmp==1) f[i*prime[j]]=1;
				else f[i*prime[j]]=(e[tmp]==e[i*prime[j]])?-f[tmp]:0;
				break;
			}
		}
	}
	for(int i=1;i<=N;i++) f[i]+=f[i-1];
}

int main()
{
	Init();
	int T;cin>>T;
	while(T--)
	{
		int n,m,j;cin>>n>>m;
		if(n>m) swap(n,m);
		LL ans=0;
		for(int i=1;i<=n;i=j+1)
		{
			j=min(n/(n/i),m/(m/i));
			ans+=(LL)(n/i)*(m/i)*(f[j]-f[i-1]);
		}
		cout<<ans<<endl;
	}
	return 0;
}
