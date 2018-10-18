#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;

const double eps=1e-6;
const double pi=acos(-1);
struct Point
{
	double x,y;
	Point(double _x=0,double _y=0):x(_x),y(_y){}
} p[3000],ch[3000];
typedef Point Vector;

Vector operator + (const Vector &a,const Vector &b){return Vector(a.x+b.x,a.y+b.y);}
Vector operator - (const Vector &a,const Vector &b){return Vector(a.x-b.x,a.y-b.y);}
double Cross(Vector a,Vector b){return a.x*b.y-a.y*b.x;}
int dcmp(double x)
{
	if(fabs(x)<=eps) return 0;
	else if(x<0) return -1;
	else return 1;
}
bool operator < (const Point &a,const Point &b){return dcmp(a.x-b.x)<0||(dcmp(a.x-b.x)==0&&dcmp(a.y-b.y)<0);}
double torad(double alpha){return alpha/180*pi;}
Vector Rotate(Vector a,double alpha){return Vector(a.x*cos(alpha)-a.y*sin(alpha),a.x*sin(alpha)+a.y*cos(alpha));}

int ConvexHull(Point a[],int n,Point b[])
{
	sort(a,a+n);
	int m=0;
	for(int i=0;i<n;i++)
	{
		while(m>1&&dcmp(Cross(b[m-2]-b[m-1],b[m-2]-a[i]))<=0) m--;
		b[m++]=a[i];
	}
	int k=m;
	for(int i=n-2;i>=0;i--)
	{
		while(m>k&&dcmp(Cross(b[m-2]-b[m-1],b[m-2]-a[i]))<=0) m--;
		b[m++]=a[i];
	}
	return m-1;
}

double PolygonArea(Point a[],int n)
{
	double area=0;
	for(int i=1;i<n-1;i++) area+=Cross(a[i]-a[0],a[i+1]-a[0]);
	return area/2;
}

int main()
{
	Point O;
	int t,n;
	double w,h,alpha;
	cin>>t;
	for(int T=1;T<=t;T++)
	{
		scanf("%d",&n);
		int cnt=0;
		double area1=0;
		for(int i=1;i<=n;i++)
		{
			scanf("%lf%lf%lf%lf%lf",&O.x,&O.y,&w,&h,&alpha);
			alpha=-torad(alpha);
			p[cnt++]=O+Rotate(Vector(-w/2,h/2),alpha);
			p[cnt++]=O+Rotate(Vector(-w/2,-h/2),alpha);
			p[cnt++]=O+Rotate(Vector(w/2,-h/2),alpha);
			p[cnt++]=O+Rotate(Vector(w/2,h/2),alpha);
			area1+=w*h;
		}
		int m=ConvexHull(p,cnt,ch);
		double area2=PolygonArea(ch,m);
		printf("%.1lf %%\n",area1/area2*100);
	}
	return 0;
}
