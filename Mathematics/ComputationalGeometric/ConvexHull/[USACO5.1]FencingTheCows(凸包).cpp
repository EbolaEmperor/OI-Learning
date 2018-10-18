#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;

const double eps=1e-6;
struct Point
{
	double x,y;
	Point(double x=0,double y=0):x(x),y(y){}
} p[10010],ch[10010];

Point operator - (Point a,Point b){return Point(a.x-b.x,a.y-b.y);}
bool operator < (const Point &a,const Point &b){return a.x<b.x||(a.x==b.x&&a.y<b.y);}
double cross(Point a,Point b){return a.x*b.y-a.y*b.x;}
void read(Point &x){scanf("%lf%lf",&x.x,&x.y);}

int ConvexHull(Point a[],int n,Point b[])
{
	sort(a,a+n);
	int m=0;
	for(int i=0;i<n;i++)
	{
		while(m>1&&cross(b[m-1]-b[m-2],p[i]-b[m-2])<=eps) m--;
		b[m++]=p[i];
	}
	int k=m;
	for(int i=n-2;i>=0;i--)
	{
		while(m>k&&cross(b[m-1]-b[m-2],p[i]-b[m-2])<=eps) m--;
		b[m++]=p[i];
	}
	return m;
}

int main()
{
	int n;
	double ans=0.0;
	cin>>n;
	for(int i=0;i<n;i++) read(p[i]);
	int m=ConvexHull(p,n,ch);
	for(int i=1;i<m;i++) ans+=sqrt((ch[i].x-ch[i-1].x)*(ch[i].x-ch[i-1].x)+(ch[i].y-ch[i-1].y)*(ch[i].y-ch[i-1].y));
	printf("%.2lf\n",ans);
	return 0;
}
