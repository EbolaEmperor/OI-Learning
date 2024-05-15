#include<bits/stdc++.h>
#define ha 20160501
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
		int x=0;char c=Get();
		while(!isdigit(c)) c=Get();
		while(isdigit(c)) x=x*10+c-'0',c=Get();
		return x;
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

typedef pair<int,int> pii;
using namespace IO;
const int N=1000010;
struct Edge{int to,next;} e[N<<1];
int h[N],esum=0,n,m,val[N];
int fa[N],hson[N],top[N];
int size[N],dep[N];
int dfn[N],idx[N],clk=0;

void add_edge(int u,int v)
{
	e[++esum].to=v;
	e[esum].next=h[u];
	h[u]=esum;
}

void dfs1(int u,int la)
{
	size[u]=1;int mx=0;
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		int v=e[tmp].to;
		if(v==la) continue;
		dep[v]=dep[u]+1;
		dfs1(v,u);fa[v]=u;
		size[u]+=size[v];
		if(size[v]>mx) mx=size[v],hson[u]=v;
	}
}

void dfs2(int u,int tp)
{
	top[u]=tp;idx[dfn[u]=++clk]=u;
	if(hson[u]) dfs2(hson[u],tp);
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
		if(e[tmp].to!=fa[u]&&e[tmp].to!=hson[u])
			dfs2(e[tmp].to,e[tmp].to);
}

int deep[N<<5],deep2[N<<5],sum[N<<5];
int dsum[N<<5],d2sum[N<<5],tag[N<<5];
int root[N],lc[N<<5],rc[N<<5],tot=0,now=0,ptx=0;
struct TRD
{
	int a,b,c;
	TRD(int x=0,int y=0,int z=0):a(x),b(y),c(z){}
	friend TRD operator + (const TRD &x,const TRD &y){return TRD((x.a+y.a)%ha,(x.b+y.b)%ha,(x.c+y.c)%ha);}
};

inline void maintain(int o,int l,int r)
{
	sum[o]=(sum[lc[o]]+sum[rc[o]]+1ll*tag[o]*(r-l+1))%ha;
	dsum[o]=(dsum[lc[o]]+dsum[rc[o]]+1ll*tag[o]*deep[o])%ha;
	d2sum[o]=(d2sum[lc[o]]+d2sum[rc[o]]+1ll*tag[o]*deep2[o])%ha;
}

inline void copynode(int o,int p)
{
	sum[o]=sum[p];
	tag[o]=tag[p];
	deep[o]=deep[p];
	deep2[o]=deep2[p];
	dsum[o]=dsum[p];
	d2sum[o]=d2sum[p];
	lc[o]=lc[p];rc[o]=rc[p];
}

void Build(int &o,int l,int r)
{
	o=++tot;
	if(l==r)
	{
		sum[o]=val[idx[l]];
		deep[o]=dep[idx[l]];
		deep2[o]=1ll*deep[o]*deep[o]%ha;
		dsum[o]=1ll*deep[o]*sum[o]%ha;
		d2sum[o]=1ll*dsum[o]*deep[o]%ha;
		return;
	}
	int mid=(l+r)/2;
	Build(lc[o],l,mid);
	Build(rc[o],mid+1,r);
	maintain(o,l,r);
	deep[o]=(deep[lc[o]]+deep[rc[o]])%ha;
	deep2[o]=(deep2[lc[o]]+deep2[rc[o]])%ha;
}

void Modify(int &o,int pre,int l,int r,int nl,int nr,int k)
{
	if(!o) copynode(o=++tot,pre);
	if(l==nl&&r==nr)
	{
		sum[o]=(sum[o]+1ll*k*(nr-nl+1))%ha;
		dsum[o]=(dsum[o]+1ll*k*deep[o])%ha;
		d2sum[o]=(d2sum[o]+1ll*k*deep2[o])%ha;
		tag[o]=(tag[o]+k)%ha;
		return;
	}
	int mid=(l+r)/2;
	if(nr<=mid)
	{
		if(lc[o]==lc[pre]) lc[o]=0;
		Modify(lc[o],lc[pre],l,mid,nl,nr,k);
	}
	else if(nl>mid)
	{
		if(rc[o]==rc[pre]) rc[o]=0;
		Modify(rc[o],rc[pre],mid+1,r,nl,nr,k);
	}
	else
	{
		if(lc[o]==lc[pre]) lc[o]=0;
		Modify(lc[o],lc[pre],l,mid,nl,mid,k);
		if(rc[o]==rc[pre]) rc[o]=0;
		Modify(rc[o],rc[pre],mid+1,r,mid+1,nr,k);
	}
	maintain(o,l,r);
}

TRD Query(int o,int l,int r,int nl,int nr,int d)
{
	if(l==nl&&r==nr) return TRD((sum[o]+1ll*d*(r-l+1))%ha,(dsum[o]+1ll*d*deep[o])%ha,(d2sum[o]+1ll*d*deep2[o])%ha);
	int mid=(l+r)/2;d=(d+tag[o])%ha;
	if(nr<=mid) return Query(lc[o],l,mid,nl,nr,d);
	else if(nl>mid) return Query(rc[o],mid+1,r,nl,nr,d);
	else
	{
		TRD res1=Query(lc[o],l,mid,nl,mid,d);
		TRD res2=Query(rc[o],mid+1,r,mid+1,nr,d);
		return res1+res2;
	}
}

void PathModify(int u,int v,int d)
{
	ptx++;
	while(top[u]!=top[v])
	{
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		Modify(root[ptx],root[now],1,n,dfn[top[u]],dfn[u],d);
		u=fa[top[u]];
	}
	if(dep[u]>dep[v]) swap(u,v);
	Modify(root[ptx],root[now],1,n,dfn[u],dfn[v],d);
	now=ptx;
}

int getlca(int u,int v)
{
	while(top[u]!=top[v])
	{
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		u=fa[top[u]];
	}
	if(dep[u]>dep[v]) swap(u,v);
	return u;
}

int PathQuery(int u,int v)
{
	int lca=getlca(u,v),t2=dep[v];
	int t1=(dep[v]-2*dep[lca]+ha)%ha;
	int ans=0;TRD res;
	while(top[u]!=top[v])
	{
		if(dep[top[u]]>=dep[top[v]])
		{
			res=Query(root[now],1,n,dfn[top[u]],dfn[u],0);
			ans=(ans+1ll*res.a*(1ll*t1*t1%ha+t1))%ha;
			ans=(ans+1ll*res.b*(2ll*t1+1)+res.c)%ha;
			u=fa[top[u]];
		}
		else
		{
			res=Query(root[now],1,n,dfn[top[v]],dfn[v],0);
			ans=(ans+1ll*res.a*(1ll*t2*t2%ha+t2))%ha;
			ans=(ans-1ll*res.b*(2ll*t2+1)%ha+res.c+ha)%ha;
			v=fa[top[v]];
		}
	}
	if(dep[u]>=dep[v])
	{
		res=Query(root[now],1,n,dfn[v],dfn[u],0);
		ans=(ans+1ll*res.a*(1ll*t1*t1%ha+t1))%ha;
		ans=(ans+1ll*res.b*(2ll*t1+1)+res.c)%ha;
	}
	else
	{
		res=Query(root[now],1,n,dfn[u],dfn[v],0);
		ans=(ans+1ll*res.a*(1ll*t2*t2%ha+t2))%ha;
		ans=(ans-1ll*res.b*(2ll*t2+1)%ha+res.c+ha)%ha;
	}
	return 10080251ll*ans%ha;
}

int main()
{
	int u,v,opt,x,y,d,lastans=0;
	n=read();m=read();
	for(int i=1;i<n;i++)
	{
		u=read();v=read();
		add_edge(u,v);
		add_edge(v,u);
	}
	for(int i=1;i<=n;i++) val[i]=read();
	dep[1]=1;dfs1(1,0);dfs2(1,1);
	Build(root[0],1,n);
	while(m--)
	{
		opt=read();x=read();
		if(opt==3) now=x^lastans;
		if(opt==1)
		{
			y=read();d=read();
			x^=lastans;
			y^=lastans;
			PathModify(x,y,d);
		}
		if(opt==2)
		{
			y=read();
			x^=lastans;
			y^=lastans;
			lastans=PathQuery(x,y);
			print(lastans);
		}
	}
	flush();
	return 0;
}
