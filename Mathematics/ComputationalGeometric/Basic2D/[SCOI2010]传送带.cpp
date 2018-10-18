#include<bits/stdc++.h>
using namespace std;

struct Point
{
	double x,y;
	Point(double a=0,double b=0):x(a),y(b){}
	friend Point operator + (Point A,Point B){return Point(A.x+B.x,A.y+B.y);}
	friend Point operator - (Point A,Point B){return Point(A.x-B.x,A.y-B.y);}
	friend Point operator * (Point A,double x){return Point(A.x*x,A.y*x);}
	friend bool operator == (Point a,Point b){return fabs(a.x-b.x)<1e-6&&fabs(a.y-b.y)<1e-6;}
	friend istream& operator >> (istream& in,Point &a)
	{
		double x,y;
		in>>x>>y;
		a.x=x;a.y=y;
	}
	friend double Len(const Point &a,const Point &b)
	{
		double x=a.x-b.x,y=a.y-b.y;
		return sqrt(x*x+y*y);
	}
} A,B,C,D;
double P,Q,R;

double gao(double x)
{
	Point P=(A==B)?A:A+(B-A)*(x/Len(A,B));
	if(C==D) return Len(P,C)/R;
	double l=0,r=Len(C,D),ans;
	while(r-l>1e-4)
	{
		double mid1=l+(r-l)/3,mid2=r-(r-l)/3;
		Point p1=C+(D-C)*(mid1/Len(C,D));
		Point p2=C+(D-C)*(mid2/Len(C,D));
		double ans1=Len(P,p1)/R+Len(p1,D)/Q;
		double ans2=Len(P,p2)/R+Len(p2,D)/Q;
		if(ans1>ans2) l=mid1,ans=ans1;
		else r=mid2,ans=ans2;
	}
	return ans;
}

int main()
{
	cin>>A>>B>>C>>D;
	cin>>P>>Q>>R;
	double l=0,r=Len(A,B);
	double ans=min(gao(l),gao(r)+r/P);
	while(r-l>1e-4)
	{
		double mid1=l+(r-l)/3,mid2=r-(r-l)/3;
		double ans1=gao(mid1)+mid1/P;
		double ans2=gao(mid2)+mid2/P;
		if(ans1>ans2) l=mid1,ans=ans1;
		else r=mid2,ans=ans2;
	}
	printf("%.2lf\n",ans);
	return 0;
}
