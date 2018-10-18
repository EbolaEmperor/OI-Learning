#include<bits/stdc++.h>
#define vec vector<Comp>
#define pb push_back
using namespace std;

struct Comp
{
	double r,i;
	Comp(double x=0,double y=0):r(x),i(y){}
	friend Comp operator + (Comp a,Comp b){return Comp(a.r+b.r,a.i+b.i);}
	friend Comp operator - (Comp a,Comp b){return Comp(a.r-b.r,a.i-b.i);}
	friend Comp operator * (Comp a,Comp b){return Comp(a.r*b.r-a.i*b.i,a.r*b.i+a.i*b.r);}
	friend Comp operator / (Comp a,double x){return Comp(a.r/x,a.i/x);}
};
const Comp e=Comp(1,0);
const Comp e0=Comp(0,0);
const double pi=acos(-1);
vec A,B,C,ans;

vec FFT(vec a,int v)
{
	int n=a.size();
	if(n==1) return a;
	vec a1,a2;
	for(int i=0;i<n;i++)
		if(i&1) a2.pb(a[i]);
		else a1.pb(a[i]);
	a1=FFT(a1,v);a2=FFT(a2,v);
	Comp wn=Comp(cos(2*pi/n),v*sin(2*pi/n)),w=e;
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
	int n,len=1,x;
	scanf("%d",&n);
	while(len<120000) len<<=1;
	for(int i=0;i<len;i++)
		A.pb(e0),B.pb(e0),C.pb(e0);
	for(int i=0;i<n;i++)
	{
		scanf("%d",&x);
		A[x]=e;B[x*2]=e;C[x*3]=e;
	}
	A=FFT(A,1);B=FFT(B,1);C=FFT(C,1);
	for(int i=0;i<len;i++)
		ans.pb(A[i]+(A[i]*A[i]-B[i])/2+(A[i]*A[i]*A[i]-3*A[i]*B[i]+2*C[i])/6);
	ans=FFT(ans,-1);
	for(int i=0;i<len;i++)
	{
		int x=(int)round(ans[i].r/len);
		if(x) printf("%d %d\n",i,x);
	}
	return 0;
}
