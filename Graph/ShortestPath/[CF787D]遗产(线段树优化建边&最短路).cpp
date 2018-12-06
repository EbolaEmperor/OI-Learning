#include<bits/stdc++.h>
#define INF 0x3f3f3f3f3f3f3f3f
using namespace std;

namespace IO
{
	const int S=1<<16;
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
		putc(' ');
	}
}

using namespace IO;
typedef long long LL;
const int N=500010;
int tot=0;
struct Edge{int to,next;LL capa;} e[N*10];
int h[N],sum=0,n,m,s;
LL dis[N];
bool vis[N];
struct Node{int v;LL w;};
bool operator < (const Node &a,const Node &b){return a.w>b.w;}

void add_edge(int u,int v,LL w)
{
	e[++sum].to=v;
	e[sum].capa=w;
	e[sum].next=h[u];
	h[u]=sum;
}

void dijkstra(int s)
{
	memset(dis,0x3f,sizeof(dis));
	priority_queue<Node> q;
	q.push((Node){s,0});
	dis[s]=0;
	while(!q.empty())
	{
		Node tmp=q.top();q.pop();
		int u=tmp.v;LL w=tmp.w;
		if(vis[u]) continue;
		vis[u]=1;
		for(int t=h[u];t;t=e[t].next)
		{
			int v=e[t].to;
			if(w+e[t].capa<dis[v])
			{
				dis[v]=w+e[t].capa;
				q.push((Node){v,dis[v]});
			}
		}
	}
}

struct SegmentTree
{
	int pnt[N<<2];
	
	void build(int o,int l,int r,bool v)
	{
		pnt[o]=++tot;
		if(l==r) return;
		int mid=(l+r)/2;
		build(o<<1,l,mid,v);
		build(o<<1|1,mid+1,r,v);
		if(v) add_edge(pnt[o],pnt[o<<1],0),add_edge(pnt[o],pnt[o<<1|1],0);
		else add_edge(pnt[o<<1],pnt[o],0),add_edge(pnt[o<<1|1],pnt[o],0);
	}
	
	void link(int o,int l,int r,int nl,int nr,int k,bool v,int w)
	{
		if(l>=nl&&r<=nr)
		{
			if(v) add_edge(k,pnt[o],w);
			else add_edge(pnt[o],k,w);
			return;
		}
		int mid=(l+r)/2;
		if(nl<=mid) link(o<<1,l,mid,nl,nr,k,v,w);
		if(nr>mid) link(o<<1|1,mid+1,r,nl,nr,k,v,w);
	}
	
	int getid(int o,int l,int r,int k)
	{
		if(l==r) return pnt[o];
		int mid=(l+r)/2;
		if(k<=mid) return getid(o<<1,l,mid,k);
		else return getid(o<<1|1,mid+1,r,k);
	}
} t1,t2;

void gao(int o,int l,int r)
{
	if(l==r){add_edge(t2.pnt[o],t1.pnt[o],0);return;}
	int mid=(l+r)/2;
	gao(o<<1,l,mid);
	gao(o<<1|1,mid+1,r);
}

int main()
{
	int t,v,x,y,w;
	n=read();m=read();s=read();
	t1.build(1,1,n,0);
	t2.build(1,1,n,1);
	gao(1,1,n);
	while(m--)
	{
		t=read();
		if(t==1)
		{
			v=read();x=read();w=read();
			v=t1.getid(1,1,n,v);
			x=t2.getid(1,1,n,x);
			add_edge(v,x,w);
		}
		if(t==2)
		{
			v=read();x=read();y=read();w=read();
			v=t1.getid(1,1,n,v);
			t2.link(1,1,n,x,y,v,1,w);
		}
		if(t==3)
		{
			v=read();x=read();y=read();w=read();
			v=t2.getid(1,1,n,v);
			t1.link(1,1,n,x,y,v,0,w);
		}
	}
	dijkstra(t1.getid(1,1,n,s));
	for(int i=1;i<=n;i++)
	{
		int u=t1.getid(1,1,n,i);
		print(dis[u]==INF?-1:dis[u]);
	}
	flush();
	return 0;
}
