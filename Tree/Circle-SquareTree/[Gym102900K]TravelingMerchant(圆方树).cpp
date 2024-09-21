#include<bits/stdc++.h>
using namespace std;

const int N=200010;

namespace Tree
{
	struct Edge{int to,next;} e[N<<2];
	int h[N<<1],sum=0,dfn[N<<1],odfn[N<<1],fa[N<<1],dfc=0;
	
	void add_edge(int u,int v)
	{ 
		e[++sum].to=v;
		e[sum].next=h[u];
		h[u]=sum;
	}
	
	void dfs(int u)
	{
		dfn[u]=++dfc;
        for(int i=h[u];i;i=e[i].next)
            if(e[i].to!=fa[u])
                fa[e[i].to]=u, dfs(e[i].to);
        odfn[u]=dfc;
	}

    bool query(int u,int v){
        if(!dfn[u] || !dfn[v]) return 0;
        if(u!=1) u=fa[u];
        if(v!=1) v=fa[v];
        if(dfn[u]>dfn[v]) swap(u,v);
        return dfn[v]<=odfn[u];
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
					int o;++tot;
					do{
						assert(!stk.empty());
						o=stk.top();
						stk.pop();
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

char col[N];
int eu[N<<1],ev[N<<1],ecnt=0;

bool work(){
	int n,m,u,v;
	scanf("%d%d",&n,&m);

    Graph::n = n;
    Graph::sum = 0;
    memset(Graph::h, 0, sizeof(int)*(n+1));
    memset(Graph::pre, 0, sizeof(int)*(n+1));
    memset(Graph::low, 0, sizeof(int)*(n+1));
	Graph::tot = Graph::n;
    memset(Tree::h, 0, sizeof(int)*(2*n+1));
    memset(Tree::dfn, 0, sizeof(int)*(2*n+1));
    Tree::sum = 0;
    Tree::dfc = 0;
    ecnt = 0;

	scanf("%s",col+1);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&u,&v);
        u++; v++;
        if(col[u]==col[v]){
            eu[++ecnt]=u;
            ev[ecnt]=v;
        } else {
            Graph::add_edge(u,v);
            Graph::add_edge(v,u);
        }
	}
	Graph::Tarjan(1);
	Tree::dfs(1);
	for(int i = 1; i <= ecnt; i++)
        if(Tree::query(eu[i],ev[i])) return 1;
    return 0;
}

int main()
{
    int T;
    scanf("%d", &T);
    while(T--)
        puts(work() ? "yes" : "no");
	return 0;
}