#include<iostream>
#include<cstdio>
#include<cmath>
#include<complex>
#include<cstdlib>
using namespace std;

const double pi=acos(-1);
struct Comp
{
	double r,i;
	Comp(double x=0,double y=0):r(x),i(y){}
	friend Comp operator + (Comp a,Comp b){return Comp(a.r+b.r,a.i+b.i);}
	friend Comp operator - (Comp a,Comp b){return Comp(a.r-b.r,a.i-b.i);}
	friend Comp operator * (Comp a,Comp b){return Comp(a.r*b.r-a.i*b.i,a.r*b.i+a.i*b.r);}
};
int n,m,l=0,r[3000000];
Comp a[3000000],b[3000000];

void FFT(Comp *a,int v)
{
	for(int i=0;i<n;i++) if(i<r[i]) swap(a[i],a[r[i]]);
	for(int i=1;i<n;i*=2)
	{
		Comp wn=Comp(cos(pi/i),v*sin(pi/i));
		int p=i*2;
		for(int j=0;j<n;j+=p)
		{
			Comp w=Comp(1,0);
			for(int k=0;k<i;k++)
			{
				Comp x=a[j+k],y=w*a[i+j+k];
				a[j+k]=x+y;a[i+j+k]=x-y;
				w=w*wn;
			}
		}
	}
}

int main()
{
	cin>>n>>m;
	for(int i=0;i<=n;i++) scanf("%lf",&a[i].r);
	for(int i=0;i<=m;i++) scanf("%lf",&b[i].r);
	m+=n;for(n=1;n<=m;n*=2) l++;
	for(int i=0;i<n;i++) r[i]=(r[i/2]/2)|((i&1)<<(l-1));
	FFT(a,1);FFT(b,1);
	for(int i=0;i<=n;i++) a[i]=a[i]*b[i];
	FFT(a,-1);
	for(int i=0;i<=m;i++) printf("%d ",(int)round(a[i].r/n));
	return 0;
}
