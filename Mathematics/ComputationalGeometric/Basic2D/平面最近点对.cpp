#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;

struct Point{double x,y;} p[200010];

void read(Point &a){scanf("%lf%lf",&a.x,&a.y);}
bool cmp(Point a,Point b){return a.x<b.x||(a.x==b.x&&a.y<b.y);}
double dist(Point a,Point b){return sqrt((b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y));}
void rotate(Point &a,double alpha)
{
	double x=a.x*cos(alpha)-a.y*sin(alpha);
	double y=a.y*cos(alpha)+a.x*sin(alpha);
	a.x=x;a.y=y;
}

int main()
{
	int n;
	double ans=1e16,tmp;
	cin>>n;
	for(int i=1;i<=n;i++) read(p[i]),rotate(p[i],1926);
	sort(p+1,p+1+n,cmp);
	for(int i=1;i<=n;i++)
	{
		for(int j=i+1;j<=n&&j<=i+5;j++)
		{
			tmp=dist(p[i],p[j]);
			if(tmp<ans) ans=tmp;
		}
	}
	printf("%.4lf\n",ans);
	return 0;
}
