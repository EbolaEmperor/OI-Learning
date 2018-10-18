#include<bits/stdc++.h>
using namespace std;

const int N=100010;
struct Edge{int to,next;} e[N<<1];
int h[N],sum=0,n,m;
int fa[N],size[N],dep[N],hson[N],top[N];
int in[N],out[N],idx[N],clk=0;

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
		dep[v]=dep[u]+1;
		dfs1(v,u);
		size[u]+=size[v];
		if(size[v]>mx) hson[u]=v,mx=size[v];
	}
}

void dfs2(int u,int tp)
{
	top[u]=tp;in[u]=++clk;idx[clk]=u;
	if(hson[u]) dfs2(hson[u],tp);
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
		if(e[tmp].to!=fa[u]&&e[tmp].to!=hson[u])
			dfs2(e[tmp].to,e[tmp].to);
	out[u]=clk;
}

int lca(int u,int v)
{
	while(top[u]!=top[v])
	{
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		u=fa[top[u]];
	}
	if(dep[u]>dep[v]) swap(u,v);
	return u;
}

int mx[N<<2],tag[N<<2];

void pushdown(int o)
{
	mx[o<<1]+=tag[o];
	tag[o<<1]+=tag[o];
	mx[o<<1|1]+=tag[o];
	tag[o<<1|1]+=tag[o];
	tag[o]=0;
}

void Build(int o,int l,int r)
{
	if(l==r){mx[o]=dep[idx[l]];return;}
	int mid=(l+r)/2;
	Build(o<<1,l,mid);
	Build(o<<1|1,mid+1,r);
	mx[o]=max(mx[o<<1],mx[o<<1|1]);
}

void Add(int o,int l,int r,int nl,int nr,int k)
{
	if(l>=nl&&r<=nr)
	{
		mx[o]+=k;
		tag[o]+=k;
		return;
	}
	if(tag[o]) pushdown(o);
	int mid=(l+r)/2;
	if(nl<=mid) Add(o<<1,l,mid,nl,nr,k);
	if(nr>mid) Add(o<<1|1,mid+1,r,nl,nr,k);
	mx[o]=max(mx[o<<1],mx[o<<1|1]);
}

int Max(int o,int l,int r,int nl,int nr)
{
	if(l>=nl&&r<=nr) return mx[o];
	if(tag[o]) pushdown(o);
	int mid=(l+r)/2,res=0;
	if(nl<=mid) res=max(res,Max(o<<1,l,mid,nl,nr));
	if(nr>mid) res=max(res,Max(o<<1|1,mid+1,r,nl,nr));
	return res;
}

int Val(int o,int l,int r,int k)
{
	if(l==r) return mx[o];
	if(tag[o]) pushdown(o);
	int mid=(l+r)/2;
	if(k<=mid) return Val(o<<1,l,mid,k);
	else return Val(o<<1|1,mid+1,r,k);
}

int f[N],ch[N][2];
#define ls ch[x][0]
#define rs ch[x][1]

bool notroot(int y){int x=f[y];return ls==y||rs==y;}
void rotate(int x)
{
	int y=f[x],z=f[y];
	int k=(ch[y][1]==x),w=ch[x][k^1];
	if(notroot(y)) ch[z][ch[z][1]==y]=x;
	ch[x][k^1]=y;ch[y][k]=w;
	if(w) f[w]=y;
	f[x]=z;f[y]=x;
}

void splay(int x)
{
	int y,z;
	while(notroot(x))
	{
		y=f[x];z=f[y];
		if(notroot(y)) rotate((ch[y][0]==x)^(ch[z][0]==y)?x:y);
		rotate(x);
	}
}

void access(int x)
{
	int y=0;
	while(x)
	{
		splay(x);
		if(rs)
		{
			int t=rs;while(ch[t][0]) t=ch[t][0];
			Add(1,1,n,in[t],out[t],1);
		}
		if(f[x])
		{
			int t=x;while(ch[t][0]) t=ch[t][0];
			Add(1,1,n,in[t],out[t],-1);
		}
		rs=y;y=x;x=f[x];
	}
}

int main()
{
	int u,v;
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&u,&v);
		add_edge(u,v);
		add_edge(v,u);
	}
	dep[1]=1;dfs1(1,0);dfs2(1,1);
	Build(1,1,n);
	for(int i=1;i<=n;i++) f[i]=fa[i];
	int opt,x,y;
	while(m--)
	{
		scanf("%d%d",&opt,&x);
		if(opt==1) access(x);
		if(opt==2)
		{
			scanf("%d",&y);
			int vx=Val(1,1,n,in[x]);
			int vy=Val(1,1,n,in[y]);
			int vl=Val(1,1,n,in[lca(x,y)]);
			printf("%d\n",vx+vy-2*vl+1);
		}
		if(opt==3) printf("%d\n",Max(1,1,n,in[x],out[x]));
	}
	return 0;
}
