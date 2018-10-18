#include<bits/stdc++.h>
#define INF 0x7f7f7f7f
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
	}
}

inline void upmin(int &x,const int &y){if(y<x) x=y;}
inline int mymin(const int &x,const int &y){return x<y?x:y;}

using namespace IO;
const int N=20010;
struct Edge{int to,capa,next;} e[N<<1];
struct edges
{
	int u,v,w;
	edges(int a=0,int b=0,int c=0):u(a),v(b),w(c){}
	friend bool operator < (const edges &a,const edges &b){return a.w<b.w;}
} eg[N*5];
vector<edges> cross[N];
int h[N],sum=0,n,m,val[N],ans=0;
int dep[N],size[N];
int fa[N],hson[N],top[N];
int dfn[N],idx[N],clk=0;
int mn[N<<2],tag[N<<2];
int fafa[N];

void add_edge(int u,int v,int w)
{
	e[++sum].to=v;
	e[sum].capa=w;
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

inline void pushdown(int o)
{
	upmin(mn[o<<1],tag[o]);
	upmin(mn[o<<1|1],tag[o]);
	upmin(tag[o<<1],tag[o]);
	upmin(tag[o<<1|1],tag[o]);
	tag[o]=INF;
}

void Modify(int o,int l,int r,int nl,int nr,int k)
{
	if(l>=nl&&r<=nr)
	{
		upmin(mn[o],k);
		upmin(tag[o],k);
		return;
	}
	int mid=(l+r)/2;
	if(tag[o]<INF) pushdown(o);
	if(nl<=mid) Modify(o<<1,l,mid,nl,nr,k);
	if(nr>mid) Modify(o<<1|1,mid+1,r,nl,nr,k);
	mn[o]=mymin(mn[o<<1],mn[o<<1|1]);
}

void DFS(int o,int l,int r)
{
	if(l==r){val[idx[l]]=mn[o];return;}
	if(tag[o]<INF) pushdown(o);
	int mid=(l+r)/2;
	DFS(o<<1,l,mid);
	DFS(o<<1|1,mid+1,r);
}

int jump(int x,int k)
{
	int u=x;
	while(dep[x]-dep[top[u]]<k) u=fa[top[u]];
	u=idx[dfn[u]-(k-(dep[x]-dep[u]))];
	return u;
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

void PathModify(int u,int v,int k)
{
	while(top[u]!=top[v])
	{
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		Modify(1,1,n,dfn[top[u]],dfn[u],k);
		u=fa[top[u]];
	}
	if(dep[u]>dep[v]) swap(u,v);
	Modify(1,1,n,dfn[u],dfn[v],k);
}

int find(int x){return fafa[x]==x?x:fafa[x]=find(fafa[x]);}

bool kruskal(int n,int m,bool ty=0)
{
	int cnt=0;
	sort(eg+1,eg+1+m);
	for(int i=1;i<=m;i++)
	{
		int u=eg[i].u,v=eg[i].v;
		u=find(u);v=find(v);
		if(u==v) continue;
		fafa[u]=v;cnt++;
		ans+=eg[i].w;
		if(ty)
		{
			add_edge(eg[i].u,eg[i].v,eg[i].w);
			add_edge(eg[i].v,eg[i].u,eg[i].w);
		}
		if(cnt==n-1) break;
	}
	return cnt==n-1;
}

void clear()
{
	sum=clk=ans=0;
	memset(h,0,sizeof(h));
	memset(mn,0x7f,sizeof(mn));
	memset(tag,0x7f,sizeof(tag));
	memset(hson,0,sizeof(hson));
	for(int i=1;i<=n;i++) cross[i].clear();
}

int main()
{
	for(int T=read();T;T--)
	{
		clear();
		n=read();m=read();
		for(int i=1;i<=m;i++)
		{
			eg[i].u=read();
			eg[i].v=read();
			int d=read(),c=read();
			eg[i].w=d*(1-c);
		}
		for(int i=1;i<=n;i++) fafa[i]=i;
		kruskal(n,m,1);
		dep[1]=1;dfs1(1,0);dfs2(1,1);
		for(int i=1;i<=m;i++)
		{
			int u=eg[i].u,v=eg[i].v,lca=getlca(u,v);
			if(u!=lca&&v!=lca) cross[lca].push_back(eg[i]);
			if(dep[u]-dep[lca]>=2)
			{
				int p=jump(u,dep[u]-dep[lca]-2);
				PathModify(p,u,eg[i].w);
			}
			if(dep[v]-dep[lca]>=2)
			{
				int p=jump(v,dep[v]-dep[lca]-2);
				PathModify(p,v,eg[i].w);
			}
		}
		DFS(1,1,n);
		int save=ans;
		for(int u=1;u<=n;u++)
		{
			int cnt=0,cmt=0;ans=save;
			for(int tmp=h[u];tmp;tmp=e[tmp].next)
			{
				int v=e[tmp].to;
				ans-=e[tmp].capa;
				fafa[v]=v;cnt++;
				if(v!=fa[u]&&val[v]<INF) eg[++cmt]=edges(v,fa[u],val[v]);
			}
			for(int i=0;i<cross[u].size();i++)
			{
				int x=cross[u][i].u,y=cross[u][i].v;
				x=jump(x,dep[x]-dep[u]-1);
				y=jump(y,dep[y]-dep[u]-1);
				eg[++cmt]=edges(x,y,cross[u][i].w);
			}
			if(cnt==0) putc('0'),putc('\n');
			else if(kruskal(cnt,cmt)) print(ans),putc('\n');
			else putc('i'),putc('n'),putc('f'),putc('\n');
		}
	}
	flush();
	return 0;
}
