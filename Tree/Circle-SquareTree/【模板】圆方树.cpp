#include<bits/stdc++.h>
using namespace std;

const int N=100010;

namespace Tree
{
	struct Edge{int to,next;} e[N<<2];
	int h[N<<1],sum=0,w[N<<1],dep[N<<1];
	int fa[N<<1][18],minv[N<<1][18];
	
	void add_edge(int u,int v)
	{ 
		e[++sum].to=v;
		e[sum].next=h[u];
		h[u]=sum;
	}
	
	void dfs(int u)
	{
		minv[u][0]=w[u];
		for(int i=1;i<=17;i++)
		{
			fa[u][i]=fa[fa[u][i-1]][i-1];
			minv[u][i]=min(minv[u][i-1],minv[fa[u][i-1]][i-1]);
		}
		for(int tmp=h[u];tmp;tmp=e[tmp].next)
		{
			if(e[tmp].to==fa[u][0]) continue;
			fa[e[tmp].to][0]=u;
			dep[e[tmp].to]=dep[u]+1;
			dfs(e[tmp].to);
		}
	}
	
	int query(int x,int y)
	{
		int res=w[x];
		if(dep[x]<dep[y]) swap(x,y);
		for(int i=17;i>=0;i--)
			if(dep[fa[x][i]]>=dep[y])
			{
				res=min(res,minv[x][i]);
				x=fa[x][i];
			}
		for(int i=17;i>=0;i--)
			if(fa[x][i]!=fa[y][i])
			{
				res=min(res,minv[x][i]);
				res=min(res,minv[y][i]);
				x=fa[x][i];y=fa[y][i];
			}
		if(x!=y) res=min(res,w[fa[x][0]]);
		return res;
	}
}

namespace Graph
{
	struct Edge{int to,next;} e[N<<2];
	int h[N],sum=0,n,tot;
	int pre[N],low[N],dfn=0;
	stack<int> stk;
	
	void add_edge(int u,int v)
	{
		e[++sum].to=v;
		e[sum].next=h[u];
		h[u]=sum;
	}
	
	void Tarjan(int u)
	{
		pre[u]=low[u]=++dfn;stk.push(u);
		for(int tmp=h[u];tmp;tmp=e[tmp].next)
		{
			int v=e[tmp].to;
			if(!pre[v])
			{
				Tarjan(v);
				low[u]=min(low[u],low[v]);
				if(low[v]>=pre[u])
				{
					int o;Tree::w[++tot]=Tree::w[u];
					do{
						assert(!stk.empty());
						o=stk.top();
						stk.pop();
						Tree::w[tot]=min(Tree::w[tot],Tree::w[o]);
						Tree::add_edge(o,tot);
						Tree::add_edge(tot,o);
					}while(o!=v);
					Tree::add_edge(u,tot);
					Tree::add_edge(tot,u);
					assert(tot<=2*n);
				}
			}
			else low[u]=min(low[u],pre[v]);
		}
	}
	
}

int main()
{
	int q,m,u,v;
	scanf("%d%d",&Graph::n,&m);
	Graph::tot=Graph::n;
	for(int i=1;i<=Graph::n;i++)
		scanf("%d",Tree::w+i);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&u,&v);
		Graph::add_edge(u,v);
		Graph::add_edge(v,u);
	}
	for(int i=1;i<=Graph::n;i++)
		if(!Graph::pre[i]) Graph::Tarjan(i);
	Tree::dep[1]=1;Tree::dfs(1);
	scanf("%d",&q);
	while(q--)
	{
		scanf("%d%d",&u,&v);
		printf("%d\n",Tree::query(u,v));
	}
	return 0;
}
