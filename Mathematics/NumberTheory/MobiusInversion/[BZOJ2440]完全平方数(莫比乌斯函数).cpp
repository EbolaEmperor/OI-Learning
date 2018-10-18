#include<bits/stdc++.h>
using namespace std;

const int N=50000;
int mu[N+10],n;
int prime[N],tot=0;
bool mark[N+10];

void Init()
{
	memset(mark,0,sizeof(mark));
	mu[1]=1;
	for(int i=2;i<=N;i++)
	{
		if(!mark[i]) prime[++tot]=i,mu[i]=-1;
		for(int j=1;j<=tot&&i*prime[j]<=N;j++)
		{
			mark[i*prime[j]]=1;
			if(i%prime[j]) mu[i*prime[j]]=-mu[i];
			else mu[i*prime[j]]=0;
		}
	}
}

bool check(int x)
{
	int res=0;
	for(int i=1;i*i<=x;i++)
		res+=mu[i]*(x/(i*i));
	return res<n;
}

int main()
{
	Init();
	int T;cin>>T;
	while(T--)
	{
		cin>>n;
		int l=1,r=2*n;
		while(l<r)
		{
			int mid=(1ll*l+r)/2;
			if(check(mid)) l=mid+1;
			else r=mid;
		}
		cout<<l<<endl;
	}
	return 0;
}
