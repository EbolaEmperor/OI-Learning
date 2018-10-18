#include<bits/stdc++.h>
#define INF 0x7fffffff
using namespace std;

const int S=(1<<20)+5;
char buf[S],*H,*T;
inline char Get()
{
	if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
	if(H==T) return -1;return *H++;
}
inline int read()
{
	int x=0,fg=1;char c=Get();
	while(!isdigit(c)&&c!='-') c=Get();
	if(c=='-') fg=-1,c=Get();
	while(isdigit(c)) x=x*10+c-'0',c=Get();
	return fg*x;
}

const int N=20010,M=5000000;
int n,m,s,t,tot=0;
int fa[N],K[N];

namespace MF
{
	
	struct Edge{int to,capa,flow,next;} e[M];
	int h[N*6],sum=-1;
	bool vis[N*6];
	int d[N*6],cur[N*6];
	
	void AddEdge(int u,int v,int w)
	{
		e[++sum].to=v;
		e[sum].capa=w;
		e[sum].flow=0;
		e[sum].next=h[u];
		h[u]=sum;
	}
	
	void add_edge(int u,int v,int w)
	{
		AddEdge(u,v,w);
		AddEdge(v,u,0);
	}
	
	bool BFS()
	{
		memset(vis,0,sizeof(vis));
		queue<int> q;q.push(s);
		d[s]=0;vis[s]=1;
		while(!q.empty())
		{
			int u=q.front();q.pop();
			for(int tmp=h[u];~tmp;tmp=e[tmp].next)
				if(e[tmp].capa>e[tmp].flow&&!vis[e[tmp].to])
				{
					vis[e[tmp].to]=1;
					d[e[tmp].to]=d[u]+1;
					q.push(e[tmp].to);
				}
		}
		return vis[t];
	}
	
	int DFS(int u,int a)
	{
		if(u==t||a==0) return a;
		int flow=0,f;
		for(int& tmp=cur[u];~tmp;tmp=e[tmp].next)
			if(d[e[tmp].to]==d[u]+1)
			{
				f=DFS(e[tmp].to,min(a,e[tmp].capa-e[tmp].flow));
				if(f>0)
				{
					flow+=f;a-=f;
					e[tmp].flow+=f;
					e[tmp^1].flow-=f;
					if(a==0) break;
				}
			}
		return flow;
	}
	
	int Dinic()
	{
		int flow=0;
		while(BFS())
		{
			for(int i=0;i<=tot;i++) cur[i]=h[i];
			flow+=DFS(s,INF);
		}
		return flow;
	}
	
}

namespace TCD
{
	
	struct Edge{int to,next;} e[N];
	int h[N],sum=0;
	int dep[N],size[N];
	int hson[N],top[N];
	int dfn[N],idx[N],clk=0;
	int pnt[N<<2];
	
	void add_edge(int u,int v)
	{
		e[++sum].to=v;
		e[sum].next=h[u];
		h[u]=sum;
	}
	
	void dfs1(int u)
	{
		size[u]=1;int mx=0;
		for(int tmp=h[u];tmp;tmp=e[tmp].next)
		{
			int v=e[tmp].to;
			dep[v]=dep[u]+1;
			dfs1(v);
			size[u]+=size[v];
			if(size[v]>mx) mx=size[v],hson[u]=v;
		}
	}
	
	void dfs2(int u,int tp)
	{
		idx[dfn[u]=++clk]=u;top[u]=tp;
		if(hson[u]) dfs2(hson[u],tp);
		for(int tmp=h[u];tmp;tmp=e[tmp].next)
			if(e[tmp].to!=fa[u]&&e[tmp].to!=hson[u])
				dfs2(e[tmp].to,e[tmp].to);
	}
	
	void Build(int o,int l,int r)
	{
		if(l==r){pnt[o]=idx[l];return;}
		int mid=(l+r)/2;
		pnt[o]=++tot;
		Build(o<<1,l,mid);
		Build(o<<1|1,mid+1,r);
		MF::add_edge(pnt[o],pnt[o<<1],INF);
		MF::add_edge(pnt[o],pnt[o<<1|1],INF);
	}
	
	void link(int o,int l,int r,int nl,int nr,int k)
	{
		if(l>=nl&&r<=nr)
		{
			MF::add_edge(k,pnt[o],INF);
			return;
		}
		int mid=(l+r)/2;
		if(nl<=mid) link(o<<1,l,mid,nl,nr,k);
		if(nr>mid) link(o<<1|1,mid+1,r,nl,nr,k);
	}
	
	void path_link(int u,int d)
	{
		if(d==0) return;
		int x=u;u=fa[u];
		while(dep[x]-dep[top[u]]<=d)
		{
			link(1,1,n,dfn[top[u]],dfn[u],x+n);
			u=fa[top[u]];
		}
		if(dep[x]-dep[u]>d) return;
		int l=dfn[top[u]],r=dfn[u],mid;
		while(l<r)
		{
			mid=(l+r)/2;
			if(dep[x]-dep[idx[mid]]<=d) r=mid;
			else l=mid+1;
		}
		link(1,1,n,r,dfn[u],x+n);
	}
	
}

int main()
{
	n=read();s=0;t=tot=2*n+1;
	memset(MF::h,-1,sizeof(MF::h));
	int ans=0,V,P;
	for(int i=1;i<=n;i++)
	{
		fa[i]=read();V=read();K[i]=read();P=read();
		if(i>1) TCD::add_edge(fa[i],i);
		if(V>=0) MF::add_edge(s,i,V),ans+=V;
		else MF::add_edge(i,t,-V);
		MF::add_edge(i,n+i,P);
	}
	TCD::dep[1]=1;
	TCD::dfs1(1);
	TCD::dfs2(1,1);
	TCD::Build(1,1,n);
	for(int i=1;i<=n;i++)
		TCD::path_link(i,K[i]);
	printf("%d\n",ans-MF::Dinic());
	return 0;
}
