#include<bits/stdc++.h>
using namespace std;

const double eps=1e-13;
struct CRL{double x,y,r;} c[1010],ct[1010];
int n=0;double xl[1010],xr[1010];
bool del[1010];
struct Line
{
	double y1,y2;
	Line(double a=0,double b=0):
		y1(a),y2(b){}
} l[1010];

bool cmp (const CRL &a,const CRL &b){return a.x<b.x;}
bool operator < (const CRL &a,const CRL &b){return a.r<b.r;}
bool operator < (const Line &a,const Line &b){return a.y1<b.y1;}
double dis(CRL a,CRL b){return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));}

double F(double x)
{
	int tot=0;
	for(int i=1;i<=n;i++)
	{
		if(xl[i]>x||xr[i]<x) continue;
		double xx=c[i].x-x;
		double len=sqrt(c[i].r*c[i].r-xx*xx);
		l[++tot]=Line(c[i].y-len,c[i].y+len);
	}
	sort(l+1,l+1+tot);
	double yy=0;int j;
	for(int i=1;i<=tot;i=j)
	{
		double y2=l[i].y2;
		for(j=i+1;j<=tot;j++)
		{
			if(l[j].y1>y2) break;
			if(y2<l[j].y2) y2=l[j].y2;
		}
		yy+=y2-l[i].y1;
	}
	return yy;
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
	if(fabs(L+R-A)<=15*eps) return L+R+(L+R-A)/15.0;
	return asr(a,mid,L)+asr(mid,b,R);
}
double asr(double a,double b){return asr(a,b,simpson(a,b));}

int main()
{
	int m;cin>>m;
	for(int i=1;i<=m;i++)
		scanf("%lf%lf%lf",&c[i].x,&c[i].y,&c[i].r);
	sort(c+1,c+1+m);
	for(int i=1;i<=m;i++)
		for(int j=i+1;j<=m;j++)
			if(dis(c[i],c[j])<=c[j].r-c[i].r)
				{del[i]=1;break;}
	for(int i=1;i<=m;i++)
		if(!del[i]) ct[++n]=c[i];
	for(int i=1;i<=n;i++) c[i]=ct[i];
	sort(c+1,c+1+n,cmp);
	for(int i=1;i<=n;i++) xl[i]=c[i].x-c[i].r,xr[i]=c[i].x+c[i].r;
	double ans=asr(-2000,c[1].x);
	for(int i=1;i<n;i++) ans+=asr(c[i].x,c[i+1].x);
	ans+=asr(c[n].x,2000);
	printf("%.3lf\n",ans);
	return 0;
}
