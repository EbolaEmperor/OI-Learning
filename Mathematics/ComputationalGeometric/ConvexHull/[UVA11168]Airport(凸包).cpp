#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;

struct Point
{
	int x,y;
	Point(int _x=0,int _y=0):x(_x),y(_y){}
} p[10010],ch[10010];
typedef Point Vector;
int sumx,sumy;

bool operator < (const Point &a,const Point &b){return a.x<b.x||(a.x==b.x&&a.y<b.y);}
Vector operator - (const Vector &a,const Vector &b){return Vector(a.x-b.x,a.y-b.y);}
int Cross(Vector a,Vector b){return a.x*b.y-a.y*b.x;}

int ConvexHull(Point a[],int n,Point b[])
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
	if(n>1) m--;
	return m;
}

double GetDist(Point a,Point b,int n)
{
	double A=a.y-b.y;
	double B=b.x-a.x;
	double C=Cross(a,b);
	return fabs(A*sumx+B*sumy+C*n)/sqrt(A*A+B*B);
}

int main()
{
	int t,n;
	cin>>t;
	for(int T=1;T<=t;T++)
	{
		double ans=1e9,tmp;
		scanf("%d",&n);
		sumx=0;sumy=0;
		for(int i=0;i<n;i++)
		{
			scanf("%d%d",&p[i].x,&p[i].y);
			sumx+=p[i].x;
			sumy+=p[i].y;
		}
		printf("Case #%d: ",T);
		int m=ConvexHull(p,n,ch);
		if(m<=2){puts("0.000");continue;}
		ch[m]=ch[0];
		for(int i=0;i<m;i++)
		{
			tmp=GetDist(ch[i],ch[i+1],n);
			if(tmp<ans) ans=tmp;
		}
		printf("%.3lf\n",ans/n);
	}
	return 0;
}
