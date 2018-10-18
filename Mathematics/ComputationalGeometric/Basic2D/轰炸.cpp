#include<iostream>
#include<cstdio>
using namespace std;

struct Point
{
	int x,y;
	Point(int x=0,int y=0):x(x),y(y) {}
} p[1000];

void read(Point &a){scanf("%d%d",&a.x,&a.y);}
Point operator - (Point a,Point b) {return Point(a.x-b.x,a.y-b.y);}
int cross(Point a,Point b) {return a.x*b.y-a.y*b.x;}

int main()
{
	int n,ans=0,cnt;
	cin>>n;
	for(int i=1;i<=n;i++) read(p[i]);
	for(int i=1;i<n;i++)
		for(int j=i+1;j<=n;j++)
		{
			cnt=2;
			for(int k=1;k<=n;k++)
			{
				if(k==i||k==j) continue;
				if(cross(p[j]-p[i],p[k]-p[j])==0) cnt++;
			}
			if(cnt>ans) ans=cnt;
		}
	cout<<ans<<endl;
	return 0;
}
