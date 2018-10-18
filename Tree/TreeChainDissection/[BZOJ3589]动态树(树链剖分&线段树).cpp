#include<bits/stdc++.h>
#define INF 0x7fffffff
using namespace std;

int read()
{
	int x=0;char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	return x;
}

const int N=200010;
struct Edge{int to,next;} e[N<<1];
int h[N],tot=0;
int fa[N],top[N],hson[N],size[N],dep[N];
int in[N],out[N],idex[N],dfn=0;

void add_edge(int u,int v)
{
	e[++tot].to=v;
	e[tot].next=h[u];
	h[u]=tot;
}

void dfs1(int u,int f)
{
	size[u]=1;int mx=0;
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		int v=e[tmp].to;
		if(v==f) continue;
		dep[v]=dep[u]+1;
		fa[v]=u;dfs1(v,u);
		size[u]+=size[v];
		if(size[v]>mx) mx=size[v],hson[u]=v;
	}
}

void dfs2(int u,int tp)
{
	top[u]=tp;in[u]=++dfn;idex[dfn]=u;
	if(hson[u]) dfs2(hson[u],tp);
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		int v=e[tmp].to;
		if(v==fa[u]||v==hson[u]) continue;
		dfs2(v,v);
	}
	out[u]=dfn;
}

int val[N<<2],sum[N<<2],add[N<<2],mdf[N<<2];

void pushdown(int o,int l,int r)
{
	if(add[o])
	{
		int mid=(l+r)/2;
		sum[o*2]+=add[o]*(mid-l+1);
		sum[o*2+1]+=add[o]*(r-mid);
		add[o*2]+=add[o];
		add[o*2+1]+=add[o];
		add[o]=0;
	}
	if(~mdf[o])
	{
		val[o*2]=sum[o*2]*mdf[o];
		val[o*2+1]=sum[o*2+1]*mdf[o];
		mdf[o*2]=mdf[o*2+1]=mdf[o];
		mdf[o]=-1;
	}
}

void maintain(int o)
{
	sum[o]=sum[o*2]+sum[o*2+1];
	val[o]=val[o*2]+val[o*2+1];
}

void Modify(int o,int l,int r,int nl,int nr,int ty)
{
	if(l>=nl&&r<=nr)
	{
		val[o]=ty*sum[o];
		mdf[o]=ty;
		return;
	}
	pushdown(o,l,r);
	int mid=(l+r)/2;
	if(nl<=mid) Modify(o*2,l,mid,nl,nr,ty);
	if(nr>mid) Modify(o*2+1,mid+1,r,nl,nr,ty);
	maintain(o);
}

void Add(int o,int l,int r,int nl,int nr,int k)
{
	if(l>=nl&&r<=nr)
	{
		sum[o]+=k*(r-l+1);
		add[o]+=k;
		return;
	}
	pushdown(o,l,r);
	int mid=(l+r)/2;
	if(nl<=mid) Add(o*2,l,mid,nl,nr,k);
	if(nr>mid) Add(o*2+1,mid+1,r,nl,nr,k);
	maintain(o);
}

void Modify(int u,int v)
{
	while(top[u]!=top[v])
	{
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		Modify(1,1,dfn,in[top[u]],in[u],1);
		u=fa[top[u]];
	}
	if(dep[u]>dep[v]) swap(u,v);
	Modify(1,1,dfn,in[u],in[v],1);
}

int main()
{
	int n=read(),u,v,opt,k;
	for(int i=1;i<n;i++)
	{
		u=read();v=read();
		add_edge(u,v);
		add_edge(v,u);
	}
	dep[1]=1;dfs1(1,0);dfs2(1,1);
	int Q=read();
	while(Q--)
	{
		opt=read();
		if(opt==0)
		{
			u=read();k=read();
			Add(1,1,n,in[u],out[u],k);
		}
		else
		{
			k=read();
			for(int i=1;i<=k;i++)
			{
				u=read();v=read();
				Modify(u,v);
			}
			printf("%d\n",val[1]&INF);
			Modify(1,1,n,1,n,0);
		}
	}
	return 0;
}
