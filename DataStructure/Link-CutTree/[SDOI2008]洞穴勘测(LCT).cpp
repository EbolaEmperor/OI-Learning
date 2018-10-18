#include<bits/stdc++.h>
#define ls nd[x].son[0]
#define rs nd[x].son[1]
using namespace std;

struct Node
{
	int son[2],fa;
	int r;
} nd[10010];
char opt[10];

inline bool nroot(int y){int x=nd[y].fa;return ls==y||rs==y;}
inline void pushr(int x){swap(ls,rs);nd[x].r^=1;}
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
	nd[y].fa=x;
	nd[x].fa=z;
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
}

void access(int x)
{
	int y=0;
	while(x)
	{
		splay(x);
		rs=y;
		y=x;
		x=nd[x].fa;
	}
}

inline int find(int x){access(x);splay(x);while(ls) pushdown(x),x=ls;return x;}
inline void makeroot(int x){access(x);splay(x);pushr(x);}
inline void split(int x,int y){makeroot(x);access(y);splay(y);}
inline void link(int x,int y){makeroot(x);if(find(y)!=x) nd[x].fa=y;}
inline void cut(int x,int y){makeroot(x);if(find(y)==x&&nd[x].fa==y&&!rs)nd[x].fa=nd[y].son[0]=0;}

int main()
{
	int n,m,x,y;
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		scanf("%s%d%d",opt,&x,&y);
		if(opt[0]=='C') link(x,y);
		if(opt[0]=='D') cut(x,y);
		if(opt[0]=='Q') puts(find(x)==find(y)?"Yes":"No");
	}
	return 0;
}
