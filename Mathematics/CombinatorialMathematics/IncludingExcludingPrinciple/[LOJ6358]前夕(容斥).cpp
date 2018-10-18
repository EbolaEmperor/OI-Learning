#include<bits/stdc++.h>
#define ha 998244353
using namespace std;

const int N=10000010;
int fac[N],ifac[N],dafa[N],pw[N];

inline void add(int &x,const int &y){x=x+y>=ha?x+y-ha:x+y;}
inline void dev(int &x,const int &y){x=x-y<0?x-y+ha:x-y;}

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
	pw[0]=2;
	for(int i=1;i<=n;i++)
		pw[i]=1ll*pw[i-1]*pw[i-1]%ha;
	static int tmp[5]={1,0,0,0,0};
	dafa[0]=1;
	for(int i=1;i<=n;i++)
	{
		for(int j=3;j>=0;j--) dev(tmp[j+1],tmp[j]);
		add(tmp[0],tmp[4]);tmp[4]=0;
		dafa[i]=tmp[0];
	}
}

inline int C(const int &n,const int &m){return 1ll*fac[n]*ifac[m]%ha*ifac[n-m]%ha;}

int main()
{
	int n,res=0;
	scanf("%d",&n);
	Init(n);
	for(int k=0;k<=n;k++)
		res=(res+(k&1?-1ll:1ll)*C(n,k)*(pw[n-k]-1)%ha*dafa[k])%ha;
	printf("%d\n",(res+1+ha)%ha);
	return 0;
}
