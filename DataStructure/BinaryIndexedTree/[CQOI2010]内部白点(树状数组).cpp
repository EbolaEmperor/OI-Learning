#include<bits/stdc++.h>
#define lowbit(x) (x&-x)
using namespace std;

const int N=100010;
struct Type{int ty,x1,x2,y;};
struct Point{int x,y;} pnt[N];
int hx[N<<2],hy[N<<2],n,mx,my;
Type p[N<<2];
int c[N<<2];

void Add(int p,int x){for(;p<=mx;p+=lowbit(p)) c[p]+=x;}
int Sum(int p){int res=0;for(;p;p-=lowbit(p)) res+=c[p];return res;}

bool cmp1(const Point &a,const Point &b){return a.x<b.x||a.x==b.x&&a.y<b.y;}
bool cmp2(const Point &a,const Point &b){return a.y<b.y||a.y==b.y&&a.x<b.x;}
bool operator < (const Type &a,const Type &b)
{
	if(a.y!=b.y) return a.y<b.y;
	if(a.ty!=b.ty) return a.ty<b.ty;
	return a.x1<b.x1;
}

int prework()
{
	sort(pnt+1,pnt+1+n,cmp1);
	int cnt=0;
	for(int i=1;i<n;i++)
		if(pnt[i+1].x==pnt[i].x&&pnt[i+1].y-pnt[i].y>1)
		{
			p[++cnt].x1=pnt[i].x;
			p[cnt].y=pnt[i].y+1;
			p[cnt].ty=1;
			p[++cnt].x1=pnt[i+1].x;
			p[cnt].y=pnt[i+1].y;
			p[cnt].ty=2;
		}
	sort(pnt+1,pnt+1+n,cmp2);
	for(int i=1;i<n;i++)
		if(pnt[i+1].y==pnt[i].y&&pnt[i+1].x-pnt[i].x>1)
		{
			p[++cnt].ty=3;
			p[cnt].x1=pnt[i].x;
			p[cnt].x2=pnt[i+1].x;
			p[cnt].y=pnt[i].y;
		}
	return cnt;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d%d",&pnt[i].x,&pnt[i].y);
	for(int i=1;i<=n;i++)
	{
		hx[i*3-2]=pnt[i].x;
		hx[i*3-1]=pnt[i].x-1;
		hx[i*3]=pnt[i].x+1;
		hy[i*3-2]=pnt[i].y;
		hy[i*3-1]=pnt[i].y-1;
		hy[i*3]=pnt[i].y+1;
	}
	sort(hx+1,hx+1+3*n);sort(hy+1,hy+1+3*n);
	mx=unique(hx+1,hx+1+3*n)-(hx+1);
	my=unique(hy+1,hy+1+3*n)-(hy+1);
	for(int i=1;i<=n;i++)
	{
		pnt[i].x=lower_bound(hx+1,hx+1+mx,pnt[i].x)-hx;
		pnt[i].y=lower_bound(hy+1,hy+1+my,pnt[i].y)-hy;
	}
	int m=prework(),ans=0;
	sort(p+1,p+1+m);
	for(int i=1;i<=m;i++)
	{
		if(p[i].ty==1) Add(p[i].x1,1);
		if(p[i].ty==2) Add(p[i].x1,-1);
		if(p[i].ty==3) ans+=Sum(p[i].x2-1)-Sum(p[i].x1);
	}
	printf("%d\n",ans+n);
	return 0;
}
