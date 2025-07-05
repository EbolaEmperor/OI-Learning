#include<iostream>
#include<cstdio>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;

const double eps=1e-6;
const double PI=acos(-1);
struct Point
{
	double x,y;
	Point(double _x=0,double _y=0):x(_x),y(_y){}
};
typedef Point Vector;
struct Circle
{
	double r;
	Point o;
	Point GetPoint(double alpha){return Point(o.x+r*cos(alpha),o.y+r*sin(alpha));}
} c[110];
vector<double> a[110];

int dcmp(double x)
{
	if(fabs(x)<=eps) return 0;
	else if(x<0) return -1;
	else return 1;
}
bool operator == (const Point &a,const Point &b){return dcmp(b.x-a.x)==0&&dcmp(b.y-a.y)==0;}
double Dot(Vector a,Vector b){return a.x*b.x+a.y*b.y;}
double Length(Vector a){return sqrt(Dot(a,a));}
Vector operator - (const Vector &a,const Vector &b){return Vector(a.x-b.x,a.y-b.y);}
double Angle(Vector a){return atan2(a.y,a.x);}
bool InCircle(Point A,Circle c){return dcmp(Length(c.o-A)-c.r)<=0;}
void GetCircleCircleIntersection(Circle a,Circle b,vector<Point> &p)
{
	if(a.o==b.o) return;
	double dist=Length(b.o-a.o);
	if(dcmp(b.r+a.r-dist)<0) return;
	if(dcmp(fabs(b.r-a.r)-dist)>0) return;
	double beta=Angle(b.o-a.o);
	if(dcmp(b.r+a.r-dist)==0||dcmp(fabs(b.r-a.r)-dist)==0)
		p.push_back(a.GetPoint(beta));
	else
	{
		double alpha=acos((a.r*a.r+dist*dist-b.r*b.r)/(2*a.r*dist));
		p.push_back(a.GetPoint(beta+alpha));
		p.push_back(a.GetPoint(beta-alpha));
	}
}

int main()
{
	int t,n;
	for(cin>>t;t;t--)
	{
		scanf("%d",&n);
		for(int i=0;i<n;i++) scanf("%lf%lf%lf",&c[i].r,&c[i].o.x,&c[i].o.y);
		for(int i=0;i<n;i++)
		{
			vector<Point> p;
			for(int j=0;j<n;j++)
				GetCircleCircleIntersection(c[i],c[j],p);
			a[i].clear();
			a[i].push_back(0);
			for(int j=0;j<p.size();j++)
				a[i].push_back(Angle(p[j]-c[i].o));
			sort(a[i].begin(),a[i].end());
		}
		double ans=0;
		for(int i=0;i<n;i++)
		{
			double alpha=0;
			for(int j=0;j<a[i].size();j++)
			{
				bool flag=true;
				if(j!=0)
				{
					Point A=c[i].GetPoint((a[i][j]+a[i][j-1])/2);
					for(int k=i+1;k<n;k++)
						if(InCircle(A,c[k])) flag=false;
					if(flag) alpha+=fabs(a[i][j]-a[i][j-1]);
				}
				else
				{
					Point A=c[i].GetPoint((a[i][j]+a[i][a[i].size()-1]+2*PI)/2);
					for(int k=i+1;k<n;k++)
						if(InCircle(A,c[k])) flag=false;
					if(flag) alpha+=fabs(a[i][j]-a[i][a[i].size()-1]+2*PI);
				}
			}
			ans+=c[i].r*alpha;
		}
		printf("%.3lf\n",ans);
	}
	return 0;
}
