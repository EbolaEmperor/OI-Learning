#include<bits/stdc++.h>
using namespace std;

const int N=100010,M=N*100;
struct Edge{int from,to,next;} e[M<<1];
struct Uni{int a,b,c;} un[N];
int posa[N],posb[N],posc[N];
int h[M],sum=0,tot=0,n;
int tr[N<<2];
int dfn[M],low[M],scc[M];
int dfc=0,sccn=0;
stack<int> s;

void add_edge(int u,int v)
{
	e[++sum].to=v;
	e[sum].from=u;
	e[sum].next=h[u];
	h[u]=sum;
}

void add(int o,int l,int r,int nl,int nr,int x)
{
	if(l>=nl&&r<=nr)
	{
		add_edge(x,tr[o]);
		return;
	}
	int mid=(l+r)/2;
	if(nl<=mid) add(o<<1,l,mid,nl,nr,x);
	if(nr>mid) add(o<<1|1,mid+1,r,nl,nr,x);
}

void insert(int o,int l,int r,int k,int x)
{
	if(l==r){tr[o]=x;return;}
	int mid=(l+r)/2;
	if(k<=mid) insert(o<<1,l,mid,k,x);
	else insert(o<<1|1,mid+1,r,k,x);
	if(!tr[o<<1]) tr[o]=tr[o<<1|1];
	else if(!tr[o<<1|1]) tr[o]=tr[o<<1];
	else
	{
		tr[o]=++tot;
		add_edge(tr[o],tr[o<<1]);
		add_edge(tr[o],tr[o<<1|1]);
	}
}

void build()
{
	tot=n;
	for(int i=1;i<=n;i++)
	{
		add(1,1,n,1,un[posa[i]].b,posa[i]);
		insert(1,1,n,un[posa[i]].b,posa[i]);
	}
	memset(tr,0,sizeof(tr));
	for(int i=1;i<=n;i++)
	{
		add(1,1,n,1,un[posa[i]].c,posa[i]);
		insert(1,1,n,un[posa[i]].c,posa[i]);
	}
	memset(tr,0,sizeof(tr));
	for(int i=1;i<=n;i++)
	{
		add(1,1,n,1,un[posb[i]].c,posb[i]);
		insert(1,1,n,un[posb[i]].c,posb[i]);
	}
}

void Tarjan(int u)
{
	s.push(u);
	dfn[u]=low[u]=++dfc;
	for(int t=h[u];t;t=e[t].next)
	{
		int v=e[t].to;
		if(!dfn[v]) Tarjan(v),low[u]=min(low[u],low[v]);
		else if(!scc[v]) low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u])
	{
		int o;sccn++;
		do{
			o=s.top();
			scc[o]=sccn;
			s.pop();
		}while(o!=u);
	}
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&un[i].a);posa[un[i].a]=i;
		scanf("%d",&un[i].b);posb[un[i].b]=i;
		scanf("%d",&un[i].c);posc[un[i].c]=i;
	}
	build();
	for(int i=1;i<=n;i++)
		if(!dfn[i]) Tarjan(i);
	for(int i=1;i<=n;i++)
		puts(scc[i]==sccn?"1":"0");
	return 0;
}