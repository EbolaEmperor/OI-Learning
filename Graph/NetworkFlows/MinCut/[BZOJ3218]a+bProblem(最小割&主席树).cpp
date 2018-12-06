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
	int x=0;char c=Get();
	while(!isdigit(c)) c=Get();
	while(isdigit(c)) x=x*10+c-'0',c=Get();
	return x;
}

const int N=10010;
struct Edge{int to,capa,flow,next;} e[100*N];
int h[N<<5],sum=-1,s,t,tot,n;
int a[N],l[N],r[N],Hash[N*3];
bool vis[N<<5];
int deep[N<<5];
int cur[N<<5];

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
	vis[s]=1;deep[s]=0;
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(int tmp=h[u];~tmp;tmp=e[tmp].next)
			if(!vis[e[tmp].to]&&e[tmp].capa>e[tmp].flow)
			{
				vis[e[tmp].to]=1;
				deep[e[tmp].to]=deep[u]+1;
				q.push(e[tmp].to);
			}
	}
	return vis[t];
}

int DFS(int u,int a)
{
	if(u==t||a==0) return a;
	int flow=0,f;
	for(int &tmp=cur[u];~tmp;tmp=e[tmp].next)
		if(deep[e[tmp].to]==deep[u]+1)
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

int root[N],pnt[N<<5],lc[N<<5],rc[N<<5],size;

inline void copynode(int o,int p)
{
	lc[o]=lc[p];rc[o]=rc[p];
	if(p) add_edge(pnt[o],pnt[p],INF);
}

void link(int o,int l,int r,int nl,int nr,int k)
{
	if(!o) return;
	if(l>=nl&&r<=nr)
	{
		add_edge(k,pnt[o],INF);
		return;
	}
	int mid=(l+r)/2;
	if(nl<=mid) link(lc[o],l,mid,nl,nr,k);
	if(nr>mid) link(rc[o],mid+1,r,nl,nr,k);
}

void insert(int &o,int pre,int l,int r,int k)
{
	pnt[o=++size]=++tot;
	copynode(o,pre);
	add_edge(pnt[o],k,INF);
	if(l==r) return;
	int mid=(l+r)/2;
	if(a[k]<=mid) insert(lc[o],lc[pre],l,mid,k);
	else insert(rc[o],rc[pre],mid+1,r,k);
}

int main()
{
	int b,w,p,ans=0;
	n=read();s=0;t=tot=2*n+1;
	memset(h,-1,sizeof(h));
	for(int i=1;i<=n;i++)
	{
		a[i]=read();b=read();w=read();ans+=b+w;
		l[i]=read();r[i]=read();p=read();
		add_edge(s,i,b);
		add_edge(i,t,w);
		add_edge(i,n+i,p);
		Hash[i]=a[i];
		Hash[n+i]=l[i];
		Hash[2*n+i]=r[i];
	}
	sort(Hash+1,Hash+1+3*n);
	int hs=unique(Hash+1,Hash+1+3*n)-(Hash+1);
	for(int i=1;i<=n;i++)
	{
		a[i]=lower_bound(Hash+1,Hash+1+hs,a[i])-Hash;
		l[i]=lower_bound(Hash+1,Hash+1+hs,l[i])-Hash;
		r[i]=lower_bound(Hash+1,Hash+1+hs,r[i])-Hash;
	}
	for(int i=1;i<=n;i++)
	{
		link(root[i-1],1,hs,l[i],r[i],n+i);
		insert(root[i],root[i-1],1,hs,i);
	}
	printf("%d\n",ans-Dinic());
	return 0;
}
