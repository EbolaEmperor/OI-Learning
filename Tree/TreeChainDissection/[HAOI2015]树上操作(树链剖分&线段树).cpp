#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
struct Edge{int to,next;} e[200010];
int h[100010],sum=0;
int w[100010],idex[100010];
int in[100010],out[100010],dfn=0;
int hson[100010],size[100010];
int top[100010],fa[100010];

int read()
{
	int x=0,fg=1;char ch=getchar();
	while((ch<'0'||ch>'9')&&ch!='-') ch=getchar();
	if(ch=='-') fg=-1,ch=getchar();
	while(ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
	return fg*x;
}

void add_edge(int u,int v){e[++sum].to=v;e[sum].next=h[u];h[u]=sum;}

void dfs1(int u,int la)
{
	size[u]=1;int mx=0;
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		int v=e[tmp].to;
		if(v==la) continue;
		fa[v]=u;dfs1(v,u);
		size[u]+=size[v];
		if(size[v]>mx) hson[u]=v;
		mx=max(mx,size[v]);
	}
}

void dfs2(int u,int tp)
{
	top[u]=tp;
	in[u]=++dfn;idex[dfn]=u;
	if(hson[u]) dfs2(hson[u],tp);
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		if(e[tmp].to==fa[u]||e[tmp].to==hson[u]) continue;
		dfs2(e[tmp].to,e[tmp].to);
	}
	out[u]=dfn;
}

LL val[400010],tag[400010];

void build(int o,int l,int r)
{
	if(l==r){val[o]=w[idex[l]];return;}
	int mid=(l+r)/2;
	build(o*2,l,mid);
	build(o*2+1,mid+1,r);
	val[o]=val[o*2]+val[o*2+1];
}

void add(int o,int l,int r,int nl,int nr,LL k)
{
	if(l>=nl&&r<=nr)
	{
		val[o]+=(r-l+1)*k;
		tag[o]+=k;
		return;
	}
	int mid=(l+r)/2;
	if(nl<=mid) add(o*2,l,mid,nl,nr,k);
	if(nr>mid) add(o*2+1,mid+1,r,nl,nr,k);
	val[o]=val[o*2]+val[o*2+1]+(r-l+1)*tag[o];
}

LL query(int o,int l,int r,int nl,int nr)
{
	if(l==nl&&r==nr) return val[o];
	int mid=(l+r)/2;
	LL res=tag[o]*(nr-nl+1);
	if(nr<=mid) res+=query(o*2,l,mid,nl,nr);
	else if(nl>mid) res+=query(o*2+1,mid+1,r,nl,nr);
	else res+=query(o*2,l,mid,nl,mid)+query(o*2+1,mid+1,r,mid+1,nr);
	return res;
}

int main()
{
	int n=read(),m=read(),u,v;
	for(int i=1;i<=n;i++) w[i]=read();
	for(int i=1;i<n;i++)
	{
		u=read();v=read();
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs1(1,0);
	dfs2(1,1);
	build(1,1,dfn);
	int opt,x,k;
	for(int i=1;i<=m;i++)
	{
		opt=read();x=read();
		if(opt==1)
		{
			k=read();
			add(1,1,dfn,in[x],in[x],(LL)k);
		}
		if(opt==2)
		{
			k=read();
			add(1,1,dfn,in[x],out[x],(LL)k);
		}
		if(opt==3)
		{
			LL ans=0;
			while(top[x]!=1) ans+=query(1,1,dfn,in[top[x]],in[x]),x=fa[top[x]];
			ans+=query(1,1,dfn,1,in[x]);
			printf("%lld\n",ans);
		}
	}
	return 0;
}
