#include<bits/stdc++.h>
#define ls nd[x].son[0]
#define rs nd[x].son[1]
using namespace std;

struct Node
{
	int son[2],fa;
	int si,sz,r;
} nd[100010];
char opt[5];

inline bool nroot(int x){return nd[nd[x].fa].son[0]==x||nd[nd[x].fa].son[1]==x;}
inline void pushr(int x){swap(ls,rs);nd[x].r^=1;}
inline void maintain(int x){nd[x].sz=nd[ls].sz+nd[ls].si+nd[rs].sz+nd[rs].si+1;}
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
	int y=nd[x].fa,z=nd[y].fa,k=(nd[y].son[1]==x),w=nd[x].son[k^1];
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
		if(nroot(y))
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
		if(rs) nd[x].si+=nd[rs].si+nd[rs].sz,nd[x].sz-=nd[rs].si+nd[rs].sz;
		rs=y;
		if(rs) nd[x].si-=nd[rs].si+nd[rs].sz,nd[x].sz+=nd[rs].si+nd[rs].sz;
		maintain(x);
		y=x;
		x=nd[x].fa;
	}
}

inline void makeroot(int x){access(x);splay(x);pushr(x);}
inline void link(int x,int y)
{
	makeroot(x);
	makeroot(y);
	nd[x].fa=y;
	nd[y].si+=nd[x].si+nd[x].sz;
	maintain(y);
}
inline void split(int x,int y){makeroot(x);access(y);splay(y);}

int main()
{
	int n,q,u,v;
	cin>>n>>q;
	for(int i=1;i<=n;i++) nd[i].sz=1;
	for(int i=1;i<=q;i++)
	{
		scanf("%s%d%d",opt,&u,&v);
		if(opt[0]=='A') link(u,v);
		else {split(u,v);printf("%lld\n",(long long)(nd[v].si+1)*(nd[u].si+1));}
	}
	return 0;
}
