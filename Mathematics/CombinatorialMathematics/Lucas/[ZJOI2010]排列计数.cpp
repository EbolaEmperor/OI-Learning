#include<bits/stdc++.h>
using namespace std;

const int N=1000010;
int n,ha;
int fac[N],ifac[N];
int f[N],size[N];

int Pow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=1ll*a*a%ha)
		if(b&1) ans=1ll*ans*a%ha;
	return ans;
}

void Init(int n)
{
	fac[0]=1;
	for(int i=1;i<=n;i++)
		fac[i]=1ll*fac[i-1]*i%ha;
	ifac[n]=Pow(fac[n],ha-2);
	for(int i=n-1;i>=0;i--)
		ifac[i]=1ll*ifac[i+1]*(i+1)%ha;
}

int C(int n,int m){return 1ll*fac[n]*ifac[m]%ha*ifac[n-m]%ha;}

int Lucas(int n,int m)
{
	if(n<ha&&m<ha) return C(n,m);
	else return 1ll*C(n%ha,m%ha)*Lucas(n/ha,m/ha)%ha;
}

int main()
{
	scanf("%d%d",&n,&ha);
	Init(min(ha-1,N-1));
	for(int i=n;i>=1;i--)
	{
		int lc=i<<1,rc=lc|1;
		if(lc>n) f[i]=size[i]=1;
		else if(rc>n) f[i]=f[lc],size[i]=size[lc]+1;
		else
		{
			size[i]=size[lc]+size[rc]+1;
			f[i]=1ll*Lucas(size[i]-1,size[lc])*f[lc]%ha*f[rc]%ha;
		}
	}
	printf("%d\n",f[1]);
	return 0;
}
