#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;

const double pi=acos(-1);
struct Point
{
	int x,y;
	Point(int _x=0,int _y=0):x(_x),y(_y){}
} p[1010],ch[1010];

void read(int &x)
{
	x=0;
	char c=getchar();
	int fg=1;
	while((c<'0'||c>'9')&&c!='-') c=getchar();
	if(c=='-') fg=-1,c=getchar();
	while(c>='0'&&c<='9') x=x*10+(int)(c-'0'),c=getchar();
	x*=fg;
}
void read(Point &a){read(a.x);read(a.y);}
bool cmp(Point a,Point b){return a.x<b.x||(a.x==b.x&&a.y<b.y);}
Point operator - (const Point &a,const Point &b){return Point(a.x-b.x,a.y-b.y);}
int cross(Point a,Point b){return a.x*b.y-a.y*b.x;}
double dist(Point a,Point b){return sqrt((b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y));}

int ConvexHull(Point p[],int n,Point ch[])
{
	sort(p+1,p+1+n,cmp);
	int m=0;
	for(int i=1;i<=n;i++)
	{
		while(m>1&&cross(ch[m-1]-ch[m-2],p[i]-ch[m-2])<=0) m--;
		ch[m++]=p[i];
	}
	int k=m;
	for(int i=n-1;i>=1;i--)
	{
		while(m>k&&cross(ch[m-1]-ch[m-2],p[i]-ch[m-2])<=0) m--;
		ch[m++]=p[i];
	}
	return m;
}

int main()
{
	int n,l;
	read(n);read(l);
	for(int i=1;i<=n;i++) read(p[i]);
	int m=ConvexHull(p,n,ch);
	ch[m]=ch[0];
	double ans=0;
	for(int i=0;i<m;i++) ans+=dist(ch[i],ch[i+1]);
	ans+=2*pi*l;
	printf("%d\n",(int)round(ans));
	return 0;
}
