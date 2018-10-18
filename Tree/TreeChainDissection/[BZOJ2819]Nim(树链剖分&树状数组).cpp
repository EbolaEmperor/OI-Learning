#include<bits/stdc++.h>
#define lowbit(x) (x&-x)
using namespace std;

const int S=(1<<20)+5;
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

const int N=500010;
struct Edge{int to,next;} e[N<<1];
int h[N],w[N],sum=0,n;
int fa[N],hson[N],size[N],dep[N];
int dfn[N],top[N],clk=0;
int bit[N];

void Add(int p,int x){for(;p<=n;p+=lowbit(p)) bit[p]^=x;}
int Sum(int p){int res=0;for(;p;p-=lowbit(p)) res^=bit[p];return res;}

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
		dfs1(v,u);fa[v]=u;
		size[u]+=size[v];
		if(size[v]>mx) mx=size[v],hson[u]=v;
	}
}

void dfs2(int u,int tp)
{
	top[u]=tp;dfn[u]=++clk;
	if(hson[u]) dfs2(hson[u],tp);
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
		if(e[tmp].to!=fa[u]&&e[tmp].to!=hson[u])
			dfs2(e[tmp].to,e[tmp].to);
}

bool gao(int u,int v)
{
	int res=0;
	while(top[u]!=top[v])
	{
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		res^=Sum(dfn[top[u]]-1)^Sum(dfn[u]);
		u=fa[top[u]];
	}
	if(dep[u]>dep[v]) swap(u,v);
	res^=Sum(dfn[u]-1)^Sum(dfn[v]);
	return res!=0;
}

int main()
{
	int u,v;
	n=read();
	for(int i=1;i<=n;i++) w[i]=read();
	for(int i=1;i<n;i++)
	{
		u=read();v=read();
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs1(1,0);dfs2(1,0);
	for(int i=1;i<=n;i++)
		Add(dfn[i],w[i]);
	int Q=read();char opt;
	while(Q--)
	{
		opt=Get();
		while(opt!='Q'&&opt!='C') opt=Get();
		u=read();v=read();
		if(opt=='Q') puts(gao(u,v)?"Yes":"No");
		else Add(dfn[u],v^w[u]),w[u]=v;
	}
	return 0;
}
