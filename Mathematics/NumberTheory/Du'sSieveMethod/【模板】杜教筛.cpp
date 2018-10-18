#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=7000000;
int prime[N],tot=0;
LL phi[N+10];
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
			if(i%prime[j]) phi[i*prime[j]]=(prime[j]-1)*phi[i];
			else phi[i*prime[j]]=prime[j]*phi[i];
		}
	}
	for(int i=1;i<=N;i++) phi[i]+=phi[i-1];
}

LL Sphi(LL n)
{
	if(n<=N) return phi[n];
	LL res=n*(n+1)/2,div;
	for(LL i=2;i<=n;i=div+1)
	{
		div=n/(n/i);
		res-=(div-i+1)*Sphi(n/i);
	}
	return res;
}

int main()
{
	Init();
	LL n;
	cin>>n;
	cout<<Sphi(n)<<endl;
	return 0;
}

/*
Description : Çósigma{phi(i)},i=1~n
Sample Input : 1000000000
Sample Output : 303963551173008414
HINT : n<=10^9
Time Limit : 1s
Memory Limit : 512MB
*/
