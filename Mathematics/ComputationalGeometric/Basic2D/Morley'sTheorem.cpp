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

Vector operator + (const Vector &a,const Vector &b){return Vector(a.x+b.x,a.y+b.y);}
Vector operator - (const Vector &a,const Vector &b){return Vector(a.x-b.x,a.y-b.y);}
Vector operator * (const double &x,const Vector &a){return Vector(a.x*x,a.y*x);}
double Cross(Vector a,Vector b){return a.x*b.y-a.y*b.x;}
double Dot(Vector a,Vector b){return a.x*b.x+a.y*b.y;}
double Lenth(Vector a){return sqrt(Dot(a,a));}
double Angle(Vector a,Vector b){return acos(Dot(a,b)/(Lenth(a)*Lenth(b)));}
Vector Rotate(Vector a,double alpha){return Vector(a.x*cos(alpha)-a.y*sin(alpha),a.x*sin(alpha)+a.y*cos(alpha));}
Point GetLineIntersection(Point P,Vector v,Point Q,Vector w)
{
	Vector u=P-Q;
	double t=Cross(w,u)/Cross(v,w);
	return P+t*v;
}

Point GetD(Point A,Point B,Point C)
{
	Vector v1=C-B;
	double a=Angle(v1,A-B);
	v1=Rotate(v1,a/3);
	Vector v2=B-C;
	double b=Angle(v2,A-C);
	v2=Rotate(v2,-b/3);
	return GetLineIntersection(B,v1,C,v2);
}

int main()
{
	Point A,B,C,D,E,F;
	int t;
	cin>>t;
	for(int T=1;T<=t;T++)
	{
		scanf("%lf%lf%lf%lf%lf%lf",&A.x,&A.y,&B.x,&B.y,&C.x,&C.y);
		D=GetD(A,B,C);
		E=GetD(B,C,A);
		F=GetD(C,A,B);
		printf("%.6lf %.6lf %.6lf %.6lf %.6lf %.6lf\n",D.x,D.y,E.x,E.y,F.x,F.y);
	}
	return 0;
}
