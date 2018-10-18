#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;

typedef long long LL;
typedef pair<LL,LL> pLL;
LL n,m,T,P;
int p[5]={3,5,6793,10007,1000003},N=1019663265;
int fac[5][1000010],ifac[5][1000010];
pLL bad[210];
int f[210];
LL b[5];

int Pow(int a,int b,int p)
{
	int ans=1;
	for(;b;b>>=1,a=1ll*a*a%p)
		if(b&1) ans=1ll*a*ans%p;
	return ans;
}

void Init(int *fac,int *ifac,int p)
{
	fac[0]=1;
	for(int i=1;i<p;i++)
		fac[i]=1ll*fac[i-1]*i%p;
	ifac[p-1]=Pow(fac[p-1],p-2,p);
	for(int i=p-2;i>=0;i--)
		ifac[i]=1ll*ifac[i+1]*(i+1)%p;
}

int C(int n,int m,int r){return 1ll*fac[r][n]*ifac[r][m]*ifac[r][n-m]%p[r];}
int Lucas(LL n,LL m,int r)
{
	if(n<m) return 0;
	if(n<p[r]&&m<p[r]) return C(n,m,r);
	return 1ll*C(n%p[r],m%p[r],r)*Lucas(n/p[r],m/p[r],r)%p[r];
}

void ExGcd(LL a,LL b,LL &x,LL &y)
{
	if(b==0){x=1;y=0;return;}
	ExGcd(b,a%b,x,y);
	LL t=x;x=y;y=t-(a/b)*y;
}

int CRT(LL x,LL y)
{
	for(int i=0;i<4;i++) b[i]=Lucas(x+y,x,i);
	LL ans=0;
	for(int i=0;i<4;i++)
	{
		LL M=N/p[i],k1,k2;
		ExGcd(M,p[i],k1,k2);
		k1=1ll*k1*b[i]%N;
		ans=(ans+1ll*k1*M)%N;
	}
	return (ans+N)%N;
}

int main()
{
	for(int i=0;i<5;i++)
		Init(fac[i],ifac[i],p[i]);
	scanf("%lld%lld%lld%lld",&n,&m,&T,&P);
	for(int i=1;i<=T;i++)
		scanf("%lld%lld",&bad[i].fi,&bad[i].se);
	bad[++T]=pLL(n,m);
	sort(bad+1,bad+1+T);
	for(int i=1;i<=T;i++)
	{
		if(P==p[4]) f[i]=Lucas(bad[i].fi+bad[i].se,bad[i].se,4);
		else f[i]=CRT(bad[i].fi,bad[i].se);
		for(int j=1;j<i;j++)
			if(P==p[4]) f[i]=(f[i]-1ll*f[j]*Lucas(bad[i].fi+bad[i].se-bad[j].fi-bad[j].se,bad[i].fi-bad[j].fi,4)%p[4]+p[4])%p[4];
			else f[i]=(f[i]-1ll*f[j]*CRT(bad[i].fi-bad[j].fi,bad[i].se-bad[j].se)%N+N)%N;
	}
	printf("%d\n",f[T]);
	return 0;
}
