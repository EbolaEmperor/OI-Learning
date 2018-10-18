#include<bits/stdc++.h>
#define ls nd[x].son[0]
#define rs nd[x].son[1]
#define Mod 51061
using namespace std;

typedef unsigned int uint;
struct Node
{
	int son[2],fa;
	int sz,r;
	uint add,mul,s,v;
} nd[100010];

bool nroot(int y){int x=nd[y].fa;return ls==y||rs==y;}

void maintain(int x)
{
	nd[x].sz=nd[ls].sz+nd[rs].sz+1;
	nd[x].s=(nd[ls].s+nd[rs].s+nd[x].v)%Mod;
}

void modify(int x,uint a,uint m)
{
	if(m!=1)
	{
		nd[x].mul=nd[x].mul*m%Mod;
		nd[x].add=nd[x].add*m%Mod;
		nd[x].v=nd[x].v*m%Mod;
		nd[x].s=nd[x].s*m%Mod;
	}
	if(a!=0)
	{
		nd[x].add=(nd[x].add+a)%Mod;
		nd[x].v=(nd[x].v+a)%Mod;
		nd[x].s=(nd[x].s+(a*nd[x].sz%Mod))%Mod;
	}
}

void pushdown(int x)
{
	if(nd[x].r)
	{
		swap(ls,rs);
		if(ls) nd[ls].r^=1;
		if(rs) nd[rs].r^=1;
		nd[x].r=0;
	}
	if(nd[x].add==0&&nd[x].mul==1) return;
	if(ls) modify(ls,nd[x].add,nd[x].mul);
	if(rs) modify(rs,nd[x].add,nd[x].mul);
	nd[x].add=0;nd[x].mul=1;
}

void rotate(int x)
{
	int y=nd[x].fa,z=nd[y].fa;
	int k=(nd[y].son[1]==x),w=nd[x].son[k^1];
	if(nroot(y)) nd[z].son[nd[z].son[1]==y]=x;
	nd[x].son[k^1]=y;
	nd[y].son[k]=w;
	if(w) nd[w].fa=y;
	nd[y].fa=x;
	nd[x].fa=z;
	maintain(y);
	maintain(x);
}

void splay(int x)
{
	int y=x,z;
	stack<int> s;
	s.push(y);
	while(nroot(y)) s.push(nd[y].fa),y=nd[y].fa;
	while(!s.empty()) pushdown(s.top()),s.pop();
	while(nroot(x))
	{
		y=nd[x].fa;
		z=nd[y].fa;
		if(nroot(y)) rotate((nd[y].son[0]==x)^(nd[z].son[0]==y)?x:y);
		rotate(x);
	}
	maintain(x);
}

void access(int x)
{
	int y=0;
	while(x)
	{
		splay(x);
		rs=y;
		maintain(x);
		y=x;
		x=nd[x].fa;
	}
}

inline int find(int x){access(x);splay(x);while(ls) pushdown(x),x=ls;return x;}
inline void makeroot(int x){access(x);splay(x);nd[x].r^=1;}
inline void split(int x,int y){makeroot(x);access(y);splay(y);}
inline void link(int x,int y){makeroot(x);if(find(y)!=x) nd[x].fa=y;}
inline void cut(int x,int y){makeroot(x);if(find(y)==x&&nd[x].fa==y&&(!rs)) nd[x].fa=nd[y].son[0]=0,maintain(y);}

struct Edge{int to,next;} e[200010];
int h[100010],sum=0;

void add_edge(int u,int v)
{
	sum++;
	e[sum].to=v;
	e[sum].next=h[u];
	h[u]=sum;
}

void dfs(int u,int fa)
{
	nd[u].fa=fa;
	nd[u].sz=1;
	nd[u].mul=1;
	nd[u].v=1;
	nd[u].s=1;
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		if(e[tmp].to==fa) continue;
		dfs(e[tmp].to,u);
	}
}

int main()
{
	int n,q,u,v,x,y;
	uint k;
	char opt[10];
	cin>>n>>q;
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&u,&v);
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs(1,0);
	for(int i=1;i<=q;i++)
	{
		scanf("%s%d%d",opt,&u,&v);
		if(opt[0]=='+') split(u,v),scanf("%d",&k),modify(v,k,1);
		if(opt[0]=='*') split(u,v),scanf("%d",&k),modify(v,0,k);
		if(opt[0]=='-') scanf("%d%d",&x,&y),cut(u,v),link(x,y);
		if(opt[0]=='/') split(u,v),printf("%d\n",nd[v].s);
	}
	return 0;
}
