#include<bits/stdc++.h>
#define ls nd[x].son[0]
#define rs nd[x].son[1]
using namespace std;

int read()
{
	int x=0;char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	return x;
}

const int N=200010;

namespace BIT{
	int mx, c[N << 1];
	inline int lowbit(int x) {return x&-x;}
	void Add(int p,int x){for(;p<=mx;p+=lowbit(p)) c[p]+=x;}
	int Sum(int p){int res=0;for(;p;p-=lowbit(p)) res+=c[p];return res;}
}

namespace LCT{
	struct Node
	{
		int col, size;
		int son[2], fa;
		bool flip;
	} nd[N];
	int sta[N],top=0;
	int colcnt = 0;

	inline bool nroot(int y){int x=nd[y].fa;return ls==y||rs==y;}
	inline void maintain(int x){
		nd[x].size = nd[ls].size + nd[rs].size + 1;
	}
	inline void pushr(int x){swap(ls,rs);nd[x].flip^=1;}
	inline void pushdown(int x)
	{
		if(nd[x].flip)
		{
			if(ls) pushr(ls);
			if(rs) pushr(rs);
			nd[x].flip=0;
		}
		if(ls) nd[ls].col = nd[x].col;
		if(rs) nd[rs].col = nd[x].col;
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
		int y=x,z;top=0;
		sta[++top]=y;
		while(nroot(y)) y=nd[y].fa,sta[++top]=y;
		while(top) pushdown(sta[top--]);
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
			BIT::Add(nd[x].col, -nd[ls].size-1);
			rs=y;
			maintain(x);
			y=x;x=nd[x].fa;
		}
	}
	void makeroot(int x){
		access(x);
		splay(x);
		nd[x].col = ++colcnt;
		BIT::Add(nd[x].col, nd[x].size);
		pushr(x);
	}
	int find(int x)
	{
		access(x);splay(x);
		while(ls) pushdown(x),x=ls;
		return x;
	}
	void cut(int x,int y)
	{
		makeroot(x);
		if(find(y)==x&&nd[x].fa==y&&!rs){
			nd[y].son[0]=nd[x].fa=0;
			maintain(y);
		}
	}
	void link(int x,int y){makeroot(x);if(find(y)!=x) nd[x].fa=y;}
	void split(int x,int y){makeroot(x);access(y);splay(y);}
	int query(int x){
		splay(x);
		return BIT::Sum(nd[x].col-1) + nd[rs].size + 1;
	}
}

priority_queue<int> topoq;
vector<int> g[N];
int fa[N], topo[N], topocnt = 0, indeg[N];

void dfs(int u){
	for(int v : g[u]){
		if(v == fa[u]) continue;
		fa[v] = u;
		dfs(v);
	}
}

void toposort(int n){
	indeg[n] = g[n].size();
	if(!indeg[n]) topoq.push(n);
	for(int i = 1; i < n; ++i){
		indeg[i] = g[i].size() - 1;
		if(!indeg[i]) topoq.push(-i);
	}
	while(!topoq.empty()){
		int u = -topoq.top();
		topoq.pop();
		topo[u] = ++topocnt;
		if(u != n){
			--indeg[fa[u]];
			if(!indeg[fa[u]]) topoq.push(-fa[u]);
		}
	}
}

int main()
{
	int n=read(), m=read();
	BIT::mx = n + m;
	for(int i = 1; i < n; ++i){
		int u = read(), v = read();
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs(n);
	toposort(n);
	for(int i = 1; i <= n; ++i){
		LCT::nd[i].fa = fa[i];
		LCT::nd[i].col = topo[i];
		LCT::nd[i].size = 1;
		BIT::Add(LCT::nd[i].col, 1);
	}
	LCT::colcnt = n;
	char s[10];
	int u, v;
	while(m--){
		scanf("%s", s);
		if(s[0] == 'u'){
			scanf("%d", &u);
			LCT::makeroot(u);
		} else if(s[0] == 'w'){
			scanf("%d", &u);
			printf("%d\n", LCT::query(u));
		} else {
			scanf("%d%d", &u, &v);
			int ans1 = LCT::query(u);
			int ans2 = LCT::query(v);
			printf("%d\n", ans1 < ans2 ? u : v);
		}
	}
	return 0;
}