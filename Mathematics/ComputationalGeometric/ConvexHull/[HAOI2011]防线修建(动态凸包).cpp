#include<bits/stdc++.h>
using namespace std;

const int N=100010;
struct PNT
{
	int x,y;
	PNT(int a=0,int b=0):x(a),y(b){}
} p[N];
bool operator < (const PNT &a,const PNT &b){return a.x<b.x||a.x==b.x&&a.y<b.y;}
set<PNT> ch;
set<PNT>::iterator lt,rt,it;
struct OPT
{
	int ty,k;
	OPT(int a=0,int b=0):ty(a),k(b){}
} opt[N<<1];
bool ptc[N];
double ans=0;
double sta[N];
int top=0;

PNT operator - (const PNT &a,const PNT &b){return PNT(a.x-b.x,a.y-b.y);}
double Length(const PNT &a){return sqrt((double)a.x*a.x+a.y*a.y);}
double dist(const PNT &a,const PNT &b){return Length(b-a);}
int Cross(const PNT &a,const PNT &b){return a.x*b.y-a.y*b.x;}

void insert(PNT x)
{
	rt=lt=ch.lower_bound(x);lt--;
	if(Cross(*rt-*lt,x-*lt)<=0) return;
	ans-=dist(*lt,*rt);
	while("STO wzt dalao")
	{
		it=rt;rt++;
		if(Cross(*it-x,*rt-x)<0){rt=it;break;}
		ans-=dist(*it,*rt);
		ch.erase(it);
	}
	while(lt!=ch.begin())
	{
		it=lt;lt--;
		if(Cross(*it-x,*lt-x)>0){lt=it;break;}
		ans-=dist(*it,*lt);
		ch.erase(it);
	}
	ans+=dist(x,*lt)+dist(x,*rt);
	ch.insert(x);
}

int main()
{
	int tot=0,n,m,op,d,k,x,y;
	scanf("%d%d%d",&k,&x,&y);
	p[++tot]=PNT(0,0);ptc[tot]=1;ch.insert(p[tot]);
	p[++tot]=PNT(k,0);ptc[tot]=1;ch.insert(p[tot]);
	p[++tot]=PNT(x,y);ptc[tot]=1;ch.insert(p[tot]);
	ans=dist(p[3],p[1])+dist(p[3],p[2]);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&x,&y);
		p[++tot]=PNT(x,y);
		ptc[tot]=1;
	}
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&op);
		if(op==1)
		{
			scanf("%d",&d);
			opt[i]=OPT(1,d+3);
			ptc[d+3]=0;
		}
		if(op==2) opt[i]=OPT(2,0);
	}
	for(int i=4;i<=tot;i++)
		if(ptc[i]) insert(p[i]);
	for(int i=m;i>=1;i--)
		if(opt[i].ty==2) sta[top++]=ans;
		else insert(p[opt[i].k]);
	while(top>0) printf("%.2lf\n",sta[--top]);
	return 0;
}
