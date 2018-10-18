#include<bits/stdc++.h>
#define Mod 1004535809
using namespace std;

const int N=40010;
int a[N],c[N],ans[N],r[N],l=0,len,inv;
int q[8010],cnt=0,lg[8010],m;

int Pow(int a,int b,int p)
{
	int ans=1;
	for(;b;b>>=1,a=1ll*a*a%p)
		if(b&1) ans=1ll*ans*a%p;
	return ans;
}

void NTT(int *a,bool INTT)
{
	for(int i=0;i<len;i++) if(i<r[i]) swap(a[i],a[r[i]]);
	for(int i=1;i<len;i<<=1)
	{
		int p=(i<<1);
		int wn=Pow(3,(Mod-1)/p,Mod);
		if(INTT) wn=Pow(wn,Mod-2,Mod);
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

int Root(int s)
{
	for(int i=2;i<=s-2;i++)
		if((s-1)%i==0) q[++cnt]=i;
	for(int i=2;;i++)
	{
		bool flag=1;
		for(int j=1;j<=cnt&&flag;j++)
			if(Pow(i,q[j],s)==1) flag=0;
		if(flag) return i;
	}
	return -1;
}

void Mult(int *a,int *b)
{
	for(int i=0;i<len;i++) c[i]=b[i];
	NTT(a,0);NTT(c,0);
	for(int i=0;i<len;i++)
		a[i]=1ll*a[i]*c[i]%Mod;
	NTT(a,1);
	for(int i=len-1;i>=m-1;i--)
		a[i-m+1]=(a[i-m+1]+a[i])%Mod,a[i]=0;
}

int main()
{
	int n,x,S,k;
	scanf("%d%d%d%d",&n,&m,&x,&S);
	for(len=1;len<(m<<1);len<<=1) l++;
	for(int i=0;i<len;i++) r[i]=(r[i/2]/2)|((i&1)<<(l-1));
	inv=Pow(len,Mod-2,Mod);
	int g=Root(m),pw=1;
	for(int i=0;i<=m-2;i++)
		lg[pw]=i,pw=pw*g%m;
	for(int i=0;i<S;i++)
	{
		scanf("%d",&k);
		if(k) a[lg[k]]++;
	}
	int b=n;ans[0]=1;
	while(b)
	{
		if(b&1) Mult(ans,a);
		Mult(a,a);
		b>>=1;
	}
	printf("%d\n",ans[lg[x]]);
	return 0;
}
