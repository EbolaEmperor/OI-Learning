#include<bits/stdc++.h>
#define ls nd[x].son[0]
#define rs nd[x].son[1]
using namespace std;

struct Node
{
	int son[2],fa;
	multiset<int> s;
	int mn,r;
} nd[100010];
struct Edge{int to,next;} e[200010];
int h[100010],sum=0;
int w[100010];
char opt[5];

void add_edge(int u,int v)
{
	sum++;
	e[sum].to=v;
	e[sum].next=h[u];
	h[u]=sum;
}

inline bool nrt(int x){return nd[nd[x].fa].son[0]==x||nd[nd[x].fa].son[1]==x;}
inline void pushr(int x){swap(ls,rs);nd[x].r^=1;}
inline void maintain(int x)
{
	nd[x].mn=*(nd[x].s.begin());
	if(ls) nd[x].mn=min(nd[x].mn,nd[ls].mn);
	if(rs) nd[x].mn=min(nd[x].mn,nd[rs].mn);
}
inline void pushdown(int x)
{
	if(nd[x].r)
	{
		if(ls) pushr(ls);
		if(rs) pushr(rs);
		nd[x].r=0;
	}
}

inline void rotate(int x)
{
	int y=nd[x].fa,z=nd[y].fa,k=(nd[y].son[1]==x),w=nd[x].son[k^1];
	if(nrt(y)) nd[z].son[nd[z].son[1]==y]=x;
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
	while(nrt(y)) s.push(nd[y].fa),y=nd[y].fa;
	while(!s.empty()) pushdown(s.top()),s.pop();
	while(nrt(x))
	{
		y=nd[x].fa;
		z=nd[y].fa;
		if(nrt(y))
			rotate((nd[y].son[0]==x)^(nd[z].son[0]==y)?x:y);
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
		if(rs) nd[x].s.insert(nd[rs].mn);
		rs=y;
		if(rs) nd[x].s.erase(nd[x].s.find(nd[rs].mn));
		y=x;
		x=nd[x].fa;
	}
}

inline void makeroot(int x){access(x);splay(x);pushr(x);}

void dfs(int u,int fa)
{
	nd[u].fa=fa;
	nd[u].s.insert(w[u]);
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		if(e[tmp].to==fa) continue;
		dfs(e[tmp].to,u);
		nd[u].s.insert(nd[e[tmp].to].mn);
	}
	maintain(u);
}

int main()
{
	int n,q,u,x;
	cin>>n>>q;
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d",&u,w+i);
		add_edge(u,i);
		add_edge(i,u);
	}
	dfs(1,0);
	for(int i=1;i<=q;i++)
	{
		scanf("%s%d",opt,&x);
		if(opt[0]=='Q')
		{
			access(x);
			splay(x);
			printf("%d\n",*(nd[x].s.begin()));
		}
		if(opt[0]=='V')
		{
			scanf("%d",&u);
			access(x);
			splay(x);
			nd[x].s.erase(nd[x].s.find(w[x]));
			nd[x].s.insert(u);
			w[x]=u;
			maintain(x);
		}
		if(opt[0]=='E') makeroot(x);
	}
	return 0;
}
