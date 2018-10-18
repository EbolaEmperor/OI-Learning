#include<bits/stdc++.h>
using namespace std;

namespace IO
{
	const int S=(1<<20)+5;
	//Input Correlation
	char buf[S],*H,*T;
	inline char Get()
	{
		if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
		if(H==T) return -1;return *H++;
	}
	inline int read()
	{
		int x=0,fg=1;char c=Get();
		while(!isdigit(c)&&c!='-') c=Get();
		if(c=='-') fg=-1,c=Get();
		while(isdigit(c)) x=x*10+c-'0',c=Get();
		return x*fg;
	}
	//Output Correlation
	char obuf[S],*oS=obuf,*oT=oS+S-1,c,qu[55];int qr;
	inline void flush(){fwrite(obuf,1,oS-obuf,stdout);oS=obuf;}
	inline void putc(char x){*oS++ =x;if(oS==oT) flush();}
	template <class I>inline void print(I x)
	{
		if(!x) putc('0');
		if(x<0) putc('-'),x=-x;
		while(x) qu[++qr]=x%10+'0',x/=10;
		while(qr) putc(qu[qr--]);
		putc(' ');
	}
}

using namespace IO;
typedef long long LL;
const int N=100010;
int n;

struct Point
{
	int x,y;
	Point(int _x=0,int _y=0):x(_x),y(_y){}
	friend Point operator - (const Point &a,const Point &b){return Point(a.x-b.x,a.y-b.y);}
	friend LL Cross(const Point &a,const Point &b){return 1ll*a.x*b.y-1ll*a.y*b.x;}
} pnt[N];

struct ConvexHull
{
	vector<Point> ch;
	
	void insert(const Point &a)
	{
		int n=ch.size();
		while(n>1&&Cross(ch[n-1]-ch[n-2],a-ch[n-2])>=0) ch.pop_back(),n--;
		ch.push_back(a);
	}
	void merge(ConvexHull &A){for(int i=0;i<A.ch.size();i++) insert(A.ch[i]);}
	
	bool query(const Point &a,const Point &b)
	{
		Point v=b-a;
		int l=0,r=ch.size()-1,mid;
		while(l<r)
		{
			mid=(l+r)/2;
			if(Cross(ch[mid]-a,v)<Cross(ch[mid+1]-a,v)) r=mid;
			else l=mid+1;
		}
		return Cross(ch[l]-a,v)<0||l+1<ch.size()&&Cross(ch[l+1]-a,v)<0;
	}
} tr[N<<2];

void Build(int o,int l,int r)
{
	tr[o].ch.clear();
	if(l==r)
	{
		tr[o].insert(pnt[l]);
		tr[o].insert(pnt[l+1]);
		return;
	}
	int mid=(l+r)/2;
	Build(o<<1,l,mid);
	Build(o<<1|1,mid+1,r);
	tr[o]=tr[o<<1];
	tr[o].merge(tr[o<<1|1]);
}

int Query(int o,int l,int r,int ql,int qr,Point &a,Point &b)
{
	if(l>=ql&&r<=qr)
	{
		if(!tr[o].query(a,b)) return 0;
		if(l==r) return l;
	}
	int mid=(l+r)/2,res=0;
	if(ql<=mid) res=Query(o<<1,l,mid,ql,qr,a,b);
	if(res) return res;
	if(qr>mid) return Query(o<<1|1,mid+1,r,ql,qr,a,b);
	return 0;
}

int main()
{
	for(int T=read();T;T--)
	{
		n=read();
		for(int i=1;i<=n;i++)
			pnt[i].x=read(),pnt[i].y=read();
		Build(1,1,n-1);
		for(int i=1;i<n;i++)
			print(Query(1,1,n-1,i+1,n-1,pnt[i],pnt[i+1]));
		putc('\n');
	}
	flush();
	return 0;
}
