#include<bits/stdc++.h>
#define Mod 1000000007
#define double long double
using namespace std;

typedef long long LL;
struct Comp
{
	double r,i;
	Comp(double x=0,double y=0):r(x),i(y){}
	friend Comp operator + (Comp a,Comp b){return Comp(a.r+b.r,a.i+b.i);}
	friend Comp operator - (Comp a,Comp b){return Comp(a.r-b.r,a.i-b.i);}
	friend Comp operator * (Comp a,Comp b){return Comp(a.r*b.r-a.i*b.i,a.r*b.i+a.i*b.r);}
};
const int M=sqrt(Mod);
const int N=400010;
const double pi=acos(-1);
Comp A[N],B[N],C[N],D[N],E[N],F[N],G[N];
int a[N],b[N],c[N],d[N],r[N];

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

void FFT(Comp *a,int n,int v)
{
	for(int i=0;i<n;i++) if(i<r[i]) swap(a[i],a[r[i]]);
	for(int i=1;i<n;i<<=1)
	{
		int p=(i<<1);
		Comp wn=Comp(cos(pi/i),v*sin(pi/i));
		for(int j=0;j<n;j+=p)
		{
			Comp w=Comp(1,0);
			for(int k=0;k<i;k++)
			{
				Comp x=a[j+k],y=w*a[i+j+k];
				a[j+k]=x+y;
				a[i+j+k]=x-y;
				w=w*wn;
			}
		}
	}
}

void MTT(int *a,int *b,int n,int *res)
{
	int len,l=0;
	for(len=1;len<(n<<1);len<<=1) l++;
	for(int i=0;i<len;i++) r[i]=(r[i/2]/2)|((i&1)<<(l-1));
	for(int i=0;i<n;i++)
	{
		A[i]=Comp(a[i]/M,0);
		B[i]=Comp(a[i]%M,0);
		C[i]=Comp(b[i]/M,0);
		D[i]=Comp(b[i]%M,0);
	}
	for(int i=n;i<len;i++) A[i]=B[i]=C[i]=D[i]=Comp(0,0);
	FFT(A,len,1);FFT(B,len,1);FFT(C,len,1);FFT(D,len,1);
	for(int i=0;i<len;i++)
	{
		E[i]=A[i]*C[i];
		F[i]=A[i]*D[i]+B[i]*C[i];
		G[i]=B[i]*D[i];
	}
	FFT(E,len,-1);FFT(F,len,-1);FFT(G,len,-1);
	for(int i=0;i<len;i++)
	{
		res[i]=(LL)round(E[i].r/len)%Mod*M%Mod*M%Mod;
		res[i]=(res[i]+(LL)round(F[i].r/len)%Mod*M%Mod)%Mod;
		res[i]=(res[i]+(LL)round(G[i].r/len)%Mod)%Mod;
	}
}

void Inv(int deg,int *a,int *b)
{
	if(deg==1){b[0]=Pow(a[0],Mod-2);return;}
	Inv((deg+1)>>1,a,b);
	MTT(a,b,deg,c);
	MTT(c,b,deg,d);
	for(int i=0;i<deg;i++)
	{
		b[i]=(b[i]+b[i])%Mod;
		b[i]=(b[i]-d[i])%Mod;
		if(b[i]<0) b[i]+=Mod;
	}
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
