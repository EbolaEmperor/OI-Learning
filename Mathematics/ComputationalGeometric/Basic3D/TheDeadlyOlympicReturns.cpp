#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

const double eps=1e-6;
struct Point3D
{
	double x,y,z;
	Point3D(double _x=0,double _y=0,double _z=0):x(_x),y(_y),z(_z){}
} As,At,Bs,Bt;
typedef Point3D Vector3D;

int dcmp(double x)
{
	if(fabs(x)<=eps) return 0;
	else if(x<0) return -1;
	else return 1;
}

void read(Point3D &a){scanf("%lf%lf%lf",&a.x,&a.y,&a.z);}
bool operator == (Point3D a,Point3D b){return dcmp(a.x-b.x)==0&&dcmp(a.y-b.y)==0&&dcmp(a.z-b.z)==0;}
Vector3D operator + (Vector3D a,Vector3D b){return Vector3D(a.x+b.x,a.y+b.y,a.z+b.z);}
Vector3D operator - (Vector3D a,Vector3D b){return Vector3D(a.x-b.x,a.y-b.y,a.z-b.z);}
Vector3D operator / (Vector3D a,double k){return Vector3D(a.x/k,a.y/k,a.z/k);}
Vector3D operator * (Vector3D a,double k){return Vector3D(a.x*k,a.y*k,a.z*k);}

double Dot(Vector3D a,Vector3D b){return a.x*b.x+a.y*b.y+a.z*b.z;}
double Length(Vector3D a){return sqrt(Dot(a,a));}
Vector3D Cross(Vector3D a,Vector3D b){return Vector3D(a.y*b.z-b.y*a.z,a.z*b.x-a.x*b.z,a.x*b.y-a.y*b.x);}

double DistanceOfPointsAndSegment(Point3D p,Point3D a,Point3D b)  
{  
    if(a==b) return Length(p-a);   
    Vector3D v1=b-a,v2=p-a,v3=p-b;  
    if(dcmp(Dot(v1, v2))<0) return Length(v2);  
    if(dcmp(Dot(v1, v3))>0) return Length(v3);  
    return Length(Cross(v1, v2))/Length(v1);   
}  

int main()
{
	int t,time;
	cin>>t;
	for(int T=1;T<=t;T++)
	{
		scanf("%d",&time);
		read(As);read(At);
		read(Bs);read(Bt);
		Vector3D v1=(At-As)/time;
		Vector3D v2=(Bt-Bs)/time;
		v2=v2-v1;
		printf("Case %d: %.4lf\n",T,DistanceOfPointsAndSegment(As,Bs,Bs+v2*(1e9)));
	}
	return 0;
}
