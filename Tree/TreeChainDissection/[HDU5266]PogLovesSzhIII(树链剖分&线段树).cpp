#include<bits/stdc++.h>
#define clear(x) memset((x),0,sizeof (x));
using namespace std;

int read()
{
	int x=0,fg=1;char c=getchar();
	while((c<'0'||c>'9')&&c!='-') c=getchar();
	if(c=='-') fg=-1,c=getchar();
	while(c>='0'&&c<='9') x=x*10+c-'0',c=getchar();
	return fg*x;
}

const int N=300010;
struct Edge{int to,next;} e[2*N];
int h[N],tot=0,n;
int dfn[N],idex[N],clk=0;
int hson[N],size[N];
int fa[N],top[N],dep[N];

void add_edge(int u,int v){e[++tot].to=v;e[tot].next=h[u];h[u]=tot;}

void dfs1(int u)
{
	size[u]=1;int mx=0;
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		int v=e[tmp].to;
		if(v==fa[u]) continue;
		fa[v]=u;dep[v]=dep[u]+1;
		dfs1(v);size[u]+=size[v];
		if(size[v]>mx) mx=size[v],hson[u]=v;
	}
}

void dfs2(int u,int tp)
{
	top[u]=tp;dfn[u]=++clk;idex[clk]=u;
	if(hson[u]) dfs2(hson[u],tp);
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		int v=e[tmp].to;
		if(v==hson[u]||v==fa[u]) continue;
		dfs2(v,v);
	}
}

int LCA(int u,int v)
{
	while(top[u]!=top[v])
	{
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		u=fa[top[u]];
	}
	if(dep[u]>dep[v]) swap(u,v);
	return u;
}

int mn[4*N],mx[4*N];

void build(int o,int l,int r)
{
	if(l==r){mn[o]=mx[o]=dfn[l];return;}
	int mid=(l+r)/2;
	build(o*2,l,mid);
	build(o*2+1,mid+1,r);
	mn[o]=min(mn[o*2],mn[o*2+1]);
	mx[o]=max(mx[o*2],mx[o*2+1]);
}

int Max(int o,int l,int r,int nl,int nr)
{
	if(l>=nl&&r<=nr) return mx[o];
	int mid=(l+r)/2,ans=0;
	if(nl<=mid) ans=max(ans,Max(o*2,l,mid,nl,nr));
	if(nr>mid) ans=max(ans,Max(o*2+1,mid+1,r,nl,nr));
	return ans;
}

int Min(int o,int l,int r,int nl,int nr)
{
	if(l>=nl&&r<=nr) return mn[o];
	int mid=(l+r)/2,ans=N;
	if(nl<=mid) ans=min(ans,Min(o*2,l,mid,nl,nr));
	if(nr>mid) ans=min(ans,Min(o*2+1,mid+1,r,nl,nr));
	return ans;
}

int main()
{
	int u,v;
	while(~scanf("%d",&n))
	{
		tot=clk=0;clear(mn);clear(mx);
		clear(h);clear(dfn);clear(idex);
		clear(hson);clear(size);clear(e);
		clear(fa);clear(top);clear(top);
		for(int i=1;i<n;i++)
		{
			u=read();v=read();
			add_edge(u,v);
			add_edge(v,u);
		}
		dep[1]=1;
		dfs1(1);
		dfs2(1,1);
		build(1,1,n);
		int Q=read();
		while(Q--)
		{
			int l=read(),r=read();
			u=Min(1,1,n,l,r);
			v=Max(1,1,n,l,r);
			printf("%d\n",LCA(idex[u],idex[v]));
		}
	}
	return 0;
}
