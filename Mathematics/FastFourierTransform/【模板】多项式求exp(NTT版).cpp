#include<bits/stdc++.h>
#define Mod 998244353
using namespace std;

const int N=800010;
int t[N],s[N],fk[N],d[N];
int r[N],iv[N+10];
int f[N],g[N];

int Pow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=1ll*a*a%Mod)
		if(b&1) ans=1ll*ans*a%Mod;
	return ans;
}

void NTT(int *a,int n,bool IDFT)
{
	for(int i=0;i<n;i++) r[i]=(r[i/2]/2)|((i&1)*(n/2));
	for(int i=0;i<n;i++) if(i<r[i]) swap(a[i],a[r[i]]);
	for(int i=1;i<n;i<<=1)
	{
		int p=(i<<1);
		int wn=Pow(3,(Mod-1)/p);
		if(IDFT) wn=Pow(wn,Mod-2);
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
	int inv=IDFT?Pow(n,Mod-2):0;
	if(IDFT) for(int i=0;i<n;i++) a[i]=1ll*a[i]*inv%Mod;
}

void Inv(int n,int *a,int *b)
{
	if(n==1){b[0]=Pow(a[0],Mod-2);return;}
	Inv(n>>1,a,b);n<<=1;
	for(int i=0;i<n/2;i++) t[i]=a[i],t[i+n/2]=0;
	NTT(t,n,0);NTT(b,n,0);
	for(int i=0;i<n;i++)
		b[i]=(2ll-1ll*t[i]*b[i]%Mod+Mod)*b[i]%Mod;
	NTT(b,n,1);
	for(int i=n/2;i<n;i++) b[i]=0;
}

void Derivate(int n,int *a)
{
	a[n]=0;
	for(int i=0;i<n;i++)
		a[i]=1ll*a[i+1]*(i+1)%Mod;
}

void Integral(int n,int *a)
{
	for(int i=n-1;i>=1;i--)
		a[i]=1ll*a[i-1]*iv[i]%Mod;
	a[0]=0;
}

void Ln(int n,int *a)
{
	for(int i=0;i<n;i++) fk[i]=a[i],fk[n+i]=0;
	int m;for(m=1;m<(n<<1);m<<=1);
	memset(s,0,sizeof(s));
	Derivate(n,fk);Inv(m/2,a,s);
	NTT(fk,m,0);NTT(s,m,0);
	for(int i=0;i<m;i++)
		a[i]=1ll*fk[i]*s[i]%Mod;
	NTT(a,m,1);
	Integral(n,a);
	for(int i=n;i<m;i++) a[i]=0;
}

void Exp(int n,int *a,int *b)
{
	if(n==1){b[0]=1;return;}
	Exp(n>>1,a,b);
	for(int i=0;i<n;i++) d[i]=b[i],d[n+i]=0;
	Ln(n,d);n<<=1;
	for(int i=0;i<n/2;i++) d[i]=(a[i]-d[i]+Mod)%Mod;
	d[0]=(d[0]+1)%Mod;
	NTT(b,n,0);NTT(d,n,0);
	for(int i=0;i<n;i++)
		b[i]=1ll*b[i]*d[i]%Mod;
	NTT(b,n,1);
	for(int i=n/2;i<n;i++) b[i]=0;
}

int main()
{
	iv[1]=1;
	for(int i=2;i<=N;i++)
		iv[i]=(-1ll*(Mod/i)*iv[Mod%i]%Mod+Mod)%Mod;
	int n,m;
	scanf("%d",&n);
	for(int i=0;i<n;i++) scanf("%d",f+i);
	for(m=1;m<n;m<<=1);
	Exp(m,f,g);
	for(int i=0;i<n;i++) printf("%d ",g[i]);
	return 0;
}
