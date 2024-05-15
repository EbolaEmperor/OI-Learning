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

const int N=300010;
struct Node
{
	int val, maxval, maxid;
	int son[2],fa;
	bool flip;
} nd[N];
int sta[N],top=0;

struct Edge{
    int u, v, a, b;
    bool operator < (const Edge &rhs) const{
        return a < rhs.a;
    }
} e[N];

inline int max3(int x, int y, int z){return max(max(x,y),z);}

inline bool nroot(int y){int x=nd[y].fa;return ls==y||rs==y;}
inline void maintain(int x){
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
		splay(x);rs=y;
		maintain(x);
		y=x;x=nd[x].fa;
	}
}
void makeroot(int x){access(x);splay(x);pushr(x);}
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

int main()
{
	int n=read(), m=read();
    for(int i = 1; i <= m; ++i)
        e[i].u = read(), e[i].v = read(), e[i].a = read(), e[i].b = read();
    sort(e + 1, e + 1 + m);
    int ans = 0x7fffffff;
    for(int i = 1; i <= m; ++i){
        int u = e[i].u, v = e[i].v, a = e[i].a, b = e[i].b;
        nd[n + i].val = nd[n + i].maxval = b;
        nd[n + i].maxid = n + i;
        makeroot(u);
        if(find(v) != u){
            link(u, n + i);
            link(n + i, v);
        } else if(nd[v].maxval > b){
            int p = nd[v].maxid;
            cut(p, e[p - n].u);
            cut(p, e[p - n].v);
            link(u, n + i);
            link(n + i, v);
        }
        makeroot(1);
        if(find(n) == 1){
            split(1, n);
            ans = min(ans, a + nd[n].maxval);
        }
    }
    cout << (ans == 0x7fffffff ? -1 : ans) << endl;
	return 0;
}