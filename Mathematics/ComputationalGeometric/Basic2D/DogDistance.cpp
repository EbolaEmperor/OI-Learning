#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

const double eps=1e-6;
struct Point
{
	double x,y;
	Point(double _x=0,double _y=0):x(_x),y(_y){}
};
typedef Point Vector;
int t,a,b;
Point p[60],q[60];
double Min,Max;

Vector operator + (const Vector &a,const Vector &b){return Vector(a.x+b.x,a.y+b.y);}
Vector operator - (const Vector &a,const Vector &b){return Vector(a.x-b.x,a.y-b.y);}
Vector operator * (const Vector &a,const double &x){return Vector(a.x*x,a.y*x);}
Vector operator / (const Vector &a,const double &x){return Vector(a.x/x,a.y/x);}
double Dot(Vector a,Vector b){return a.x*b.x+a.y*b.y;}
double Cross(Vector a,Vector b){return a.x*b.y-a.y*b.x;}
int dcmp(double x){if(fabs(x)<=eps) return 0;else return x<0?-1:1;}
bool operator == (const Vector &a,const Vector &b){return dcmp(a.x-b.x)==0&&dcmp(a.y-b.y)==0;}
double Length(Vector a){return sqrt(Dot(a,a));}
double DistanceToSegment(Point P,Point A,Point B)
{
	if(A==B) return Length(A-P);
	Vector v1=B-A,v2=P-A,v3=P-B;
	if(dcmp(Dot(v1,v2))==-1) return Length(v2);
	else if(dcmp(Dot(v1,v3))==1) return Length(v3);
	else return fabs(Cross(v1,v2))/Length(v1);
}

void update(Point P,Point A,Point B)
{
	Min=min(Min,DistanceToSegment(P,A,B));
	Max=max(Max,Length(P-A));
	Max=max(Max,Length(P-B));
}

int main()
{
	cin>>t;
	for(int T=1;T<=t;T++)
	{
		scanf("%d%d",&a,&b);
		for(int i=0;i<a;i++) scanf("%lf%lf",&p[i].x,&p[i].y);
		for(int i=0;i<b;i++) scanf("%lf%lf",&q[i].x,&q[i].y);
		double LenA=0.0,LenB=0.0;
		for(int i=0;i<a-1;i++) LenA+=Length(p[i+1]-p[i]);
		for(int i=0;i<b-1;i++) LenB+=Length(q[i+1]-q[i]);
		int Sa=0,Sb=0;
		Point Pa=p[0],Pb=q[0];
		Min=1e9,Max=-1e9;
		while(Sa<a-1&&Sb<b-1)
		{
			double La=Length(p[Sa+1]-Pa);
			double Lb=Length(q[Sb+1]-Pb);
			double time=min(La/LenA,Lb/LenB);
			Vector Va=(p[Sa+1]-Pa)/La*time*LenA;
			Vector Vb=(q[Sb+1]-Pb)/Lb*time*LenB;
			update(Pa,Pb,Pb+Vb-Va);
			Pa=Pa+Va;
			Pb=Pb+Vb;
			if(Pa==p[Sa+1]) Sa++;
			if(Pb==q[Sb+1]) Sb++;
		}
		printf("Case %d: %.0lf\n",T,Max-Min);
	}
	return 0;
}
