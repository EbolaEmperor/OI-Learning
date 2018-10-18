#include<bits/stdc++.h>
using namespace std;

typedef unsigned long long ULL;
const int N=100010;
const ULL mx=-1;
int n,m,k;
struct Edge{int to,next;} e[N<<1];
int h[N],sum=0;
struct Node{int opt;ULL v;} p[N];
struct node{ULL v0,v1,w0,w1;} t[N<<2],ans1[N],ans2[N];
int fa[N],hson[N],size[N],dep[N];
int top[N],dfn[N],idx[N],clk=0;

ULL operator + (const ULL &a,const Node &b)
{
	if(b.opt==1) return a&b.v;
	if(b.opt==2) return a|b.v;
	if(b.opt==3) return a^b.v;
}

void add_edge(int u,int v)
{
	e[++sum].to=v;
	e[sum].next=h[u];
	h[u]=sum;
}

void dfs1(int u,int la)
{
	fa[u]=la;size[u]=1;int mx=0;
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		int v=e[tmp].to;
		if(v==la) continue;
		dep[v]=dep[u]+1;dfs1(v,u);
		size[u]+=size[v];
		if(size[v]>mx) hson[u]=v,mx=size[v];
	}
}

void dfs2(int u,int tp)
{
	dfn[u]=++clk;idx[clk]=u;top[u]=tp;
	if(hson[u]) dfs2(hson[u],tp);
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
		if(e[tmp].to!=fa[u]&&e[tmp].to!=hson[u])
			dfs2(e[tmp].to,e[tmp].to);
}

node operator + (const node &a,const node &b)
{
	node ans;
	ans.v0=(a.v0&b.v1)|((~a.v0)&b.v0);
	ans.v1=(a.v1&b.v1)|((~a.v1)&b.v0);
	ans.w0=(b.w0&a.w1)|((~b.w0)&a.w0);
	ans.w1=(b.w1&a.w1)|((~b.w1)&a.w0);
	return ans;
}

void Build(int o,int l,int r)
{
	if(l==r)
	{
		t[o].v0=t[o].w0=0+p[idx[l]];
		t[o].v1=t[o].w1=mx+p[idx[l]];
		return;
	}
	int mid=(l+r)/2;
	Build(o<<1,l,mid);
	Build(o<<1|1,mid+1,r);
	t[o]=t[o<<1]+t[o<<1|1];
}

void Modify(int o,int l,int r,int k,Node x)
{
	if(l==r)
	{
		t[o].v0=t[o].w0=0+x;
		t[o].v1=t[o].w1=mx+x;
		return;
	}
	int mid=(l+r)/2;
	if(k<=mid) Modify(o<<1,l,mid,k,x);
	else Modify(o<<1|1,mid+1,r,k,x);
	t[o]=t[o<<1]+t[o<<1|1];
}

node Query(int o,int l,int r,int nl,int nr)
{
	if(l==nl&&r==nr) return t[o];
	int mid=(l+r)/2;node ans;
	if(nr<=mid) ans=Query(o<<1,l,mid,nl,nr);
	else if(nl>mid) ans=Query(o<<1|1,mid+1,r,nl,nr);
	else ans=Query(o<<1,l,mid,nl,mid)+Query(o<<1|1,mid+1,r,mid+1,nr);
	return ans;
}

node PathQry(int u,int v)
{
	int cnt1=0,cnt2=0;
	while(top[u]!=top[v])
		if(dep[top[u]]<dep[top[v]])
		{
			ans2[++cnt2]=Query(1,1,n,dfn[top[v]],dfn[v]);
			v=fa[top[v]];
		}
		else
		{
			ans1[++cnt1]=Query(1,1,n,dfn[top[u]],dfn[u]);
			u=fa[top[u]];
		}
	if(dep[u]<dep[v]) ans2[++cnt2]=Query(1,1,n,dfn[u],dfn[v]);
	else ans1[++cnt1]=Query(1,1,n,dfn[v],dfn[u]);
	for(int i=1;i<=cnt1;i++) swap(ans1[i].v0,ans1[i].w0),swap(ans1[i].v1,ans1[i].w1);
	node ans;
	if(cnt1)
	{
		ans=ans1[1];
		for(int i=2;i<=cnt1;i++)
			ans=ans+ans1[i];
		if(cnt2) ans=ans+ans2[cnt2];
	}
	else ans=ans2[cnt2];
	for(int i=cnt2-1;i>=1;i--)
		ans=ans+ans2[i];
	return ans;
}

int main()
{
	int u,v,opt;ULL z;
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++)
		scanf("%d%llu",&p[i].opt,&p[i].v);
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&u,&v);
		add_edge(u,v);
		add_edge(v,u);
	}
	dep[1]=1;dfs1(1,0);dfs2(1,1);
	Build(1,1,n);
	while(m--)
	{
		scanf("%d%d%d%llu",&opt,&u,&v,&z);
		if(opt==2) Modify(1,1,n,dfn[u],Node{v,z});
		else
		{
			node ans=PathQry(u,v);ULL res=0;
			for(int i=63;i>=0;i--)
			{
				ULL t0=(ans.v0>>i)&1,t1=(ans.v1>>i)&1;
				if(t0>=t1||(1ull<<i)>z) res|=t0?(1ull<<i):0;
				else res|=t1?(1ull<<i):0,z-=1ull<<i;
			}
			printf("%llu\n",res);
		}
	}
	return 0;
}
