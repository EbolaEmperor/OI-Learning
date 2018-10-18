#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#define INF 0x7fffffff
using namespace std;

struct Line{int u,v;double alpha;} l[65000];
struct Point{int x,y;} p[300];
int f[300];

bool cmp(Line a,Line b){return a.alpha<b.alpha;}
void read(Point &a){scanf("%d%d",&a.x,&a.y);}

int main()
{
	int n,m=0,ans=0;
	cin>>n;
	for(int i=1;i<=n;i++) read(p[i]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			if(i==j) continue;
			l[++m].u=i;
			l[m].v=j;
			l[m].alpha=atan2(p[j].y-p[i].y,p[j].x-p[i].x);
		}
	sort(l+1,l+1+m,cmp);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++) f[j]=-INF;
		f[i]=0;
		for(int j=1;j<=m;j++) f[l[j].v]=max(f[l[j].v],f[l[j].u]+1);
		if(f[i]>ans) ans=f[i];
	}
	cout<<ans<<endl;
	return 0;
}
