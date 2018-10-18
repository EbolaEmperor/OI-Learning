#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

struct Point
{
	int x,y;
	Point(int _x=0,int _y=0):x(_x),y(_y){}
};
Point p[4];

Point operator - (const Point &a,const Point &b){return Point(a.x-b.x,a.y-b.y);}
int cross(Point a,Point b){return a.x*b.y-a.y*b.x;}

int main()
{
	char c;
	for(int i=0;i<4;i++) cin>>c>>p[i].x>>c>>p[i].y>>c;
	for(int i=0;i<3;i++)
		if(p[3].x==p[i].x&&p[3].y==p[i].y){putchar('4');return 0;}
	int s1=abs(cross(p[0]-p[3],p[1]-p[3]));
	int s2=abs(cross(p[0]-p[3],p[2]-p[3]));
	int s3=abs(cross(p[1]-p[3],p[2]-p[3]));
	int s=abs(cross(p[0]-p[2],p[1]-p[2]));
	if(s1+s2+s3>s){putchar('2');return 0;}
	if(s1==0||s2==0||s3==0) putchar('3');else putchar('1');
	return 0;
}
