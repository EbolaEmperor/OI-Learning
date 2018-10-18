#include<bits/stdc++.h>
#define Mod 998244353
#define inv2 499122177
using namespace std;

const int g=3;
const int N=400010;
int a[N],b[N],c[N],r[N];
int t[N],s[N];

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

void NTT(int *a,int n,bool INTT)
{
	int inv=INTT?Pow(n,Mod-2):0;
	for(int i=0;i<n;i++) r[i]=(r[i/2]/2)|((i&1)*(n/2));
	for(int i=0;i<n;i++) if(i<r[i]) swap(a[i],a[r[i]]);
	for(int i=1;i<n;i<<=1)
	{
		int p=(i<<1);
		int wn=Pow(g,(Mod-1)/p);
		if(INTT) wn=Pow(wn,Mod-2);
		for(int j=0;j<n;j+=p)
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
	if(INTT) for(int i=0;i<n;i++) a[i]=1ll*a[i]*inv%Mod;
}

void Inv(int deg,int *a,int *b)
{
	if(deg==1){b[0]=Pow(a[0],Mod-2);return;}
	Inv(deg>>1,a,b);deg<<=1;
	for(int i=0;i<deg/2;i++) s[i]=a[i],s[i+deg/2]=0;
	NTT(s,deg,0);NTT(b,deg,0);
	for(int i=0;i<deg;i++)
		b[i]=1ll*(2ll-1ll*s[i]*b[i]%Mod+Mod)*b[i]%Mod;
	NTT(b,deg,1);
	for(int i=deg/2;i<deg;i++) b[i]=0;
}

void Sqrt(int deg,int *a,int *b)
{
	if(deg==1){b[0]=1;return;}
	Sqrt(deg>>1,a,b);deg<<=1;
	for(int i=0;i<deg;i++) t[i]=0;
	Inv(deg>>1,b,t);
	for(int i=0;i<deg/2;i++) s[i]=a[i],s[i+deg/2]=0;
	NTT(s,deg,0);NTT(t,deg,0);NTT(b,deg,0);
	for(int i=0;i<deg;i++)
		b[i]=1ll*(s[i]+1ll*b[i]*b[i]%Mod)%Mod*t[i]%Mod*inv2%Mod;
	NTT(b,deg,1);
	for(int i=deg/2;i<deg;i++) b[i]=0;
}

int main()
{
	int n,m=1;
	scanf("%d",&n);
	for(int i=0;i<n;i++) scanf("%d",a+i);
	while(m<n) m<<=1;
	Sqrt(m,a,b);
	for(int i=0;i<n;i++) printf("%d ",b[i]);
	return 0;
}
