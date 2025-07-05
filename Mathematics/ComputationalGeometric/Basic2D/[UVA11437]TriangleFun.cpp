#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

struct Point
{
	double x,y;
	Point(double _x=0,double _y=0):x(_x),y(_y){}
};
typedef Point Vector;

Vector operator + (Vector a,Vector b){return Vector(a.x+b.x,a.y+b.y);}
Vector operator - (Vector a,Vector b){return Vector(a.x-b.x,a.y-b.y);}
Vector operator * (Vector a,double x){return Vector(a.x*x,a.y*x);}
Vector operator / (Vector a,double x){return Vector(a.x/x,a.y/x);}
double Cross(Vector a,Vector b){return a.x*b.y-a.y*b.x;}
Point GetLineIntersection(Point P,Vector v,Point Q,Vector w)
{
	Vector u=P-Q;
	double t=Cross(w,u)/Cross(v,w);
	return P+v*t;
}

int main()
{
	Point A,B,C;
	int n;
	cin>>n;
	for(int T=1;T<=n;T++)
	{
		scanf("%lf%lf%lf%lf%lf%lf",&A.x,&A.y,&B.x,&B.y,&C.x,&C.y);
		Vector BC=C-B;
		Vector AB=B-A;
		Vector CA=A-C;
		Vector AD=AB+BC/3;
		Vector BE=BC+CA/3;
		Vector CF=CA+AB/3;
		Point P=GetLineIntersection(B,BE,A,AD);
		Point R=GetLineIntersection(A,AD,C,CF);
		Point Q=GetLineIntersection(B,BE,C,CF);
		printf("%.0lf\n",fabs(Cross(P-Q,R-Q)/2));
	}
	return 0;
}
