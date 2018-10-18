#include<bits/stdc++.h>
#define INF 0x3f3f3f3f
using namespace std;

const int N=300010;
int tot=0;
struct Edge{int to,capa,next;} e[N*10];
int h[N],sum=0,n,m,K;
int dis[12][N];
bool vis[12][N];
struct Node{int k,v,w;};
bool operator < (const Node &a,const Node &b){return a.w>b.w;}

void add_edge(int u,int v,int w)
{
	e[++sum].to=v;
	e[sum].capa=w;
	e[sum].next=h[u];
	h[u]=sum;
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

void dijkstra(int s)
{
	memset(dis,0x3f,sizeof(dis));
	priority_queue<Node> q;
	q.push((Node){0,s,0});
	dis[0][s]=0;
	while(!q.empty())
	{
		Node tmp=q.top();q.pop();
		int u=tmp.v,w=tmp.w,k=tmp.k;
		if(vis[k][u]) continue;
		vis[k][u]=1;
		for(int t=h[u];t;t=e[t].next)
		{
			int v=e[t].to;
			if(w+e[t].capa<dis[k][v])
			{
				dis[k][v]=w+e[t].capa;
				q.push((Node){k,v,dis[k][v]});
			}
			if(k<K&&w<dis[k+1][v])
			{
				dis[k+1][v]=w;
				q.push((Node){k+1,v,w});
			}
		}
	}
}

int main()
{
	int T,a,b,c,d,w;
	scanf("%d%d%d%d",&T,&n,&m,&K);
	t1.build(1,1,n,0);
	t2.build(1,1,n,1);
	gao(1,1,n);
	while(m--)
	{
		scanf("%d%d%d%d%d",&a,&b,&c,&d,&w);
		tot++;
		t1.link(1,1,n,a,b,tot,0,w);
		t2.link(1,1,n,c,d,tot,1,0);
		tot++;
		t1.link(1,1,n,c,d,tot,0,w);
		t2.link(1,1,n,a,b,tot,1,0);
	}
	dijkstra(t1.getid(1,1,n,1));
	int ans=INF,t=t2.getid(1,1,n,n);
	for(int i=0;i<=K;i++)
		ans=min(ans,dis[i][t]);
	if(ans==INF) puts("Yww is our red sun!");
	else cout<<ans<<endl;
	return 0;
}
