#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=500;
LL phi[N+10];
int prime[95+10],tot=0;
bool mark[N];

void Init()
{
	memset(mark,0,sizeof(mark));
	for(int i=2;i<=N;i++)
	{
		if(!mark[i]) prime[++tot]=i,phi[i]=i-1;
		for(int j=1;j<=tot&&i*prime[j]<=N;j++)
		{
			mark[i*prime[j]]=1;
			if(i%prime[j]) phi[i*prime[j]]=phi[i]*(prime[j]-1);
			else phi[i*prime[j]]=phi[i]*prime[j];
		}
	}
	phi[1]=0;
	for(int i=2;i<=N;i++) phi[i]=phi[i-1]+phi[i];
}

int main()
{
	Init();
	int n;
	while(cin>>n&&n)
	{
		LL ans=0;
		for(int i=1;i<=n;i++)
			ans+=(LL)i*phi[n/i];
		cout<<ans<<endl;
	}
	return 0;
}
