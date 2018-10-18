#include<bits/stdc++.h>
#define ls ch[x][0]
#define rs ch[x][1]
using namespace std;

namespace IO
{
	const int S=1<<20;
	//Input Correlation
	char buf[S],*H,*T;
	inline char Get()
	{
		if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
		if(H==T) return -1;return *H++;
	}
	inline int read()
	{
		int x=0;char c=Get();
		while(!isdigit(c)) c=Get();
		while(isdigit(c)) x=x*10+c-'0',c=Get();
		return x;
	}
	//Output Correlation
	char obuf[S],*oS=obuf,*oT=oS+S-1,c,qu[55];int qr;
	inline void flush()
	{
		fwrite(obuf,1,oS-obuf,stdout);
		oS=obuf;
	}
	inline void putc(char x)
	{
		*oS++ =x;
		if(oS==oT) flush();
	}
	template <class I>
	inline void print(I x)
	{
		if(!x) putc('0');
		if(x<0) putc('-'),x=-x;
		while(x) qu[++qr]=x%10+'0',x/=10;
		while(qr) putc(qu[qr--]);
	}
}

using namespace IO;
typedef long long LL;
const int N=50010;
int ch[N][2],fa[N],size[N];
LL val[N],sum[N],ans[N],lsum[N],rsum[N],tag[N];
bool flip[N];
int stk[N],top;

struct Edge{int to,next;} e[N<<1];
int h[N],tot=0;

void add_edge(int u,int v)
{
	e[++tot].to=v;
	e[tot].next=h[u];
	h[u]=tot;
}

void dfs(int u,int la)
{
	fa[u]=la;
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
		if(e[tmp].to!=la) dfs(e[tmp].to,u);
}

inline bool nroot(int x){return ch[fa[x]][0]==x||ch[fa[x]][1]==x;}
inline void pushr(int x){swap(lsum[x],rsum[x]);swap(ls,rs);flip[x]^=1;}
void add(int y,LL k)
{
	val[y]+=k;tag[y]+=k;sum[y]+=k*size[y];
	lsum[y]+=1ll*size[y]*(size[y]+1)/2*k;
	rsum[y]+=1ll*size[y]*(size[y]+1)/2*k;
	ans[y]+=1ll*size[y]*(size[y]+1)*(size[y]+2)/6*k;
}
inline void pushdown(int x)
{
	if(flip[x])
	{
		if(ls) pushr(ls);
		if(rs) pushr(rs);
		flip[x]=0;
	}
	if(tag[x])
	{
		if(ls) add(ls,tag[x]);
		if(rs) add(rs,tag[x]);
		tag[x]=0;
	}
}
inline void maintain(int x)
{
	ans[x]=ans[ls]+lsum[ls]*(size[rs]+1)+ans[rs]+rsum[rs]*(size[ls]+1)+val[x]*(size[ls]+1)*(size[rs]+1);
	lsum[x]=lsum[ls]+val[x]*(size[ls]+1)+lsum[rs]+sum[rs]*(size[ls]+1);
	rsum[x]=rsum[rs]+val[x]*(size[rs]+1)+rsum[ls]+sum[ls]*(size[rs]+1);
	sum[x]=sum[ls]+sum[rs]+val[x];size[x]=size[ls]+size[rs]+1;
}

void rotate(int x)
{
	int y=fa[x],z=fa[y];
	int k=ch[y][1]==x,w=ch[x][k^1];
	if(nroot(y)) ch[z][ch[z][1]==y]=x;
	ch[y][k]=w;ch[x][k^1]=y;
	fa[x]=z;fa[y]=x;
	if(w) fa[w]=y;
	maintain(y);
	maintain(x);
}

void splay(int x)
{
	int y=x,z;
	top=0;stk[++top]=y;
	while(nroot(y)) y=fa[y],stk[++top]=y;
	while(top) pushdown(stk[top--]);
	while(nroot(x))
	{
		y=fa[x];z=fa[y];
		if(nroot(y)) rotate((ch[y][0]==x)^(ch[z][0]==y)?x:y);
		rotate(x);
	}
}

inline void access(int x){for(int y=0;x;y=x,x=fa[x]) splay(x),rs=y,maintain(x);}
inline int find(int x){access(x);splay(x);while(ls) pushdown(x),x=ls;return x;}
inline void makeroot(int x){access(x);splay(x);pushr(x);}
inline void link(int x,int y){makeroot(x);if(find(y)!=x) fa[x]=y;}
inline void cut(int x,int y){makeroot(x);if(find(y)==x&&fa[x]==y&&!rs)ch[y][0]=fa[x]=0;}

LL gcd(LL a,LL b){return b==0?a:gcd(b,a%b);}

int main()
{
	int n,m,opt,x,y,k;
	n=read();m=read();
	for(int i=1;i<=n;i++)
	{
		val[i]=read();
		sum[i]=lsum[i]=rsum[i]=ans[i]=val[i];
		size[i]=1;
	}
	for(int i=1;i<n;i++)
	{
		x=read();y=read();
		add_edge(x,y);
		add_edge(y,x);
	}
	dfs(1,0);
	while(m--)
	{
		opt=read();x=read();y=read();
		if(opt==1) cut(x,y);
		if(opt==2) link(x,y);
		if(opt==3)
		{
			k=read();
			if(find(x)!=find(y)) continue;
			makeroot(x);access(y);splay(y);
			add(y,k);
		}
		if(opt==4)
		{
			if(find(x)!=find(y)) print(-1),putc('\n');
			else
			{
				makeroot(x);access(y);splay(y);
				LL a=ans[y],b=1ll*size[y]*(size[y]+1)/2,g=gcd(a,b);
				print(a/g);putc('/');print(b/g);putc('\n');
			}
		}
	}
	flush();
	return 0;
}
