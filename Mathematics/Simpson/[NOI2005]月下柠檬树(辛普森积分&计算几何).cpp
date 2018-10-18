#include<bits/stdc++.h>
using namespace std;

const double eps=1e-8;
struct Circle{double x,r;} c[510];
struct Trapezoid{double xl,yl,xr,yr;} ta[510];
int n=0,cnt=0;

double F(double x)
{
	int tot=0,j;double res=0;
	for(int i=1;i<=n;i++)
	{
		double tx=c[i].x-x;
		if(tx>c[i].r) continue;
		double len=sqrt(c[i].r*c[i].r-tx*tx);
		res=max(res,2*len);
	}
	for(int i=1;i<=cnt;i++)
	{
		if(ta[i].xl>x||ta[i].xr<x) continue;
		double yy=ta[i].yr-ta[i].yl;
		double xx=ta[i].xr-ta[i].xl;
		double tx=x-ta[i].xl,k=yy/xx;
		double y2=ta[i].yl+k*tx;
		res=max(res,2*y2);
	}
	return res;
}

double simpson(double a,double b)
{
	double mid=(a+b)/2;
	return (F(a)+4*F(mid)+F(b))*(b-a)/6;
}

double asr(double a,double b,double A)
{
	double mid=(a+b)/2;
	double L=simpson(a,mid),R=simpson(mid,b);
	if(fabs(L+R-A)<=15*eps) return L+R-(L+R-A)/15.0;
	return asr(a,mid,L)+asr(mid,b,R);
}
double asr(double a,double b){return asr(a,b,simpson(a,b));}

int main()
{
	double alpha,k;
	scanf("%d%lf",&n,&alpha);
	c[1].x=0;scanf("%lf",&k);
	double tana=tan(alpha);
	for(int i=1;i<=n;i++)
	{
		scanf("%lf",&k);
		c[i+1].x=c[i].x+k/tana;
	}
	double ll=1e10,rr=-1e10;
	for(int i=1;i<=n;i++)
	{
		scanf("%lf",&c[i].r);
		ll=min(ll,c[i].x-c[i].r);
		rr=max(rr,c[i].x+c[i].r);
	}
	rr=max(rr,c[n+1].x);
	double len,d,beta,fg;
	Circle c1,c2;
	for(int i=1;i<=n;i++)
	{
		double len=c[i+1].x-c[i].x;
		if(c[i+1].r>c[i].r) c1=c[i],c2=c[i+1],fg=-1;
		else c1=c[i+1],c2=c[i],fg=1;
		if(len+c1.r<=c2.r) continue;
		cnt++;d=c2.r-c1.r;
		beta=d/len;
		ta[cnt].xl=c[i].x+fg*c[i].r*beta;
		ta[cnt].xr=c[i+1].x+fg*c[i+1].r*beta;
		beta=sin(acos(beta));
		ta[cnt].yl=c[i].r*beta;
		ta[cnt].yr=c[i+1].r*beta;
	}
	printf("%.2lf\n",asr(ll,rr));
	return 0;
}
