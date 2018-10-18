#include<bits/stdc++.h>
#define vec vector<Comp>
#define pb push_back
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

vec A,B,C;

vec FFT(vec a,int v)
{
	int n=a.size();
	if(n==1) return a;
	vec a1,a2;
	for(int i=0;i<n;i++)
		if(i&1) a2.pb(a[i]);
		else a1.pb(a[i]);
	a1=FFT(a1,v);a2=FFT(a2,v);
	Comp wn=Comp(cos(2*pi/n),v*sin(2*pi/n));
	Comp w=Comp(1,0);
	for(int i=0;i<n/2;i++)
	{
		Comp x=a1[i],y=a2[i];
		a[i]=x+w*y;
		a[n/2+i]=x-w*y;
		w=w*wn;
	}
	return a;
}

int main()
{
	int n,m;double x;
	scanf("%d%d%d",&n,&m);
	for(int i=0;i<=n;i++)
	{
		scanf("%lf",&x);
		A.pb(Comp(x,0));
	}
	for(int i=0;i<=m;i++)
	{
		scanf("%lf",&x);
		B.pb(Comp(x,0));
	}
	int now=1;
	while(now<=n+m) now<<=1;
	for(int i=n+1;i<now;i++) A.pb(Comp(0,0));
	for(int i=m+1;i<now;i++) B.pb(Comp(0,0));
	A=FFT(A,1);B=FFT(B,1);
	for(int i=0;i<now;i++) C.pb(A[i]*B[i]);
	C=FFT(C,-1);
	for(int i=0;i<=n+m;i++) printf("%d ",(int)round(C[i].r/now));
	return 0;
}
