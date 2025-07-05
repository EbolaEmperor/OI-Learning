#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

struct Point
{
	long long x,y;
	Point(long long _x=0,long long _y=0):x(_x),y(_y){}
} p[1010];

void read(int &x)
{
	x=0;
	char c=getchar();
	int fg=1;
	while((c<'0'||c>'9')&&c!='-') c=getchar();
	if(c=='-') fg=-1,c=getchar();
	while(c>='0'&&c<='9') x=x*10+(int)(c-'0'),c=getchar();
	x*=fg;
}
void read(long long &x)
{
	x=0;
	char c=getchar();
	long long fg=1;
	while((c<'0'||c>'9')&&c!='-') c=getchar();
	if(c=='-') fg=-1,c=getchar();
	while(c>='0'&&c<='9') x=x*10+(int)(c-'0'),c=getchar();
	x*=fg;
}
void read(Point &a){read(a.x);read(a.y);}

long long dist2(Point a,Point b){return (b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y);}
double dist(Point a,Point b){return sqrt(dist2(a,b));}
Point operator - (const Point &a,const Point &b){return Point(a.x-b.x,a.y-b.y);}
long long cross(Point a,Point b){return a.x*b.y-a.y*b.x;}

int main()
{
	int n;read(n);
	double ans=1e9;
	for(int i=1;i<=n;i++) read(p[i]);
	p[0]=p[n];p[n+1]=p[1];
	for(int i=1;i<=n;i++)
	{
		double l=dist(p[i-1],p[i+1]);
		double s=(double)cross(p[i-1]-p[i],p[i+1]-p[i]);
		double d=s/l/2;
		if(d<ans) ans=d;
	}
	if(ans<0.01) printf("%lf\n",-ans);else printf("%lf\n",ans);
	return 0;
}
