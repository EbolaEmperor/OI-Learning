#include<bits/stdc++.h>
#define Mod 1000000007
using namespace std;

const int N=1000000;
int fac[N+10],ifac[N+10];

int Pow(int a,int b,int p)
{
	int ans=1;
	for(;b;a=1ll*a*a%p,b>>=1)
		if(b&1) ans=1ll*ans*a%p;
	return ans;
}

void Init()
{
	fac[0]=ifac[0]=1;
	for(int i=1;i<=N;i++)
		fac[i]=1ll*fac[i-1]*i%Mod;
	ifac[N]=Pow(fac[N],Mod-2,Mod);
	for(int i=N-1;i>=1;i--)
		ifac[i]=1ll*ifac[i+1]*(i+1)%Mod;
}

int C(int n,int k){return 1ll*fac[n]*ifac[k]%Mod*ifac[n-k]%Mod;}

int main()
{
	Init();
	int n,k,fg,tmp=2,ans=0;
	cin>>n>>k;
	for(int i=n-k;i>=0;i--)
	{
		fg=(i&1)?-1:1;
		ans=(ans+1ll*fg*C(n,k+i)*C(k+i,k)%Mod*tmp%Mod)%Mod;
		tmp=1ll*tmp*tmp%Mod;
	}
	cout<<(ans+Mod)%Mod<<endl;
	return 0;
}
