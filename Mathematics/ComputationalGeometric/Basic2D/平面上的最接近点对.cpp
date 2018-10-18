#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

struct Point
{
	int x,y;
	Point(int x=0,int y=0):x(x),y(y) {}
} p[10010];

void read(Point &a){scanf("%d%d",&a.x,&a.y);}
int dist2(Point a,Point b){return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);}

int main()
{
	int n,ans=0x7fffffff;
	cin>>n;
	for(int i=1;i<=n;i++) read(p[i]);
	for(int i=1;i<n;i++)
		for(int j=i+1;j<=n;j++)
		{
			int tmp=dist2(p[i],p[j]);
			if(tmp<ans&&tmp>0) ans=tmp;
		}
	printf("%.4f\n",sqrt(ans));
	return 0;
}
