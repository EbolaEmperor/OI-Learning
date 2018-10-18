#include<bits/stdc++.h>
using namespace std;

const int N=100010;
struct Edge{int to,next;} e[2*N];
int h[N],tot=0,n;
int fa[N],dep[N],top[N];
int size[N],hson[N];
int dfn[N],dfs_clock=0;
int w[N],c[N];

void add_edge(int u,int v){e[++tot].to=v;e[tot].next=h[u];h[u]=tot;}

void dfs1(int u,int la)
{
	size[u]=1;int mx=0;
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		int v=e[tmp].to;
		if(v==la) continue;
		dep[v]=dep[u]+1;
		fa[v]=u;dfs1(v,u);
		size[u]+=size[v];
		if(size[v]>mx) mx=size[v],hson[u]=v;
	}
}

void dfs2(int u,int tp)
{
	dfn[u]=++dfs_clock;top[u]=tp;
	if(hson[u]) dfs2(hson[u],tp);
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		int v=e[tmp].to;
		if(v==fa[u]||v==hson[u]) continue;
		dfs2(v,v);
	}
}

const int P=5000010;
int lc[P],rc[P],sum[P],mx[P];
int root[N],cnt=0;

void modify(int &o,int l,int r,int x,int k)
{
	if(!o) o=++cnt;
	if(l==r){sum[o]=mx[o]=k;return;}
	int mid=(l+r)/2;
	if(x<=mid) modify(lc[o],l,mid,x,k);
	else modify(rc[o],mid+1,r,x,k);
	sum[o]=sum[lc[o]]+sum[rc[o]];
	mx[o]=max(mx[lc[o]],mx[rc[o]]);
}

int Sum(int o,int l,int r,int nl,int nr)
{
	if(l>=nl&&r<=nr) return sum[o];
	int mid=(l+r)/2,res=0;
	if(nl<=mid) res+=Sum(lc[o],l,mid,nl,nr);
	if(nr>mid) res+=Sum(rc[o],mid+1,r,nl,nr);
	return res;
}

int Max(int o,int l,int r,int nl,int nr)
{
	if(l>=nl&&r<=nr) return mx[o];
	int mid=(l+r)/2,ans=0;
	if(nl<=mid) ans=max(ans,Max(lc[o],l,mid,nl,nr));
	if(nr>mid) ans=max(ans,Max(rc[o],mid+1,r,nl,nr));
	return ans;
}

int QSum(int c,int u,int v)
{
	int ans=0;
	while(top[u]!=top[v])
	{
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		ans+=Sum(root[c],1,n,dfn[top[u]],dfn[u]);
		u=fa[top[u]];
	}
	if(dep[u]>dep[v]) swap(u,v);
	ans+=Sum(root[c],1,n,dfn[u],dfn[v]);
	return ans;
}

int QMax(int c,int u,int v)
{
	int ans=0;
	while(top[u]!=top[v])
	{
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		ans=max(ans,Max(root[c],1,n,dfn[top[u]],dfn[u]));
		u=fa[top[u]];
	}
	if(dep[u]>dep[v]) swap(u,v);
	ans=max(ans,Max(root[c],1,n,dfn[u],dfn[v]));
	return ans;
}

int main()
{
	int Q,u,v;
	scanf("%d%d",&n,&Q);
	for(int i=1;i<=n;i++)
		scanf("%d%d",w+i,c+i);
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&u,&v);
		add_edge(u,v);
		add_edge(v,u);
	}
	dep[1]=1;
	dfs1(1,0);
	dfs2(1,1);
	for(int i=1;i<=n;i++)
		modify(root[c[i]],1,n,dfn[i],w[i]);
	char opt[5];
	for(int i=1;i<=Q;i++)
	{
		scanf("%s%d%d",opt,&u,&v);
		if(opt[1]=='C')
		{
			modify(root[c[u]],1,n,dfn[u],0);
			modify(root[v],1,n,dfn[u],w[u]);
			c[u]=v;
		}
		if(opt[1]=='W')
		{
			modify(root[c[u]],1,n,dfn[u],v);
			w[u]=v;
		}
		if(opt[1]=='S') printf("%d\n",QSum(c[u],u,v));
		if(opt[1]=='M') printf("%d\n",QMax(c[u],u,v));
	}
	return 0;
}
