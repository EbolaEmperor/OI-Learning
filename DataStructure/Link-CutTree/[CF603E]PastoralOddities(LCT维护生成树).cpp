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

const int N=400010;
int odd = 0, n, m;
struct Node
{
	int val, maxval, maxid;
	int size, imsize;
	int son[2], fa;
	bool flip;
} nd[N];
int sta[N], top=0, tot=0;
bool deleted[N];

struct Edge{
    int u, v, w, id;
    bool operator < (const Edge &rhs) const{
        return w < rhs.w;
    }
} erec[N];
priority_queue<Edge> egs;

inline int max3(int x, int y, int z){return max(max(x,y),z);}

inline bool nroot(int y){int x=nd[y].fa;return ls==y||rs==y;}
inline void maintain(int x){
	nd[x].size = nd[ls].size + nd[rs].size + nd[x].imsize + (x <= n);
    nd[x].maxval = max3(nd[ls].maxval, nd[rs].maxval, nd[x].val);
    if(nd[x].maxval == nd[x].val) nd[x].maxid = x;
    else if(nd[x].maxval == nd[ls].maxval) nd[x].maxid = nd[ls].maxid;
    else nd[x].maxid = nd[rs].maxid;
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
		nd[x].imsize -= nd[y].size;
		nd[x].imsize += nd[rs].size;
		rs=y;
		maintain(x);
		y=x;x=nd[x].fa;
	}
}
void makeroot(int x){access(x);splay(x);pushr(x);}
int find(int x)
{
	access(x);splay(x);
	while(ls) pushdown(x), x = ls;
	splay(x);
	return x;
}
void split(int x,int y){makeroot(x);access(y);splay(y);}
void cut(int x,int y)
{
	split(x, y);
	odd -= nd[y].size & 1;
	nd[y].son[0] = nd[x].fa = 0;
	maintain(y);
	odd += nd[x].size & 1;
	odd += nd[y].size & 1;
}
void link(int x,int y){
	makeroot(x);
	access(y);
	splay(y);
	odd -= nd[x].size & 1;
	odd -= nd[y].size & 1;
	nd[x].fa = y;
	nd[y].imsize += nd[x].size;
	maintain(y);
	odd += nd[y].size & 1;
}

void insertEdge(int u, int v, int w){
	if(find(u) == find(v)){
		split(u, v);
		if(nd[v].maxval <= w) return;
		int e = nd[v].maxid;
		cut(erec[e].u, e);
		cut(e, erec[e].v);
		deleted[e] = true;
	}
	++tot;
	nd[tot].val = nd[tot].maxval = w;
	nd[tot].maxid = tot;
	link(u, tot);
	link(tot, v);
	erec[tot] = (Edge){u, v, w, tot};
	egs.push(erec[tot]);
}

void deleteEdge(){
	if(odd) return;
	while(!egs.empty()){
		auto e = egs.top();
		if(!deleted[e.id]){
			cut(e.u, e.id);
			cut(e.v, e.id);
			if(odd){
				link(e.u, e.id);
				link(e.v, e.id);
				return;
			}
		}
		egs.pop();
	}
}

int main()
{
	n=read(), m=read();
	tot = odd = n;
	for(int i = 1; i <= n; ++i) nd[i].size = 1;
    for(int i = 1; i <= m; ++i){
		int u = read(), v = read(), w = read();
        insertEdge(u, v, w);
		deleteEdge();
		printf("%d\n", odd ? -1 : egs.top().w);
	}
	return 0;
}