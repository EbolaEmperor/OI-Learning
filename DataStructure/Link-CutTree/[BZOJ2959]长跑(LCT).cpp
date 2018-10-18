#include<bits/stdc++.h>
#define ls nd[x].son[0]
#define rs nd[x].son[1]
using namespace std;

struct Node
{
	int fa,son[2];
	int v,s,r;
} nd[150010];

struct FindingSet
{
	int fa[150010];
	int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
} fs1,fs2;

int sta[150010],top;
int a[150010];

inline bool nroot(int y)
{
	if(nd[y].fa==0) return 0;
	int x=fs2.find(nd[y].fa);
	return rs==y||ls==y;
}
inline void maintain(int x){nd[x].s=nd[ls].s+nd[rs].s+nd[x].v;}
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
	int y=fs2.find(nd[x].fa),z=fs2.find(nd[y].fa);
	int k=(nd[y].son[1]==x),w=nd[x].son[k^1];
	if(y==nd[z].son[0]||y==nd[z].son[1]) nd[z].son[nd[z].son[1]==y]=x;
	nd[x].son[k^1]=y;
	nd[y].son[k]=w;
	if(w) nd[w].fa=y;
	if(y) nd[y].fa=x;
	nd[x].fa=z;
	maintain(y);
	maintain(x);
}

void splay(int x)
{
	int y=x,z;
	top=0;
	sta[++top]=y;
	while(nroot(y)) sta[++top]=nd[y].fa,y=nd[y].fa;
	while(top) pushdown(sta[top--]);
	while(nroot(x))
	{
		y=fs2.find(nd[x].fa);
		z=fs2.find(nd[y].fa);
		if(nroot(nd[x].fa)) rotate((nd[z].son[0]==y)^(nd[y].son[0]==x)?x:nd[x].fa);
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
		x=fs2.find(nd[x].fa);
	}
}

inline void makeroot(int x){access(x);splay(x);pushr(x);}
inline void split(int x,int y){makeroot(x);access(y);splay(y);}

inline void read(int &x)
{
	x=0;
	char c=getchar();
	int fg=1;
	while(c!='-'&&(!(c>='0'&&c<='9'))) c=getchar();
	if(c=='-') fg=-1,c=getchar();
	while(c>='0'&&c<='9') x=x*10+c-'0',c=getchar();
	x*=fg;
}

int dfs(int x,int rt)
{
	if(x==0) return 0;
	fs2.fa[x]=rt;
	return dfs(ls,rt)+dfs(rs,rt)+nd[x].v;
}

int main()
{
	int n,m,opt,x,y;
	read(n);read(m);
	for(int i=1;i<=n;i++)
	{
		read(a[i]);
		nd[i].s=nd[i].v=a[i];
		fs1.fa[i]=fs2.fa[i]=i;
	}
	for(int i=1;i<=m;i++)
	{
		read(opt);read(x);read(y);
		if(opt==1)
		{
			int fx2=fs2.find(x);
			int fy2=fs2.find(y);
			if(fx2!=fy2)
			{
				int fx1=fs1.find(x);
				int fy1=fs1.find(y);
				if(fx1!=fy1)
				{
					makeroot(fx2);
					nd[fx2].fa=fy2;
					fs1.fa[fy1]=fx1;
				}
				else
				{
					split(fx2,fy2);
					nd[fx2].v=dfs(fy2,fx2);
					nd[fx2].fa=nd[fx2].son[0]=nd[fx2].son[1]=0;
					maintain(fx2);
				}
			}
		}
		if(opt==2)
		{
			int fx2=fs2.find(x);
			splay(fx2);
			nd[fx2].v-=a[x];
			a[x]=y;
			nd[fx2].v+=a[x];
			maintain(fx2);
		}
		if(opt==3)
		{
			if(fs1.find(x)!=fs1.find(y)){puts("-1");continue;}
			int fx2=fs2.find(x);
			int fy2=fs2.find(y);
			split(fx2,fy2);
			printf("%d\n",nd[fy2].s);
		}
	}
	return 0;
}
