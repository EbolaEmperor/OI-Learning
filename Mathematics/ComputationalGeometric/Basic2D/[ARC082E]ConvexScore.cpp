#include<bits/stdc++.h>
#define ha 998244353
using namespace std;

struct Point
{
	int x,y;
	Point(int a=0,int b=0):x(a),y(b){}
	friend Point operator - (const Point &a,const Point &b){return Point(a.x-b.x,a.y-b.y);}
	friend int operator * (const Point &a,const Point &b){return a.x*b.y-a.y*b.x;}
} p[210];
int pw2[210];

int main()
{
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&p[i].x,&p[i].y);
	pw2[0]=1;
	for(int i=1;i<=n;i++)
		pw2[i]=(pw2[i-1]<<1)%ha;
	int ans=(pw2[n]-n*(n-1)/2-n-1+ha)%ha;
	for(int i=2;i<n;i++)
		for(int j=i+1;j<=n;j++)
		{
			int sum=0;
			for(int k=1;k<i;k++)
				sum+=((p[k]-p[i])*(p[j]-p[i])==0);
			ans=(ans-pw2[sum]+1+ha)%ha;
		}
	printf("%d\n",ans);
	return 0;
}
