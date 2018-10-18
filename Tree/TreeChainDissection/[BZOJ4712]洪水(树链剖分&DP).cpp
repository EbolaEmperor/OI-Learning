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
	template <typename I>inline void read(I &x)
	{
		x=0;char c=Get();
		while(!isdigit(c)) c=Get();
		while(isdigit(c)) x=x*10+c-'0',c=Get();
	}
	//Output Correlation
	char obuf[S],*oS=obuf,*oT=oS+S-1,c,qu[55];int qr;
	inline void flush(){fwrite(obuf,1,oS-obuf,stdout);oS=obuf;}
	inline void putc(char x){*oS++ =x;if(oS==oT) flush();}
	template <typename I>inline void print(I x)
	{
		if(!x) putc('0');
		if(x<0) putc('-'),x=-x;
		while(x) qu[++qr]=x%10+'0',x/=10;
		while(qr) putc(qu[qr--]);
		putc('\n');
	}
}

typedef long long LL;
using namespace IO;

inline LL mymin(const LL &x,const LL &y){return x<y?x:y;}

const int N=200010;
struct Edge{int to,next;} e[N<<1];
int h[N],sum=0,n;
int fa[N],top[N],hson[N];
int dep[N],size[N];
int dfn[N],idx[N],clk=0;
LL v[N],g[N],f[N];

void add_edge(int u,int v)
{
	e[++sum].to=v;
	e[sum].next=h[u];
	h[u]=sum;
}

void dfs1(int u,int la)
{
	size[u]=1;int mx=0;
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		int v=e[tmp].to;
		if(v==la) continue;
		dep[v]=dep[u]+1;
		dfs1(v,u);
		fa[v]=u;
		g[u]+=f[v];
		size[u]+=size[v];
		if(size[v]>mx) mx=size[v],hson[u]=v;
	}
	if(size[u]==1) f[u]=v[u],g[u]=1ll<<60;
	else f[u]=mymin(g[u],v[u]);
}

void dfs2(int u,int tp)
{
	top[u]=tp;idx[dfn[u]=++clk]=u;
	if(hson[u]) dfs2(hson[u],tp);
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
		if(e[tmp].to!=fa[u]&&e[tmp].to!=hson[u])
			dfs2(e[tmp].to,e[tmp].to);
}

LL mindelta[N<<2],minv[N<<2],tag[N<<2];

inline void maintain(const int &o)
{
	mindelta[o]=mymin(mindelta[o<<1],mindelta[o<<1|1]);
	minv[o]=mymin(minv[o<<1],minv[o<<1|1]);
}

inline void pushdown(const int &o)
{
	if(!tag[o]) return;
	mindelta[o<<1]-=tag[o];
	mindelta[o<<1|1]-=tag[o];
	tag[o<<1]+=tag[o];
	tag[o<<1|1]+=tag[o];
	tag[o]=0;
}

void Build(int o,int l,int r)
{
	if(l==r)
	{
		mindelta[o]=v[idx[l]]-g[idx[l]];
		minv[o]=v[idx[l]];
		return;
	}
	int mid=(l+r)/2;
	Build(o<<1,l,mid);
	Build(o<<1|1,mid+1,r);
	maintain(o);
}

LL gQuery(int o,int l,int r,int k)
{
	if(l==r) return minv[o]-mindelta[o];
	pushdown(o);
	int mid=(l+r)/2;
	if(k<=mid) return gQuery(o<<1,l,mid,k);
	else return gQuery(o<<1|1,mid+1,r,k);
}

LL dQuery(int o,int l,int r,int ql,int qr)
{
	if(l>=ql&&r<=qr) return mindelta[o];
	pushdown(o);
	int mid=(l+r)/2;
	if(qr<=mid) return dQuery(o<<1,l,mid,ql,qr);
	else if(ql>mid) return dQuery(o<<1|1,mid+1,r,ql,qr);
	else return mymin(dQuery(o<<1,l,mid,ql,qr),dQuery(o<<1|1,mid+1,r,ql,qr));
}

void Modify(int o,int l,int r,int k)
{
//	cout<<"Modify single node "<<k<<'\n';
	if(l==r)
	{
		mindelta[o]+=v[idx[l]]-minv[o];
		minv[o]=v[idx[l]];
		return;
	}
	pushdown(o);
	int mid=(l+r)/2;
	if(k<=mid) Modify(o<<1,l,mid,k);
	else Modify(o<<1|1,mid+1,r,k);
	maintain(o);
}

void Modify(int o,int l,int r,int ql,int qr,LL c)
{
	if(l>=ql&&r<=qr)
	{
		mindelta[o]-=c;
		tag[o]+=c;
		return;
	}
	pushdown(o);
	int mid=(l+r)/2;
	if(ql<=mid) Modify(o<<1,l,mid,ql,qr,c);
	if(qr>mid) Modify(o<<1|1,mid+1,r,ql,qr,c);
	maintain(o);
}

void Add(int x,LL c)
{
	while(x)
	{
		LL gx=gQuery(1,1,n,dfn[x]);
		LL fx=mymin(gx,v[x]);
		Modify(1,1,n,dfn[x],dfn[x],c);
		if(gx>=v[x]) break;
		if(gx+c>v[x]) c=v[x]-fx,x=fa[x];
		else
		{
			if(top[x]==x){x=fa[x];continue;}
			if(dQuery(1,1,n,dfn[top[x]],dfn[x]-1)>=c)
			{
				Modify(1,1,n,dfn[top[x]],dfn[x]-1,c);
				x=fa[top[x]];
			}
			else
			{
				int l=dfn[top[x]],r=dfn[x],mid;
				while(l<r)
				{
					mid=(l+r)/2;
					if(dQuery(1,1,n,mid,dfn[x]-1)>=c) r=mid;
					else l=mid+1;
				}
				if(r<dfn[x]) Modify(1,1,n,r,dfn[x]-1,c);
				x=idx[r-1];
			}
		}
	}
}

int main()
{
	int x,y;
	read(n);
	for(int i=1;i<=n;i++) read(v[i]);
	for(int i=1;i<n;i++)
	{
		read(x);read(y);
		add_edge(x,y);
		add_edge(y,x);
	}
	dfs1(1,0);dfs2(1,1);
	Build(1,1,n);
	int Q;LL c;char opt;
	for(read(Q);Q;Q--)
	{
		opt=Get();
		while(opt!='Q'&&opt!='C') opt=Get();
		read(x);
		if(opt=='Q') print(mymin(v[x],gQuery(1,1,n,dfn[x])));
		else
		{
			read(c);
			LL gx=gQuery(1,1,n,dfn[x]);
			LL fx=mymin(gx,v[x]);
			v[x]+=c;Modify(1,1,n,dfn[x]);
			if(mymin(v[x],gx)>fx) Add(fa[x],mymin(v[x],gx)-fx);
		}
	}
	flush();
	return 0;
}
