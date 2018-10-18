#include<bits/stdc++.h>
using namespace std;

const int N=100010;
int sum[N<<2],tag[N<<2];
int n,m,root,ha;
struct Edge{int to,next;} e[N<<1];
int h[N],tot=0,val[N];
int fa[N],top[N],hson[N];
int in[N],out[N],idex[N],clk=0;
int dep[N],size[N];

void Build(int o,int l,int r)
{
	if(l==r){sum[o]=val[idex[l]];return;}
	int mid=(l+r)/2;
	Build(o<<1,l,mid);
	Build(o<<1|1,mid+1,r);
	sum[o]=(sum[o<<1]+sum[o<<1|1])%ha;
}

void Add(int o,int l,int r,int nl,int nr,int x)
{
	if(l>=nl&&r<=nr)
	{
		sum[o]=(sum[o]+1ll*x*(r-l+1))%ha;
		tag[o]=(tag[o]+x)%ha;
		return;
	}
	int mid=(l+r)/2;
	if(nl<=mid) Add(o<<1,l,mid,nl,nr,x);
	if(nr>mid) Add(o<<1|1,mid+1,r,nl,nr,x);
	sum[o]=(sum[o<<1]+sum[o<<1|1]+1ll*tag[o]*(r-l+1))%ha;
}

int Query(int o,int l,int r,int nl,int nr)
{
	if(l==nl&&r==nr) return sum[o];
	int mid=(l+r)/2,res=1ll*tag[o]*(nr-nl+1)%ha;
	if(nr<=mid) res=(res+Query(o<<1,l,mid,nl,nr))%ha;
	else if(nl>mid) res=(res+Query(o<<1|1,mid+1,r,nl,nr))%ha;
	else res=(res+Query(o<<1,l,mid,nl,mid)+Query(o<<1|1,mid+1,r,mid+1,nr))%ha;
	return res;
}

void add_edge(int u,int v)
{
	e[++tot].to=v;
	e[tot].next=h[u];
	h[u]=tot;
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
	top[u]=tp;in[u]=++clk;idex[clk]=u;
	if(hson[u]) dfs2(hson[u],tp);
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		int v=e[tmp].to;
		if(v==fa[u]||v==hson[u]) continue;
		dfs2(v,v);
	}
	out[u]=clk;
}

void PathAdd(int u,int v,int k)
{
	while(top[u]!=top[v])
	{
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		Add(1,1,n,in[top[u]],in[u],k);
		u=fa[top[u]];
	}
	if(dep[u]>dep[v]) swap(u,v);
	Add(1,1,n,in[u],in[v],k);
}

int PathSum(int u,int v)
{
	int ans=0;
	while(top[u]!=top[v])
	{
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		ans=(ans+Query(1,1,n,in[top[u]],in[u]))%ha;
		u=fa[top[u]];
	}
	if(dep[u]>dep[v]) swap(u,v);
	ans=(ans+Query(1,1,n,in[u],in[v]))%ha;
	return ans;
}

int main()
{
	int opt,x,y,z;
	scanf("%d%d%d%d",&n,&m,&root,&ha);
	for(int i=1;i<=n;i++) scanf("%d",val+i);
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		add_edge(x,y);
		add_edge(y,x);
	}
	dep[root]=1;
	fa[root]=root;
	dfs1(root,0);
	dfs2(root,root);
	Build(1,1,n);
	while(m--)
	{
		scanf("%d",&opt);
		if(opt==1)
		{
			scanf("%d%d%d",&x,&y,&z);
			PathAdd(x,y,z%ha);
		}
		if(opt==2)
		{
			scanf("%d%d",&x,&y);
			printf("%d\n",PathSum(x,y));
		}
		if(opt==3)
		{
			scanf("%d%d",&x,&z);
			Add(1,1,n,in[x],out[x],z%ha);
		}
		if(opt==4)
		{
			scanf("%d",&x);
			printf("%d\n",Query(1,1,n,in[x],out[x]));
		}
	}
	return 0;
}
