#include<bits/stdc++.h>
#define INF 0x7fffffff
using namespace std;

struct Edge{int from,to,capa,next;};
bool operator < (Edge a,Edge b){return a.capa>b.capa;}

struct Graph
{
	Edge e[100010];
	int h[10010],sum;
	void add_edge(int u,int v,int w)
	{
		sum++;
		e[sum].from=u;
		e[sum].to=v;
		e[sum].capa=w;
		e[sum].next=h[u];
		h[u]=sum;
	}
} g,t;

int n,m;
int fa[10010];
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
int mul[10010][20],limit[10010][20],dep[10010];

void dfs(int u,int fa)
{
	mul[u][0]=fa;
	for(int tmp=t.h[u];tmp;tmp=t.e[tmp].next)
	{
		if(t.e[tmp].to==fa) continue;
		limit[t.e[tmp].to][0]=t.e[tmp].capa;
		dep[t.e[tmp].to]=dep[u]+1;
		dfs(t.e[tmp].to,u);
	}
}

void init()
{
	for(int j=1;j<=14;j++)
		for(int i=1;i<=n;i++)
		{
			mul[i][j]=mul[mul[i][j-1]][j-1];
			limit[i][j]=min(limit[mul[i][j-1]][j-1],limit[i][j-1]);
		}
}

int LCA(int p1,int p2)
{
	if(dep[p1]<dep[p2]) swap(p1,p2);
	for(int j=14;j>=0;j--)
		if(dep[mul[p1][j]]>=dep[p2]) p1=mul[p1][j];
	for(int j=14;j>=0;j--)
		if(mul[p1][j]!=mul[p2][j]) p1=mul[p1][j],p2=mul[p2][j];
	if(p1!=p2) p1=mul[p1][0];
	return p1;
}

int solve(int u,int v)
{
	int lca=LCA(u,v);
	int ans=INF;
	for(int j=14;j>=0;j--)
	{
		if(dep[mul[u][j]]>=dep[lca])
		{
			ans=min(ans,limit[u][j]);
			u=mul[u][j];
		}
		if(dep[mul[v][j]]>=dep[lca])
		{
			ans=min(ans,limit[v][j]);
			v=mul[v][j];
		}
	}
	return ans;
}

int main()
{
	int u,v,w;
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&u,&v,&w);
		g.add_edge(u,v,w);
		g.add_edge(v,u,w);
	}
	sort(g.e+1,g.e+g.sum+1);
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1;i<=g.sum;i++)
	{
		u=g.e[i].from;
		v=g.e[i].to;
		w=g.e[i].capa;
		int x=find(u),y=find(v);
		if(x==y) continue;
		fa[y]=x;
		t.add_edge(u,v,w);
		t.add_edge(v,u,w);
	}
	for(int i=0;i<=n;i++)
		for(int j=0;j<=15;j++)
			limit[i][j]=INF;
	for(int i=1;i<=n;i++)
		if(mul[i][0]==0) dfs(i,i);
	init();
	cin>>w;
	for(int i=1;i<=w;i++)
	{
		scanf("%d%d",&u,&v);
		if(find(u)!=find(v)) puts("-1");
		else printf("%d\n",solve(u,v));
	}
	return 0;
}
