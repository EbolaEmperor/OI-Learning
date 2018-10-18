#include<bits/stdc++.h>
#define Mod 1000000007
using namespace std;

typedef long long LL;
const int N=50000;
int phi[N+10];
int prime[N/5],tot=0;
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
}

int main()
{
	Init();
	int n,m;
	cin>>n>>m;
	if(n>m) swap(n,m);
	LL ans1=1ll*m*(m-1)*(m-2)/6%Mod*n%Mod;
	LL ans2=1ll*n*(n-1)*(n-2)/6%Mod*m%Mod;
	LL ans3=0;
	for(int d=1;d<n;d++)
	{
		LL res1=0;
		for(int i=1;i<=(n-1)/d;i++)
			res1=(res1+n-1ll*i*d)%Mod;
		LL res2=0;
		for(int i=1;i<=(m-1)/d;i++)
			res2=(res2+m-1ll*i*d)%Mod;
		res1=res1*res2%Mod;
		res1=1ll*phi[d]*res1%Mod;
		ans3=(ans3+res1)%Mod;
	}
	int x=0,y=0;
	for(int i=1;i<n;i++) x=(x+n-i)%Mod;
	for(int i=1;i<m;i++) y=(y+m-i)%Mod;
	ans3=(ans3-1ll*x*y%Mod+Mod)%Mod;
	ans3=ans3*2%Mod;
	LL ans=(ans1+ans2+ans3)%Mod;
	cout<<ans<<endl;
	return 0;
}
