#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

struct XY{int x,y;} a[100010];
bool operator < (XY x,XY y){return x.x<y.x;}

int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) scanf("%d%d",&a[i].x,&a[i].y);
	sort(a+1,a+1+n);
	for(int i=2;i<=n;i++)
		if(a[i-1].x<a[i].x&&a[i-1].y>a[i].y){puts("Happy Alex");return 0;}
	puts("Poor Alex");
	return 0;
}
