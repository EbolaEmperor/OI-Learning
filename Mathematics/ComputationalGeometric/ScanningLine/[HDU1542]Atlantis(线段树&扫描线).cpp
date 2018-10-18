#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<map>
using namespace std;

const int MAXN=4000;
struct Segment{int c;double m;} node[MAXN];
struct Line{double x,y1,y2;bool s;} line[MAXN];
double ty[MAXN],y[MAXN];
map<double,int> indexs;

const double eps=1e-6;
int dcmp(double a)
{
	if(fabs(a)<=eps) return 0;
	else if(a>0) return 1;
	else return -1;
}

bool operator < (const Line &a,const Line &b){return dcmp(a.x-b.x)<0;}

void build(int o,int l,int r)
{
	node[o].m=0,node[o].c=0;
	if(r-l>1)
	{
		int mid=(l+r)/2;
		build(o*2,l,mid);
		build(o*2+1,mid,r);
	}
}

void update(int o,int l,int r)
{
	if(node[o].c>0) node[o].m=y[r-1]-y[l-1];
	else if(r-l==1) node[o].m=0;
	else node[o].m=node[o*2].m+node[o*2+1].m;
}

void add(int o,int l,int r,int nl,int nr,int k)
{
	if(l>=nl&&r<=nr)
		node[o].c+=k;
	else
	{
		int mid=(l+r)/2;
		if(nl<mid) add(o*2,l,mid,nl,nr,k);
		if(nr>mid) add(o*2+1,mid,r,nl,nr,k);
	}
	update(o,l,r);
}

void init()
{
	indexs.clear();
	for(int i=0;i<MAXN;i++)
	{
		node[i].c=0;
		node[i].m=0;
		ty[i]=y[i]=0;
		line[i].x=line[i].y1=line[i].y2=0;
		line[i].s=0;
	}
}

int main()
{
	int n,T=0;
	double x1,x2,y1,y2;
	while(~scanf("%d",&n)&&n)
	{
		T++;
		init();
		for(int i=0;i<n;i++)
		{
			scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
			line[2*i].x=x1;line[2*i+1].x=x2;
			line[2*i].y1=line[2*i+1].y1=y1;
			line[2*i].y2=line[2*i+1].y2=y2;
			line[2*i].s=1;line[2*i+1].s=0;
			ty[2*i]=y1;ty[2*i+1]=y2;
		}
		n*=2;
		sort(line,line+n);
		sort(ty,ty+n);
		y[0]=ty[0];
		int sz=1;
		for(int i=1;i<n;i++)
			if(dcmp(ty[i]-ty[i-1])!=0)
				y[sz++]=ty[i];
		for(int i=0;i<sz;i++)
			indexs[y[i]]=i;
		build(1,1,sz);
		double area=0;
		for(int i=0;i<n-1;i++)
		{
			int l=indexs[line[i].y1]+1,r=indexs[line[i].y2]+1;
			if(line[i].s) add(1,1,n,l,r,1);
			else add(1,1,n,l,r,-1);
			area+=node[1].m*(line[i+1].x-line[i].x);
		}
		printf("Test case #%d\nTotal explored area: %.2lf\n\n",T,area);
	}
	return 0;
}
