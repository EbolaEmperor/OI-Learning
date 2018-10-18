#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

struct Point
{
	int x,y;
	Point(int _x=0,int _y=0):x(_x),y(_y){}
} q[10],p[10];
typedef Point Vector;

Vector operator + (Vector a,Vector b){return Vector(a.x+b.x,a.y+b.y);}
Vector operator - (Vector a,Vector b){return Vector(a.x-b.x,a.y-b.y);}
int Dot(Vector a,Vector b){return a.x*b.x+a.y*b.y;}
int Cross(Vector a,Vector b){return a.x*b.y-a.y*b.x;}
int Length2(Vector a){return Dot(a,a);}
bool operator < (Point a,Point b){return a.x<b.x||(a.x==b.x&&a.y<b.y);}

void ConvexHull(Point a[],int n,Point b[])
{
	sort(a,a+n);
	int m=0;
	for(int i=0;i<n;i++)
	{
		while(m>1&&Cross(b[m-1]-b[m-2],a[i]-b[m-2])<=0) m--;
		b[m++]=a[i];
	}
	int k=m;
	for(int i=n-2;i>=0;i--)
	{
		while(m>k&&Cross(b[m-1]-b[m-2],a[i]-b[m-2])<=0) m--;
		b[m++]=a[i];
	}
}

int main()
{
	int n;
	cin>>n;
	for(int T=1;T<=n;T++)
	{
		for(int i=0;i<4;i++) scanf("%d%d",&q[i].x,&q[i].y);
		ConvexHull(q,4,p);
		printf("Case %d: ",T);
		p[4]=p[0];
		int cnt1=0,cnt2=0,cnt3=0;
		for(int i=0;i<3;i++)
			for(int j=i+1;j<4;j++)
			{
				if(Cross(p[i+1]-p[i],p[j+1]-p[j])==0) cnt1++;
				if(Dot(p[i+1]-p[i],p[j+1]-p[j])==0) cnt2++;
			}
		if(cnt1==0){puts("Ordinary Quadrilateral");continue;}
		if(cnt1==1){puts("Trapezium");continue;}
		for(int i=0;i<3;i++)
			if(Length2(p[i+1]-p[i])==Length2(p[i+2]-p[i+1])) cnt3++;
		if(cnt2==4&&cnt3==3){puts("Square");continue;}
		if(cnt2==4){puts("Rectangle");continue;}
		if(cnt3==3){puts("Rhombus");continue;}
		puts("Parallelogram");
	}
	return 0;
}
