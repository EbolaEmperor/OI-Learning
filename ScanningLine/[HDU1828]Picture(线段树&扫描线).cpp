#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<map>
using namespace std;

const int MAXN=800000;
struct SegmentTree{int m,c;} st[MAXN];
struct Line{int x,y_1,y_2,s;} line[MAXN];
int y[MAXN],ty[MAXN];
int x_1[MAXN],x_2[MAXN],y_1[MAXN],y_2[MAXN];
map<int,int> indexs;

bool operator < (const Line &a,const Line &b){return a.x<b.x;}

void build(int o,int l,int r)
{
	st[o].m=st[o].c=0;
	if(r-l>1)
	{
		int mid=(l+r)/2;
		build(o*2,l,mid);
		build(o*2+1,mid,r);
	}
}

void update(int o,int l,int r)
{
	if(st[o].c>0) st[o].m=y[r-1]-y[l-1];
	else if(r-l==1) st[o].m=0;
	else st[o].m=st[o*2].m+st[o*2+1].m;
}

void add(int o,int l,int r,int nl,int nr,int k)
{
	if(l>=nl&&r<=nr)
		st[o].c+=k;
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
		st[i].c=st[i].m=0;
		ty[i]=y[i]=0;
		line[i].x=line[i].y_1=line[i].y_2=0;
		line[i].s=0;
	}
}

int main()
{
	int n;
	while(~scanf("%d",&n))
	{
		init();
		for(int i=0;i<n;i++)
		{
			scanf("%d%d%d%d",x_1+i,y_1+i,x_2+i,y_2+i);
			line[i*2].x=x_1[i];line[i*2+1].x=x_2[i];
			line[i*2].y_1=line[i*2+1].y_1=y_1[i];
			line[i*2].y_2=line[i*2+1].y_2=y_2[i];
			line[i*2].s=1;line[i*2+1].s=-1;
			ty[i*2]=y_1[i];ty[i*2+1]=y_2[i];
		}
		int sz=1,m=2*n;
		sort(ty,ty+m);
		sort(line,line+m);
		y[0]=ty[0];
		for(int i=1;i<m;i++)
			if(ty[i]!=ty[i-1]) y[sz++]=ty[i];
		for(int i=0;i<sz;i++)
			indexs[y[i]]=i;
		build(1,1,sz);
		int len=0,pre=0;
		for(int i=0;i<m;i++)
		{
			int l=indexs[line[i].y_1]+1,r=indexs[line[i].y_2]+1;
			add(1,1,sz,l,r,line[i].s);
			len+=abs(st[1].m-pre);
			pre=st[1].m;
		}
		init();
		for(int i=0;i<n;i++)
		{
			line[i*2].x=y_1[i];line[i*2+1].x=y_2[i];
			line[i*2].y_1=line[i*2+1].y_1=x_1[i];
			line[i*2].y_2=line[i*2+1].y_2=x_2[i];
			line[i*2].s=1;line[i*2+1].s=-1;
			ty[i*2]=x_1[i];ty[i*2+1]=x_2[i];
		}
		sz=1;
		sort(ty,ty+m);
		sort(line,line+m);
		y[0]=ty[0];
		for(int i=1;i<m;i++)
			if(ty[i]!=ty[i-1]) y[sz++]=ty[i];
		for(int i=0;i<sz;i++)
			indexs[y[i]]=i;
		build(1,1,sz);
		pre=0;
		for(int i=0;i<m;i++)
		{
			int l=indexs[line[i].y_1]+1,r=indexs[line[i].y_2]+1;
			add(1,1,sz,l,r,line[i].s);
			len+=abs(st[1].m-pre);
			pre=st[1].m;
		}
		printf("%d\n",len);
	}
	return 0;
}
