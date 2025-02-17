#include<bits/stdc++.h>
#define lowbit(x) (x&-x)
using namespace std;

int read()
{
	int x=0;char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	return x;
}

const int MAX=1000000;
int bit[MAX+10],mx;

void Add(int p,int k){for(;p<=mx;p+=lowbit(p))if(k>bit[p])bit[p]=k;}
int Qry(int p){int res=0;for(;p>0;p-=lowbit(p))if(bit[p]>res)res=bit[p];return res;}
void Clr(int p){for(;p<=mx;p+=lowbit(p))bit[p]=0;}

struct OPT{int x,y,id,ty,time;} opt[MAX+10],tmp[MAX+10];
int ans[MAX/2+10];

bool operator < (const OPT &a,const OPT &b){return a.x<b.x||(a.x==b.x&&a.ty<b.ty);}

void CDQ(int L,int R)
{
	if(L==R) return;
	int M=(L+R)/2;
	int p1=L,p2=M+1,lst=0;
	for(int i=L;i<=R;i++)
		if(opt[i].time<=M) tmp[p1++]=opt[i];
		else tmp[p2++]=opt[i];
	for(int i=L;i<=R;i++) opt[i]=tmp[i];
	p1=L;p2=M+1;
	while(p2<=R)
	{
		while(p1<=M&&opt[p1].ty!=1) p1++;
		while(p2<=R&&opt[p2].ty==1) p2++;
		if(p1<=M&&opt[p1].x<=opt[p2].x)
			Add(opt[p1].y,opt[p1].x+opt[p1].y),lst=p1++;
		else if(p2<=R)
		{
			int t=Qry(opt[p2].y);
			if(t&&opt[p2].x+opt[p2].y-t<ans[opt[p2].id])
				ans[opt[p2].id]=opt[p2].x+opt[p2].y-t;
			p2++;
		}
	}
	for(int i=L;i<=lst;i++)
		if(opt[i].ty==1) Clr(opt[i].y);
	CDQ(L,M);CDQ(M+1,R);
}

int main()
{
	int n=read(),m=read();
	for(int i=1;i<=n;i++)
	{
		opt[i].time=i;
		opt[i].x=read()+1;
		opt[i].y=read()+1;
		opt[i].ty=1;
		if(opt[i].x>mx) mx=opt[i].x;
		if(opt[i].y>mx) mx=opt[i].y;
	}
	int cnt=0;
	for(int i=1;i<=m;i++)
	{
		opt[n+i].time=n+i;
		opt[n+i].ty=read();
		opt[n+i].x=read()+1;
		opt[n+i].y=read()+1;
		if(opt[n+i].ty==2) opt[n+i].id=++cnt;
		if(opt[n+i].x>mx) mx=opt[n+i].x;
		if(opt[n+i].y>mx) mx=opt[n+i].y;
	}
	mx++;
	for(int i=1;i<=cnt;i++) ans[i]=4*mx;
	sort(opt+1,opt+1+n+m);
	CDQ(1,n+m);
	for(int i=1;i<=n+m;i++) opt[i].y=-opt[i].y+mx;
	sort(opt+1,opt+1+n+m);
	CDQ(1,n+m);
	for(int i=1;i<=n+m;i++) opt[i].x=-opt[i].x+mx;
	sort(opt+1,opt+1+n+m);
	CDQ(1,n+m);
	for(int i=1;i<=n+m;i++) opt[i].y=-(opt[i].y-mx);
	sort(opt+1,opt+1+n+m);
	CDQ(1,n+m);
	for(int i=1;i<=cnt;i++) printf("%d\n",ans[i]);
	return 0;
}
