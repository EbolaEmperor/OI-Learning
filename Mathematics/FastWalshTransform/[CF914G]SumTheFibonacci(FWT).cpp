#include<bits/stdc++.h>
#define Mod 1000000007
#define inv2 500000004
using namespace std;

const int N=(1<<18)+10,M=1<<17;
const int AND=1,OR=2,XOR=3;
int a[N],f[N],g[N],h[N],fib[N];
int dp[20][N],dp2[20][N],size[N];

void FWT(int *a,int n,bool DWT,int type)
{
	for(int i=1;i<n;i<<=1)
		for(int j=0;j<n;j+=(i<<1))
			for(int k=0;k<i;k++)
			{
				int x=a[j+k],y=a[i+j+k];
				if(DWT)
				{
					if(type==XOR) a[j+k]=(x+y)%Mod,a[i+j+k]=(x-y+Mod)%Mod;
					if(type==AND) a[j+k]=(x+y)%Mod;
					if(type==OR) a[i+j+k]=x+y;
				}
				else
				{
					if(type==XOR) a[j+k]=1ll*(x+y)*inv2%Mod,a[i+j+k]=1ll*(x-y+Mod)*inv2%Mod;
					if(type==AND) a[j+k]=(x-y+Mod)%Mod;
					if(type==OR) a[i+j+k]=(y-x+Mod)%Mod;
				}
			}
}

void FST()
{
	for(int s=0;s<M;++s)
		for(int i=0;i<=17;++i)
			if((s>>i)&1) size[s]++;
	for(int i=0;i<N;++i)
		dp[size[i]][i]=a[i];
	for(int i=0;i<=17;i++)
		FWT(dp[i],M,1,OR);
	for(int i=0;i<=17;i++)
		for(int j=0;j<=i;j++)
			for(int k=0;k<N;++k)
				dp2[i][k]=(dp2[i][k]+1ll*dp[j][k]*dp[i-j][k]%Mod)%Mod;
	for(int i=0;i<=17;++i)
		FWT(dp2[i],M,0,OR);
	for(int i=0;i<N;++i)
		f[i]=(f[i]+dp2[size[i]][i])%Mod;
}

int main()
{
	fib[1]=fib[2]=1;
	for(int i=3;i<=M;i++)
		fib[i]=(fib[i-1]+fib[i-2])%Mod;
	int n,x;scanf("%d",&n);
	for(int i=0;i<n;i++)
	{
		scanf("%d",&x);
		a[x]++;h[x]++;g[x]++;
	}
	FST();FWT(h,M,1,XOR);
	for(int i=0;i<M;i++)
		h[i]=1ll*h[i]*h[i]%Mod;
	FWT(h,M,0,XOR);
	for(int i=0;i<M;i++)
	{
		f[i]=1ll*fib[i]*f[i]%Mod;
		g[i]=1ll*fib[i]*g[i]%Mod;
		h[i]=1ll*fib[i]*h[i]%Mod;
	}
	FWT(f,M,1,AND);FWT(g,M,1,AND);FWT(h,M,1,AND);
	for(int i=0;i<M;i++)
		h[i]=1ll*f[i]*g[i]%Mod*h[i]%Mod;
	FWT(h,M,0,AND);
	int ans=0;
	for(int i=0;i<17;i++)
		ans=(ans+h[1<<i])%Mod;
	printf("%d\n",ans);
	return 0;
}
