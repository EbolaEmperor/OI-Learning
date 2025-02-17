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

int bit[500010],n;

void Add(int p,int k){for(;p<=n;p+=lowbit(p))bit[p]+=k;}
int Sum(int p){int res=0;for(;p>0;p-=lowbit(p))res+=bit[p];return res;}

struct OPT{int x,y1,y2,k,ty,id;} opt[400010];
int ans[200010];

bool operator < (const OPT &a,const OPT &b){return a.x<b.x||(a.x==b.x&&a.ty<b.ty);}

void CDQ(int L,int R)
{
	if(L==R) return;
	int M=(L+R)/2;
	CDQ(L,M);CDQ(M+1,R);
	sort(opt+L,opt+M+1);
	sort(opt+M+1,opt+R+1);
	int p1=L,p2=M+1,lst=0;
	while(p2<=R)
	{
		while(p1<=M&&opt[p1].ty!=1) p1++;
		while(p2<=R&&opt[p2].ty==1) p2++;
		if(p1<=M&&opt[p1].x<=opt[p2].x)
			Add(opt[p1].y1,opt[p1].k),lst=p1++;
		else if(p2<=R)
		{
			int fg=(opt[p2].ty==2)?-1:1;
			ans[opt[p2].id]+=fg*(Sum(opt[p2].y2)-Sum(opt[p2].y1));
			p2++;
		}
	}
	for(int i=L;i<=lst;i++)
		if(opt[i].ty==1) Add(opt[i].y1,-opt[i].k);
}

int main()
{
	n=read();
	int cnt=0,op=0,idex=0;
	while(op!=3)
	{
		cnt++;
		op=read();
		if(op==1)
		{
			opt[cnt].x=read();
			opt[cnt].y1=read();
			opt[cnt].k=read();
			opt[cnt].ty=1;
		}
		else if(op==2)
		{
			opt[cnt].x=read()-1;
			opt[cnt].y1=opt[cnt+1].y1=read()-1;
			opt[cnt+1].x=read();
			opt[cnt].y2=opt[cnt+1].y2=read();
			opt[cnt].ty=2;
			opt[cnt+1].ty=3;
			opt[cnt].id=opt[cnt+1].id=++idex;
			cnt++;
		}
	}
	CDQ(1,cnt);
	for(int i=1;i<=idex;i++) printf("%d\n",ans[i]);
	return 0;
}
