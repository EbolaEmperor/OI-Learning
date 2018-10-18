#include<bits/stdc++.h>
#define lowbit(x) (x&-x)
using namespace std;

typedef long long LL;
int read()
{
	int x=0;char c=getchar();
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
	return x;
}

const int N=300010;

int n;
LL c[N];
void Add(int p,int x){for(;p<=n;p+=lowbit(p))c[p]+=x;}
LL Sum(int p){LL res=0;for(p;p>0;p-=lowbit(p)) res+=c[p];return res;}

struct Edge{int to,next;} e[2*N];
int h[N],sum=0;
int dep[N],sz[N];

void add_edge(int u,int v)
{
	sum++;
	e[sum].to=v;
	e[sum].next=h[u];
	h[u]=sum;
}

void dfs1(int u,int fa)
{
	sz[u]=1;
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		int v=e[tmp].to;
		if(v==fa) continue;
		dep[v]=dep[u]+1;
		dfs1(v,u);
		sz[u]+=sz[v];
	}
}

struct QUERY{int id,k;QUERY(int a=0,int b=0):id(a),k(b){}};
vector<QUERY> qry[N];
LL ans[N];

void dfs2(int u,int fa)
{
	for(int i=0;i<qry[u].size();i++)
		ans[qry[u][i].id]-=Sum(min(dep[u]+qry[u][i].k,n))-Sum(dep[u]);
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
		if(e[tmp].to!=fa) dfs2(e[tmp].to,u);
	for(int i=0;i<qry[u].size();i++)
	{
		ans[qry[u][i].id]+=Sum(min(dep[u]+qry[u][i].k,n))-Sum(dep[u]);
		ans[qry[u][i].id]+=(LL)(min(qry[u][i].k,dep[u]-1))*(sz[u]-1);
	}
	Add(dep[u],sz[u]-1);
}

int main()
{
	n=read();int q=read(),u,v;
	for(int i=1;i<n;i++)
	{
		u=read();v=read();
		add_edge(u,v);
		add_edge(v,u);
	}
	dep[1]=1;
	dfs1(1,0);
	for(int i=1;i<=q;i++)
	{
		u=read();v=read();
		qry[u].push_back(QUERY(i,v));
	}
	dfs2(1,0);
	for(int i=1;i<=q;i++)
		printf("%lld\n",ans[i]);
	return 0;
}
