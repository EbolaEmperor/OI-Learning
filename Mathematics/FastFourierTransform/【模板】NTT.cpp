#include<bits/stdc++.h>
#define Mod 998244353
using namespace std;

const int g=3;
const int N=400010;
int a[N],b[N],r[N];
int l=0,n,m,len,inv;

int Pow(int a,int b)
{
	int ans=1;
	while(b)
	{
		if(b&1) ans=1ll*ans*a%Mod;
		a=1ll*a*a%Mod;
		b>>=1;
	}
	return ans;
}

void NTT(int *a,bool INTT)
{
	for(int i=0;i<len;i++) if(i<r[i]) swap(a[i],a[r[i]]);
	for(int i=1;i<len;i<<=1)
	{
		int p=(i<<1);
		int wn=Pow(g,(Mod-1)/p);
		if(INTT) wn=Pow(wn,Mod-2);
		for(int j=0;j<len;j+=p)
		{
			int w=1;
			for(int k=0;k<i;k++)
			{
				int x=a[j+k],y=1ll*w*a[i+j+k]%Mod;
				a[j+k]=(x+y)%Mod;
				a[i+j+k]=(x-y+Mod)%Mod;
				w=1ll*w*wn%Mod;
			}
		}
	}
	if(INTT) for(int i=0;i<len;i++) a[i]=1ll*a[i]*inv%Mod;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=0;i<=n;i++) scanf("%d",a+i);
	for(int i=0;i<=m;i++) scanf("%d",b+i);
	for(len=1;len<=n+m;len<<=1) l++;
	inv=Pow(len,Mod-2);
	for(int i=0;i<len;i++) r[i]=(r[i/2]/2)|((i&1)<<(l-1));
	NTT(a,0);NTT(b,0);
	for(int i=0;i<len;i++) a[i]=1ll*a[i]*b[i]%Mod;
	NTT(a,1);
	for(int i=0;i<=n+m;i++) printf("%d ",a[i]);
	return 0;
}
