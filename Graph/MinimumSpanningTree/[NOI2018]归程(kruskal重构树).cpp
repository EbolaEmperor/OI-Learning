#include<bits/stdc++.h>
#define INF 0x7fffffff
using namespace std;

int read()
{
	int x=0;char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	return x;
}

const int N=200010;
struct Edge{int u,v,l,a,nxt;} e[N<<2],eg[N<<1],t[N<<1];
int h[N],f[N<<1],n,m;
struct Node{int v,w;};
int dis[N];
bool vis[N];
struct node{int l,a;} p[N<<1];
int fa[N<<1];
int mul[20][N<<1];

bool operator < (const Node &a,const Node &b){return a.w>b.w;}
bool operator < (const Edge &a,const Edge &b){return a.a>b.a;}

void add_edge(Edge *e,int *h,int u,int v,int l,int a)
{
	e[++h[0]]=Edge{u,v,l,a,h[u]};
	h[u]=h[0];
}

void dijkstra()
{
	priority_queue<Node> q;
	q.push(Node{1,0});
	for(int i=2;i<=n;i++) dis[i]=INF;
	memset(vis,0,sizeof(vis));
	while(!q.empty())
	{
		Node tmp=q.top();q.pop();
		int u=tmp.v,d=tmp.w;
		if(vis[u]) continue;
		vis[u]=1;
		for(int i=h[u];i;i=e[i].nxt)
			if(d+e[i].l<dis[e[i].v])
			{
				dis[e[i].v]=d+e[i].l;
				q.push(Node{e[i].v,dis[e[i].v]});
			}
	}
	for(int i=1;i<=n;i++) p[i].l=dis[i];
}

void dfs(int u,int la)
{
	mul[0][u]=la;
	for(int i=1;i<=19;i++)
		mul[i][u]=mul[i-1][mul[i-1][u]];
	if(u>n) p[u].l=INF;
	for(int i=f[u];i;i=t[i].nxt)
	{
		dfs(t[i].v,u);
		p[u].l=min(p[u].l,p[t[i].v].l);
	}
}

int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}

void kruskal()
{
	for(int i=1;i<=2*n;i++) fa[i]=i;
	sort(eg+1,eg+1+m);
	int tot=n;
	for(int i=1;i<=m;i++)
	{
		if(tot==2*n-1) break;
		int u=find(eg[i].u),v=find(eg[i].v);
		if(u==v) continue;
		fa[u]=++tot;fa[v]=tot;
		add_edge(t,f,tot,u,0,0);
		add_edge(t,f,tot,v,0,0);
		p[tot].a=eg[i].a;
	}
	dfs(tot,0);
}

int Query(int u,int a)
{
	for(int i=19;i>=0;i--)
		if(a<p[mul[i][u]].a)
			u=mul[i][u];
	return p[u].l;
}

int main()
{
	int T=read(),u,v,l,a;
	while(T--)
	{
		memset(h,0,sizeof(h));
		memset(f,0,sizeof(f));
		memset(p,0,sizeof(p));
		n=read();m=read();
		for(int i=1;i<=m;i++)
		{
			u=read();v=read();l=read();a=read();
			eg[i]=Edge{u,v,l,a,0};
			add_edge(e,h,u,v,l,a);
			add_edge(e,h,v,u,l,a);
		}
		dijkstra();
		kruskal();
		p[0].a=-1;
		int Q=read(),K=read(),S=read(),lastans=0;
		while(Q--)
		{
			v=read();a=read();
			v=(v+K*lastans-1)%n+1;
			a=(a+K*lastans)%(S+1);
			lastans=Query(v,a);
			printf("%d\n",lastans);
		}
	}
	return 0;
}
