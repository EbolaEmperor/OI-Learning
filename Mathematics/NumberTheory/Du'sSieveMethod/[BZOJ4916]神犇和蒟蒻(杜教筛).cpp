#include<bits/stdc++.h>
#define Mod 1000000007
#define inv6 166666668
#define inv2 500000004
using namespace std;

typedef long long LL;
const int N=7000000;
int prime[664579+10],tot=0;
LL phi[N+10];
bool mark[N+10];
map<int,LL> sphi;

void Init()
{
	phi[1]=1;
	for(int i=2;i<=N;i++)
	{
		if(!mark[i]) prime[++tot]=i,phi[i]=i-1;
		for(int j=1;j<=tot&&i*prime[j]<=N;j++)
		{
			mark[i*prime[j]]=1;
			if(i%prime[j]) phi[i*prime[j]]=(prime[j]-1)*phi[i];
			else phi[i*prime[j]]=prime[j]*phi[i];
		}
	}
	for(int i=1;i<=N;i++) phi[i]=(phi[i-1]+(LL)i*phi[i])%Mod;
}

LL Sum(LL n)
{
	if(n<=N) return phi[n]%Mod;
	if(sphi.count(n)) return sphi[n];
	LL div,res=(n*(n+1)%Mod)*(2*n+1)%Mod;
	res=res*inv6%Mod;
	for(LL i=2;i<=n;i=div+1)
	{
		div=n/(n/i);
		LL s=((i+div)*(div-i+1)%Mod)*inv2%Mod;
		res=(res-s*Sum(n/i)%Mod+Mod)%Mod;
	}
	sphi[n]=res;
	return res;
}

int main()
{
	Init();
	LL n;
	cin>>n;
	puts("1");
	cout<<Sum(n)<<endl;
	return 0;
}
