#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
using namespace std;

const int N=30010;
struct Edge{int to,next;} e[2*N];
int h[N],tot=0,n;
int fa[N],top[N],hson[N];
int dep[N],size[N],w[N];
int dfn[N],dfs_clock=0,idex[N];

void add_edge(int u,int v){e[++tot].to=v;e[tot].next=h[u];h[u]=tot;}

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
		if(size[v]>mx) hson[u]=v,mx=size[v];
	}
}

void dfs2(int u,int tp)
{
	dfn[u]=++dfs_clock;
	idex[dfs_clock]=u;top[u]=tp;
	if(hson[u]) dfs2(hson[u],tp);
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		int v=e[tmp].to;
		if(v==fa[u]||v==hson[u]) continue;
		dfs2(v,v);
	}
}

int sum[N*4],mx[N*4];

void build(int o,int l,int r)
{
	if(l==r){sum[o]=mx[o]=w[idex[l]];return;}
	int mid=(l+r)/2;
	build(o*2,l,mid);
	build(o*2+1,mid+1,r);
	sum[o]=sum[o*2]+sum[o*2+1];
	mx[o]=max(mx[o*2],mx[o*2+1]);
}

void change(int o,int l,int r,int x,int k)
{
	if(l==r){sum[o]=mx[o]=k;return;}
	int mid=(l+r)/2;
	if(x<=mid) change(o*2,l,mid,x,k);
	else change(o*2+1,mid+1,r,x,k);
	sum[o]=sum[o*2]+sum[o*2+1];
	mx[o]=max(mx[o*2],mx[o*2+1]);
}

int Sum(int o,int l,int r,int nl,int nr)
{
	if(l>=nl&&r<=nr) return sum[o];
	int mid=(l+r)/2,res=0;
	if(nl<=mid) res+=Sum(o*2,l,mid,nl,nr);
	if(nr>mid) res+=Sum(o*2+1,mid+1,r,nl,nr);
	return res;
}

int Max(int o,int l,int r,int nl,int nr)
{
	if(l>=nl&&r<=nr) return mx[o];
	int mid=(l+r)/2,ans=-INF;
	if(nl<=mid) ans=max(ans,Max(o*2,l,mid,nl,nr));
	if(nr>mid) ans=max(ans,Max(o*2+1,mid+1,r,nl,nr));
	return ans;
}

int QSum(int u,int v)
{
	int ans=0;
	while(top[u]!=top[v])
	{
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		ans+=Sum(1,1,n,dfn[top[u]],dfn[u]);
		u=fa[top[u]];
	}
	if(dep[u]>dep[v]) swap(u,v);
	ans+=Sum(1,1,n,dfn[u],dfn[v]);
	return ans;
}

int QMax(int u,int v)
{
	int ans=-INF;
	while(top[u]!=top[v])
	{
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		ans=max(ans,Max(1,1,n,dfn[top[u]],dfn[u]));
		u=fa[top[u]];
	}
	if(dep[u]>dep[v]) swap(u,v);
	ans=max(ans,Max(1,1,n,dfn[u],dfn[v]));
	return ans;
}

int main()
{
	int a,b;
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&a,&b);
		add_edge(a,b);
		add_edge(b,a);
	}
	dep[1]=1;
	dfs1(1,0);
	dfs2(1,1);
	for(int i=1;i<=n;i++) scanf("%d",w+i);
	build(1,1,n);
	int Q;scanf("%d",&Q);
	char opt[10];
	while(Q--)
	{
		scanf("%s%d%d",opt,&a,&b);
		if(opt[1]=='H') change(1,1,n,dfn[a],b);
		if(opt[1]=='S') printf("%d\n",QSum(a,b));
		if(opt[1]=='M') printf("%d\n",QMax(a,b));
	}
	return 0;
}
