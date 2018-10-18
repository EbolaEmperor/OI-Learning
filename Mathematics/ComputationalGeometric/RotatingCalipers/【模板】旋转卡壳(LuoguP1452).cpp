#include<bits/stdc++.h>
using namespace std;

struct Point
{
	double x,y;
	Point(double _x=0,double _y=0):x(_x),y(_y){}
} p[2000005],ch[2000005];

typedef Point Vector;

const double eps=1e-6;
int dcmp(double x)
{
	if(fabs(x)<=eps) return 0;
	else if(x<0) return -1;
	else return 1;
}

double Angle(Vector a){return atan2(a.y,a.x);}
Vector operator + (Vector a,Vector b){return Vector(a.x+b.x,a.y+b.y);}
Vector operator - (Vector a,Vector b){return Vector(a.x-b.x,a.y-b.y);}
Vector operator - (Vector b){return Vector(-b.x,-b.y);}
Vector operator * (Vector a,double x){return Vector(a.x*x,a.y*x);}
Vector operator / (Vector a,double x){return Vector(a.x/x,a.y/x);}

bool operator < (Point a,Point b){return a.x<b.x||(a.x==b.x&&a.y<b.y);}
bool operator == (Point a,Point b){return dcmp(a.x-b.x)==0&&dcmp(a.y-b.y)==0;}

double Dot(Vector a,Vector b){return a.x*b.x+a.y*b.y;}
double Length2(Vector a){return Dot(a,a);}
double Length(Vector a){return sqrt(Length2(a));}
double Angle(Vector a,Vector b){return acos(Dot(a,b)/(Length(a)*Length(b)));}
double Cross(Vector a,Vector b){return a.x*b.y-a.y*b.x;}

int ConvexHull(Point *a,int n,Point *b)
{
	sort(a,a+n);
	int m=0;
	for(int i=0;i<n;i++)
	{
		while(m>1&&dcmp(Cross(b[m-1]-b[m-2],a[i]-b[m-2]))<=0) m--;
		b[m++]=a[i];
	}
	int k=m;
	for(int i=n-2;i>=0;i--)
	{
		while(m>k&&dcmp(Cross(b[m-1]-b[m-2],a[i]-b[m-2]))<=0) m--;
		b[m++]=a[i];
	}
	if(n>1) m--;
	return m;
}

double RotatingCalipers(Point *ch,int n)
{
	int p1=0,p2;
	for(int i=1;i<=n;i++)
		if(dcmp(ch[i].x-ch[i-1].x)<0){p2=i-1;break;}
	int u=p1,v=p2;
	Vector v1,v2;
	v1=Vector(0,-1e9);
	v2=Vector(0,1e9);
	double ans=0;
	while(u<=p2&&v<n)
	{
		ans=max(ans,Length2(ch[v]-ch[u]));
		if(dcmp(Angle(ch[u+1]-ch[u],v1)-Angle(ch[v+1]-ch[v],v2))<0) v1=ch[u+1]-ch[u],u++,v2=-v1;
		else v2=ch[v+1]-ch[v],v++,v1=-v2;
	}
	return ans;
}

int main()
{
	int n;
	cin>>n;
	for(int i=0;i<n;i++)
		scanf("%lf%lf",&p[i].x,&p[i].y);
	int m=ConvexHull(p,n,ch);
	cout<<(int)round(RotatingCalipers(ch,m))<<endl;
	return 0;
}
