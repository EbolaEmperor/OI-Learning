#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

const double PI=acos(-1);
struct Point
{
	double x,y;
	Point(double _x=0,double _y=0):x(_x),y(_y){}
} p[600];
typedef Point Vector;

Vector operator - (const Vector &a,const Vector &b){return Vector(a.x-b.x,a.y-b.y);}
double Cross(Vector a,Vector b){return a.x*b.y-a.y*b.x;}
double torad(double alpha){return alpha/180*PI;}

int main()
{
	int n,r;
	double alpha;
	while(scanf("%d%d",&n,&r)==2&&n&&r)
	{
		for(int i=0;i<n;i++)
		{
			scanf("%lf",&alpha);
			alpha=torad(alpha);
			p[i].x=r*cos(alpha);
			p[i].y=r*sin(alpha);
		}
		double ans=0;
		for(int i=0;i<n-2;i++)
			for(int j=i+1;j<n-1;j++)
				for(int k=j+1;k<n;k++)
					ans+=fabs(Cross(p[j]-p[i],p[k]-p[i])/2);
		printf("%.0lf\n",ans);
	}
	return 0;
}
