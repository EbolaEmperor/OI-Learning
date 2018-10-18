#include<bits/stdc++.h>
#define Mod 998244353
using namespace std;

const int N=400010;
const int g=3;
int r[N];
int a[N],b[N],c[N];

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

void NTT(int *a,int len,bool INTT)
{
	int inv=Pow(len,Mod-2);
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

void Inv(int deg,int *a,int *b)
{
	if(deg==1){b[0]=Pow(a[0],Mod-2);return;}
	Inv((deg+1)>>1,a,b);
	int l=0,n=1;
	while(n<(deg<<1)) n<<=1,l++;
	for(int i=0;i<n;i++) r[i]=(r[i/2]/2)|((i&1)<<(l-1));
	for(int i=0;i<deg;i++) c[i]=a[i];
	for(int i=deg;i<n;i++) c[i]=0;
	NTT(c,n,0);NTT(b,n,0);
	for(int i=0;i<n;i++)
		b[i]=1ll*(2ll-1ll*c[i]*b[i]%Mod+Mod)%Mod*b[i]%Mod;
	NTT(b,n,1);
	for(int i=deg;i<n;i++) b[i]=0;
}

int main()
{
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++) scanf("%d",a+i);
	Inv(n,a,b);
	for(int i=0;i<n;i++) printf("%d ",b[i]);
	return 0;
}
