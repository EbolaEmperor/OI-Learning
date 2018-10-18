#include<bits/stdc++.h>
#define ls nd[x].son[0]
#define rs nd[x].son[1]
using namespace std;

struct Node
{
	int son[2],fa;
	int s,mx,r,v;
} nd[30010];
struct Edge{int to,next;} e[60010];
int h[30010],sum=0,n;
char opt[10];

inline void add_edge(int u,int v)
{
	sum++;
	e[sum].to=v;
	e[sum].next=h[u];
	h[u]=sum;
}

void dfs(int u,int fa)
{
	nd[u].fa=fa;
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		if(e[tmp].to==fa) continue;
		dfs(e[tmp].to,u);
	}
}

inline bool nroot(int x){return nd[nd[x].fa].son[0]==x||nd[nd[x].fa].son[1]==x;}
inline void pushr(int x){swap(ls,rs);nd[x].r^=1;}
inline void maintain(int x){nd[x].mx=max(nd[x].v,max(nd[ls].mx,nd[rs].mx));nd[x].s=nd[ls].s+nd[rs].s+nd[x].v;}
inline void pushdown(int x)
{
	if(nd[x].r)
	{
		if(ls) pushr(ls);
		if(rs) pushr(rs);
		nd[x].r=0;
	}
}

void rotate(int x)
{
	int y=nd[x].fa,z=nd[y].fa;
	int k=(nd[y].son[1]==x),w=nd[x].son[k^1];
	if(nroot(y)) nd[z].son[nd[z].son[1]==y]=x;
	nd[x].son[k^1]=y;
	nd[y].son[k]=w;
	if(w) nd[w].fa=y;
	nd[x].fa=z;
	nd[y].fa=x;
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
		if(nroot(y)) rotate((nd[z].son[0]==y)^(nd[y].son[0]==x)?x:y);
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

inline void makeroot(int x){access(x);splay(x);pushr(x);}
inline void split(int x,int y){makeroot(x);access(y);splay(y);}

int main()
{
	int q,x,y;
	cin>>n;
	nd[0].mx=-0x7fffffff;
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&x,&y);
		add_edge(x,y);
		add_edge(y,x);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++) scanf("%d",&nd[i].v);
	cin>>q;
	for(int i=1;i<=q;i++)
	{
		scanf("%s%d%d",opt,&x,&y);
		if(opt[1]=='M'){split(x,y);printf("%d\n",nd[y].mx);}
		if(opt[1]=='S'){split(x,y);printf("%d\n",nd[y].s);}
		if(opt[1]=='H'){makeroot(x);nd[x].v=y;maintain(x);}
	}
	return 0;
}
