#include<bits/stdc++.h>
using namespace std;

typedef unsigned int uint;
namespace IO
{
	const int S=1<<20;
	//Input Correlation
	char buf[S],*H,*T;
	inline char Get()
	{
		if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
		if(H==T) return -1;return *H++;
	}
	inline uint read()
	{
		uint x=0;char c=Get();
		while(!isdigit(c)) c=Get();
		while(isdigit(c)) x=x*10+c-'0',c=Get();
		return x;
	}
	inline char reads()
	{
		char c=Get();
		while(c!='R'&&c!='Q') c=Get();
		char res=c;
		while(c>='a'&&c<='z') c=Get();
		return res;
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
		putc('\n');
	}
}

using namespace IO;
const int N=100010;
struct Edge{int to,next;} e[N<<1];
int h[N],sum=0,n,m,K;
int fa[N],dep[N],size[N],hson[N];
int dfn[N],idx[N],top[N],clk=0;
uint val[N];

void add_edge(int u,int v)
{
	e[++sum].to=v;
	e[sum].next=h[u];
	h[u]=sum;
}

void dfs1(int u,int last)
{
	size[u]=1;int mx=0;
	for(int t=h[u];t;t=e[t].next)
	{
		int v=e[t].to;
		if(v==last) continue;
		fa[v]=u;dep[v]=dep[u]+1;
		dfs1(v,u);
		size[u]+=size[v];
		if(size[v]>mx) mx=size[v],hson[u]=v;
	}
}

void dfs2(int u,int tp)
{
	top[u]=tp;dfn[u]=++clk;idx[clk]=u;
	if(hson[u]) dfs2(hson[u],tp);
	for(int t=h[u];t;t=e[t].next)
		if(e[t].to!=fa[u]&&e[t].to!=hson[u])
			dfs2(e[t].to,e[t].to);
}

struct Data
{
	uint val[2];
	Data(uint a=0,uint b=0){val[0]=a;val[1]=b;}
	uint& operator [] (const int &x){return val[x];}
	
	friend Data operator + (Data a,Data b)
	{
		Data res;
		res[0]=(a[0]&b[1])|((~a[0])&b[0]);
		res[1]=(a[1]&b[1])|((~a[1])&b[0]);
		return res;
	}
} tr[N<<2][2];

uint nand(const uint &a,const uint &b){return ~(a&b);}

inline void maintain(int o)
{
	tr[o][0]=tr[o<<1][0]+tr[o<<1|1][0];
	tr[o][1]=tr[o<<1|1][1]+tr[o<<1][1];
}

void Build(int o,int l,int r)
{
	if(l==r)
	{
		tr[o][0]=tr[o][1]=Data(nand(0,val[idx[l]]),nand(~0,val[idx[l]]));
		return;
	}
	int mid=(l+r)/2;
	Build(o<<1,l,mid);
	Build(o<<1|1,mid+1,r);
	maintain(o);
}

void Modify(int o,int l,int r,int k,uint x)
{
	if(l==r)
	{
		tr[o][0]=tr[o][1]=Data(nand(0,x),nand(~0,x));
		return;
	}
	int mid=(l+r)/2;
	if(k<=mid) Modify(o<<1,l,mid,k,x);
	else Modify(o<<1|1,mid+1,r,k,x);
	maintain(o);
}

Data Query(int o,int l,int r,int nl,int nr,bool d)
{
	if(l==nl&&r==nr) return tr[o][d];
	int mid=(l+r)/2;
	if(nr<=mid) return Query(o<<1,l,mid,nl,nr,d);
	else if(nl>mid) return Query(o<<1|1,mid+1,r,nl,nr,d);
	else if(!d) return Query(o<<1,l,mid,nl,mid,d)+Query(o<<1|1,mid+1,r,mid+1,nr,d);
	else return Query(o<<1|1,mid+1,r,mid+1,nr,d)+Query(o<<1,l,mid,nl,mid,d);
}

uint QueryPath(int u,int v)
{
	Data res1,res2;
	res1=res2=Data(0,~0);
	while(top[u]!=top[v])
	{
		if(dep[top[u]]>dep[top[v]])
		{
			res1=res1+Query(1,1,n,dfn[top[u]],dfn[u],1);
			u=fa[top[u]];
		}
		else
		{
			res2=Query(1,1,n,dfn[top[v]],dfn[v],0)+res2;
			v=fa[top[v]];
		}
	}
	if(dep[u]<dep[v]) res2=Query(1,1,n,dfn[u],dfn[v],0)+res2;
	else res1=res1+Query(1,1,n,dfn[v],dfn[u],1);
	res1=res1+res2;
	return res1[0]&((1ll<<K)-1);
}

int main()
{
	uint u,v;
	n=read();m=read();K=read();
	for(int i=1;i<=n;i++) val[i]=read();
	for(int i=1;i<n;i++)
	{
		u=read();v=read();
		add_edge(u,v);
		add_edge(v,u);
	}
	dep[1]=1;dfs1(1,0);dfs2(1,1);
	Build(1,1,n);
	while(m--)
	{
		char opt=reads();u=read();v=read();
		if(opt=='R') Modify(1,1,n,dfn[u],v);
		else print(QueryPath(u,v));
	}
	flush();
	return 0;
}
