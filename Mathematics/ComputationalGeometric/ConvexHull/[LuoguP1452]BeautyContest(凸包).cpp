//思路：求出凸包，再枚举凸包上的点算最大距离
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

struct Point
{
	int x,y;
	Point(int x=0,int y=0):x(x),y(y){}
} p[50010],ch[50010];

Point operator - (Point a,Point b){return Point(a.x-b.x,a.y-b.y);}
int cross(Point a,Point b){return a.x*b.y-a.y*b.x;}
bool operator < (const Point &a,const Point &b){return a.x<b.x||(a.x==b.x&&a.y<b.y);}
void read(Point &x){scanf("%d%d",&x.x,&x.y);}

int ConvexHull(Point a[],int n,Point b[])
{
	sort(a,a+n);
	int m=0;
	for(int i=0;i<n;i++)
	{
		while(m>1&&cross(b[m-1]-b[m-2],a[i]-b[m-2])<=0) m--;
		b[m++]=a[i];
	}
	int k=m;
	for(int i=n-2;i>=0;i--)
	{
		while(m>k&&cross(b[m-1]-b[m-2],a[i]-b[m-2])<=0) m--;
		b[m++]=a[i];
	}
	return m;
}

int main()
{
	int n,ans=0;
	cin>>n;
	for(int i=0;i<n;i++) read(p[i]);
	int m=ConvexHull(p,n,ch);
	for(int i=0;i<m;i++)
		for(int j=i+1;j<m;j++)
		{
			int s=(ch[i].x-ch[j].x)*(ch[i].x-ch[j].x)+(ch[i].y-ch[j].y)*(ch[i].y-ch[j].y);
			if(s>ans) ans=s;
		}
	cout<<ans<<endl;
	return 0;
}
