#include<bits/stdc++.h>
#define ha 1000000007
using namespace std;

const int N=10000000;
int pre[N+10],suf[N+10];
int ifac[N+10];
int arry[N+10];

int Pow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=1ll*a*a%ha)
		if(b&1) ans=1ll*ans*a%ha;
	return ans;
}

void Init()
{
	int facn=1;
	for(int i=1;i<=N;i++)
		facn=1ll*facn*i%ha;
	ifac[N]=Pow(facn,ha-2);
	for(int i=N-1;i>=0;i--)
		ifac[i]=1ll*ifac[i+1]*(i+1)%ha;
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
	int n,x;Init();
	scanf("%d%d",&n,&x);
	for(int i=1;i<=n;i++)
		scanf("%d",arry+i);
	printf("%d\n",Lagrange(arry,n,x));
	return 0;
}
