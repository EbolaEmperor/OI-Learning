#include<bits/stdc++.h>
#define ha 1000000007
using namespace std;

const int N=10000005;
int pre[N+10],suf[N+10],n,k;
int ifac[N+10],pw[N+10];
int prm[N/10],tot=0;
bool mark[N+10];

int Pow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=1ll*a*a%ha)
		if(b&1) ans=1ll*ans*a%ha;
	return ans;
}

void Initfac()
{
	int facn=1;
	for(int i=1;i<=N;i++)
		facn=1ll*facn*i%ha;
	ifac[N]=Pow(facn,ha-2);
	for(int i=N-1;i>=0;i--)
		ifac[i]=1ll*ifac[i+1]*(i+1)%ha;
}

void Initprm()
{
	pw[1]=1;
	for(int i=2;i<=N;i++)
	{
		if(!mark[i])
		{
			prm[++tot]=i;
			mark[i]=1;
			pw[i]=Pow(i,k);
		}
		for(int j=1;j<=tot&&i*prm[j]<=N;j++)
		{
			mark[i*prm[j]]=1;
			pw[i*prm[j]]=1ll*pw[i]*pw[prm[j]]%ha;
			if(i%prm[j]==0) break;
		}
	}
	for(int i=1;i<=N;i++) pw[i]=(pw[i]+pw[i-1])%ha;
}

int Lagrange(int *y,int n,int k)
{
	pre[0]=suf[n+1]=1;
	for(int i=1;i<=n;i++) pre[i]=1ll*pre[i-1]*(k-i)%ha;
	for(int i=n;i>=1;i--) suf[i]=1ll*suf[i+1]*(k-i)%ha;
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		int s1=1ll*pre[i-1]*suf[i+1]%ha;
		int s2=1ll*ifac[i-1]*ifac[n-i]%ha;
		int fg=(n-i)&1?-1:1;
		ans=(ans+1ll*fg*s1*s2%ha*y[i])%ha;
	}
	return (ans+ha)%ha;
}

int main()
{
	scanf("%d%d",&n,&k);
	Initfac();Initprm();
	if(n<=k+2) printf("%d\n",pw[n]);
	else printf("%d\n",Lagrange(pw,k+2,n));
	return 0;
}
