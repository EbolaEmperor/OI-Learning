#include<bits/stdc++.h>
#define ha 999911659
using namespace std;

int n,g;
int p[4]={2,3,4679,35617},b[4];
int fac[4][36000],ifac[4][36000];

int Pow(int a,int b,int p)
{
	if(!a) return 0;
	int ans=1;
	for(;b;b>>=1,a=1ll*a*a%p)
		if(b&1) ans=1ll*ans*a%p;
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
int Lucas(int n,int m,int r)
{
	if(n<p[r]&&m<p[r]) return C(n,m,r);
	return 1ll*C(n%p[r],m%p[r],r)*Lucas(n/p[r],m/p[r],r)%p[r];
}

void gao(int r)
{
	for(int d=1;d*d<=n;d++)
	{
		if(n%d) continue;
		b[r]=(b[r]+Lucas(n,d,r))%p[r];
		if(d*d==n) continue;
		b[r]=(b[r]+Lucas(n,n/d,r))%p[r];
	}
}

void ExGcd(int a,int b,int &x,int &y)
{
	if(b==0){x=1;y=0;return;}
	ExGcd(b,a%b,x,y);
	int t=x;x=y;y=t-(a/b)*y;
}

int CRT()
{
	int N=ha-1,ans=0;
	for(int i=0;i<4;i++)
	{
		int M=N/p[i],x,y;
		ExGcd(M,p[i],x,y);
		x=1ll*x*b[i]%N;
		ans=(ans+1ll*x*M)%N;
	}
	return (ans+N)%N;
}

int main()
{
	for(int i=0;i<4;i++)
		Init(fac[i],ifac[i],p[i]);
	cin>>n>>g;
	if(g==ha){puts("0");return 0;}
	for(int i=0;i<4;i++) gao(i);
	printf("%d\n",Pow(g,CRT(),ha));
	return 0;
}
