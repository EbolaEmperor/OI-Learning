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
	int val,sum;
	int son[2],fa;
	bool flip;
} nd[N];
int sta[N],top=0;

inline bool nroot(int y){int x=nd[y].fa;return ls==y||rs==y;}
inline void maintain(int x){nd[x].sum=nd[ls].sum^nd[rs].sum^nd[x].val;}
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
int find(int x) // 寻找 x 所在的树根
{
	access(x);splay(x);
	while(ls) pushdown(x),x=ls;
	return x;
}
void cut(int x,int y)
{
	makeroot(x);
	if(find(y)==x && nd[x].fa==y && nd[y].son[0]==x && !rs)
		nd[y].son[0]=nd[x].fa=0;
}
void link(int x,int y){makeroot(x);if(find(y)!=x) nd[x].fa=y;}
void split(int x,int y){makeroot(x);access(y);splay(y);}

int main()
{
	int n=read(),m=read(),opt,x,y;
	for(int i=1;i<=n;i++) nd[i].val=read();
	while(m--)
	{
		opt=read();x=read();y=read();
		// split 完之后，x 到 y 的路径在以 y 为根的 splay 树中，且不含其它节点
		if(opt==0) split(x,y),printf("%d\n",nd[y].sum);
		if(opt==1) link(x,y);
		if(opt==2) cut(x,y);
		if(opt==3) splay(x),nd[x].val=y,maintain(x);
	}
	return 0;
}
