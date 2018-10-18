#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

struct Point{double x,y;};
struct Matrix{Point a,b;} r[510];
struct Circle{Point o;double r;} c[510];
int nc=0,nr=0;

void read(Point &a){scanf("%lf%lf",&a.x,&a.y);}
void read(Circle &a){read(a.o);scanf("%lf",&a.r);}
void read(Matrix &a){read(a.a);read(a.b);}
double dist2(Point a,Point b){return (b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y);}
double dist(Point a,Point b){return sqrt(dist2(a,b));}
bool judge(Point a,Circle c){double d=dist(a,c.o);return d<c.r;}
bool judge(Point a,Matrix r){return a.x>r.a.x&&a.y>r.a.y&&a.x<r.b.x&&a.y<r.b.y;}
void sort(Matrix &r){if(r.b.x<r.a.x) swap(r.a.x,r.b.x);if(r.b.y<r.a.y) swap(r.a.y,r.b.y);}

int main()
{
	int n,m;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		char ch=getchar();
		while(ch!='c'&&ch!='r') ch=getchar();
		if(ch=='c') read(c[++nc]);
		if(ch=='r') read(r[++nr]),sort(r[nr]);
	}
	Point tmp;
	for(int i=1;i<=m;i++)
	{
		read(tmp);
		int ans=0;
		for(int j=1;j<=nc;j++) ans+=judge(tmp,c[j]);
		for(int j=1;j<=nr;j++) ans+=judge(tmp,r[j]);
		printf("%d\n",ans);
	}
	return 0;
}
