#include<bits/stdc++.h>
using namespace std;

const int N=10010;
vector<int> g[N],lims;
int dfn[N],low[N],scc[N],dfc,sccn;
stack<int> stk;
int p[N],q[N],a[N],b[N];
int ch[N][2];
int n,m;

void dfs(int x)
{
	if(x<=m){lims.push_back(x);return;}
	for(int i=0;i<2;i++)
		dfs(ch[x][i]);
}

void Tarjan(int u)
{
	stk.push(u);
	low[u]=dfn[u]=++dfc;
	for(int v : g[u])
		if(!dfn[v]) Tarjan(v),low[u]=min(low[u],low[v]);
		else if(!scc[v]) low[u]=min(low[u],dfn[v]);
	if(dfn[u]==low[u])
	{
		int o;sccn++;
		do{
			o=stk.top();
			scc[o]=sccn;
			stk.pop();
		}while(o!=u);
	}
}

bool gao(int u)
{
	lims.clear();dfs(u);
	for(int i=1;i<=2*n;i++) g[i].clear();
	for(int x : lims)
	{
		g[p[x]+n*a[x]].push_back(q[x]+n*(b[x]^1));
		g[q[x]+n*b[x]].push_back(p[x]+n*(a[x]^1));
	}
	dfc=sccn=0;
	memset(scc,0,sizeof(int)*(2*n+1));
	memset(dfn,0,sizeof(int)*(2*n+1));
	memset(low,0,sizeof(int)*(2*n+1));
	for(int i=1;i<=2*n;i++)
		if(!dfn[i]) Tarjan(i);
	for(int i=1;i<=n;i++)
		if(scc[i]==scc[i+n]) return 0;
	return 1;
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1,x,y;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		p[i]=abs(x);a[i]=(x<0);
		q[i]=abs(y);b[i]=(y<0);
	}
	for(int i=m+1;i<2*m;i++)
		scanf("%d%d",ch[i],ch[i]+1);
	static char ans[N];
	for(int i=m+1;i<2*m;i++)
		ans[i-m-1]='0'+gao(i);
	puts(ans);
	return 0;
}
