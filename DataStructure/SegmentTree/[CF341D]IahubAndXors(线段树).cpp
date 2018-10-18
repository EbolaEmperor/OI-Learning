#include<bits/stdc++.h>
#define lowbit(x) (x&-x)
using namespace std;

typedef long long LL;
const int N=100010;
struct OPT
{
	int ty,x,y1,y2,id;LL c;
	OPT(int _ty=0,int _x=0,int _y1=0,int _y2=0,LL _c=0,int _id=0):
		ty(_ty),x(_x),y1(_y1),y2(_y2),c(_c),id(_id){}
	friend bool operator < (const OPT &a,const OPT &b)
	{
		if(a.x!=b.x) return a.x<b.x;
		if(a.ty!=b.ty) return a.ty<b.ty;
		if(a.y1!=b.y1) return a.y1<b.y1;
		return a.y2<b.y2;
	}
} p[N<<1];
LL val[4010],tag[4010];
LL ans[N];

void Add(int o,int l,int r,int nl,int nr,LL c)
{
	if(l==nl&&r==nr)
	{
		if((r-l+1)&1) val[o]^=c;
		tag[o]^=c;return;
	}
	int mid=(l+r)/2;
	if(nr<=mid) Add(o<<1,l,mid,nl,nr,c);
	else if(nl>mid) Add(o<<1|1,mid+1,r,nl,nr,c);
	else Add(o<<1,l,mid,nl,mid,c),Add(o<<1|1,mid+1,r,mid+1,nr,c);
	val[o]=val[o<<1]^val[o<<1|1];
}

LL Sum(int o,int l,int r,int nl,int nr)
{
	if(l==nl&&r==nr) return val[o];
	int mid=(l+r)/2;LL res=0;
	if((nr-nl+1)&1) res=tag[o];
	if(nr<=mid) res^=Sum(o<<1,l,mid,nl,nr);
	else if(nl>mid) res^=Sum(o<<1|1,mid+1,r,nl,nr);
	else res^=Sum(o<<1,l,mid,nl,mid)^Sum(o<<1|1,mid+1,r,mid+1,nr);
	return res;
}

int main()
{
	int n,m,cnt=0,qry=0,ty,x1,x2,y1,y2;LL c;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d%d%d",&ty,&x1,&y1,&x2,&y2);
		x1++;y1++;x2++;y2++;
		if(ty==1)
		{
			qry++;
			p[++cnt]=OPT(2,x1-1,y1,y2,0,qry);
			p[++cnt]=OPT(2,x2,y1,y2,0,qry);
		}
		else
		{
			scanf("%lld",&c);
			p[++cnt]=OPT(1,x1,y1,y2,c);
			p[++cnt]=OPT(1,x2+1,y1,y2,c);
		}
	}
	sort(p+1,p+1+cnt);
	for(int i=1;i<=cnt;i++)
		if(p[i].ty==1) Add(1,1,1002,p[i].y1,p[i].y2,p[i].c);
		else ans[p[i].id]^=Sum(1,1,1002,p[i].y1,p[i].y2);
	for(int i=1;i<=qry;i++) printf("%lld\n",ans[i]);
	return 0;
}
