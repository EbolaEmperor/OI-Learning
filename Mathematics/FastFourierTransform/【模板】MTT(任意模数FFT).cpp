//Mathew Theoretic Transform
#include<bits/stdc++.h>
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
const int N=400010,M=32768;
const double pi=acos(-1);
Comp a1[N],b1[N],c1[N],d1[N];
Comp a2[N],b2[N],c2[N],d2[N];
int n,m,len=1,p,l=0,r[N];
int A[N],B[N];
LL ans[N];

void FFT(Comp *a,int v)
{
	for(int i=0;i<len;i++) if(i<r[i]) swap(a[i],a[r[i]]);
	for(int i=1;i<len;i<<=1)
	{
		Comp wn=Comp(cos(pi/i),v*sin(pi/i));
		int p=(i<<1);
		for(int j=0;j<len;j+=p)
		{
			Comp w=Comp(1,0);
			for(int k=0;k<i;k++)
			{
				Comp x=a[j+k],y=a[i+j+k];
				a[j+k]=x+w*y;
				a[i+j+k]=x-w*y;
				w=w*wn; 
			} 
		}
	}
}

void MTT()
{
	for(int i=0;i<=n+m;i++)
	{
		a1[i]=Comp(A[i]/M,0);
		b1[i]=Comp(A[i]%M,0);
		c1[i]=Comp(B[i]/M,0);
		d1[i]=Comp(B[i]%M,0);
	}
	FFT(a1,1);FFT(b1,1);FFT(c1,1);FFT(d1,1);
	for(int i=0;i<len;i++)
	{
		a2[i]=a1[i]*c1[i];
		b2[i]=a1[i]*d1[i];
		c2[i]=b1[i]*c1[i];
		d2[i]=b1[i]*d1[i];
	}
	FFT(a2,-1);FFT(b2,-1);FFT(c2,-1);FFT(d2,-1);
	for(int i=0;i<len;i++)
	{
		ans[i]=(LL)round(a2[i].r/len)%p*M%p*M%p;
		ans[i]+=(LL)round(b2[i].r/len)%p*M%p;
		ans[i]+=(LL)round(c2[i].r/len)%p*M%p;
		ans[i]+=(LL)round(d2[i].r/len)%p;
		ans[i]%=p;
	}
}

int main()
{
	scanf("%d%d%d",&n,&m,&p);
	for(int i=0;i<=n;i++) scanf("%d",A+i);
	for(int i=0;i<=m;i++) scanf("%d",B+i);
	for(len=1;len<=n+m;len<<=1) l++;
	for(int i=0;i<len;i++) r[i]=(r[i/2]/2)|((i&1)<<(l-1));
	MTT();
	for(int i=0;i<=n+m;i++) printf("%lld ",ans[i]);
	return 0;
}
