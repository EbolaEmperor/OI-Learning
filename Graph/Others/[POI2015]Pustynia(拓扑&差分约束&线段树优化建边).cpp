#include<bits/stdc++.h>
using namespace std;

namespace IO
{
	const int S=(1<<20)+5;
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
	inline void flush(){fwrite(obuf,1,oS-obuf,stdout);oS=obuf;}
	inline void putc(char x){*oS++ =x;if(oS==oT) flush();}
	template <class I>inline void print(I x)
	{
		if(!x) putc('0');
		if(x<0) putc('-'),x=-x;
		while(x) qu[++qr]=x%10+'0',x/=10;
		while(qr) putc(qu[qr--]);
		putc(' ');
	}
}

inline void upmax(int &x,const int &y){if(y>x) x=y;}

using namespace IO;
const int N=500010,lim=(int)1e9;
struct Edge{int to,capa,next;} e[5000000];
int h[N],sum=0,tot,n,m,s;
int a[N],dis[N],deg[N];
int pnt[N];
bool vis[N];

void add_edge(int u,int v,int w)
{
	e[++sum].to=v;
	e[sum].capa=w;
	e[sum].next=h[u];
	h[u]=sum;
	deg[v]++;
}

void Build(int o,int l,int r)
{
	if(l==r){pnt[o]=l;return;}
	pnt[o]=++tot;
	int mid=(l+r)/2;
	Build(o<<1,l,mid);
	Build(o<<1|1,mid+1,r);
	add_edge(pnt[o<<1],pnt[o],0);
	add_edge(pnt[o<<1|1],pnt[o],0);
}

void link(int o,int l,int r,int nl,int nr,int x)
{
	if(l>=nl&&r<=nr){add_edge(pnt[o],x,0);return;}
	int mid=(l+r)/2;
	if(nl<=mid) link(o<<1,l,mid,nl,nr,x);
	if(nr>mid) link(o<<1|1,mid+1,r,nl,nr,x);
}

void TopoSort()
{
	queue<int> q;
	for(int i=1;i<=tot;i++)
	{
		if(!dis[i]) dis[i]=1;
		if(!deg[i]) q.push(i);
	}
	while(!q.empty())
	{
		int u=q.front();q.pop();vis[u]=1;
		for(int tmp=h[u];tmp;tmp=e[tmp].next)
		{
			int v=e[tmp].to;
			upmax(dis[v],dis[u]+e[tmp].capa);
			if(a[v]&&dis[v]>a[v]) puts("NIE"),exit(0);
			if(! --deg[v]) q.push(v);
		}
	}
}

int main()
{
	int k,x,l,r,pre;
	tot=n=read();s=read();m=read();
	Build(1,1,n);
	for(int i=1;i<=s;i++)
	{
		k=read();x=read();
		a[k]=dis[k]=x;
	}
	for(int i=1;i<=m;i++)
	{
		l=read();r=read();k=read();
		pre=l-1;tot++;
		for(int j=1;j<=k;j++)
		{
			x=read();
			add_edge(tot,x,1);
			if(x>pre+1) link(1,1,n,pre+1,x-1,tot);
			pre=x;
		}
		if(x<r) link(1,1,n,x+1,r,tot);
	}
	TopoSort();
	for(int i=1;i<=tot;i++)
		if(!vis[i]||dis[i]>lim)
		{
			puts("NIE");
			return 0;
		}
	puts("TAK");
	for(int i=1;i<=n;i++) print(dis[i]);
	flush();
	return 0;
}
