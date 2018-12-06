#include<bits/stdc++.h>
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
	inline void flush(){fwrite(obuf,1,oS-obuf,stdout);oS=obuf;}
	inline void putc(char x){*oS++ =x;if(oS==oT) flush();}
	template <class I>inline void print(I x)
	{
		if(!x) putc('0');
		if(x<0) putc('-'),x=-x;
		while(x) qu[++qr]=x%10+'0',x/=10;
		while(qr) putc(qu[qr--]);
		putc('\n');
	}
	inline void prints(char *s)
	{
		int n=strlen(s);
		for(int i=0;i<n;i++) putc(s[i]);
		putc('\n');
	}
}

using namespace IO;
const int N=100010;
struct Edge{int to,next;} e[N<<2];
int h[N],sum,ans,n,m,cs=0;
int low[N],pre[N],clk;
int fa[N],f[N];

int find(int x){return f[x]==x?x:f[x]=find(f[x]);}

void add_edge(int u,int v)
{
	e[++sum].to=v;
	e[sum].next=h[u];
	h[u]=sum;
}

void Tarjan(int u,int last)
{
	low[u]=pre[u]=++clk;
	for(int t=h[u];t;t=e[t].next)
	{
		int v=e[t].to;
		if(!pre[v])
		{
			Tarjan(v,u);fa[v]=u;
			low[u]=min(low[u],low[v]);
			if(low[v]>pre[u]) ans++;
			else if(find(u)!=find(v)) f[find(v)]=find(u);
		}
		else if(pre[v]<pre[u]&&v!=last)
			low[u]=min(low[u],pre[v]);
	}
}

void gao(int u,int v)
{
	if(find(u)==find(v)) return;
	if(pre[u]<pre[v]) swap(u,v);
	while(pre[u]>pre[v])
	{
		if(find(u)!=find(fa[u]))
			ans--,f[find(u)]=find(fa[u]);
		u=fa[u];
	}
	while(u!=v)
	{
		if(find(v)!=find(fa[v]))
			ans--,f[find(v)]=find(fa[v]);
		v=fa[v];
	}
}

int main()
{
	n=read();m=read();
	while(n&&m)
	{
		static char cas[10];
		sprintf(cas,"Case %d:",++cs);
		prints(cas);
		int u,v;sum=ans=clk=0;
		memset(h,0,sizeof(h));
		memset(pre,0,sizeof(pre));
		memset(low,0,sizeof(low));
		memset(fa,0,sizeof(fa));
		for(int i=1;i<=n;i++) f[i]=i;
		for(int i=1;i<=m;i++)
		{
			u=read();v=read();
			add_edge(u,v);
			add_edge(v,u);
		}
		for(int i=1;i<=n;i++)
			if(!pre[i]) Tarjan(i,0);
		int Q=read();
		while(Q--)
		{
			u=read();v=read();
			gao(u,v);
			print(ans);
		}
		n=read();m=read();
		putc('\n');
	}
	flush();
	return 0;
}
