#include<bits/stdc++.h>
using namespace std;

struct Edge{int to,next;} e[2][100010];
int froms[100010],tos[100010],n,m;
int h[2][10010],sum[2]={0};
int pre[10010],low[10010],scc[10010];
int ww[10010],w[10010];
int f[10010];
int dfs_clock,scc_size;
stack<int> s;

void add_edge(int u,int v,int ty)
{
	sum[ty]++;
	e[ty][sum[ty]].to=v;
	e[ty][sum[ty]].next=h[ty][u];
	h[ty][u]=sum[ty];
}

void Tarjan(int u)
{
	pre[u]=low[u]=++dfs_clock;
	s.push(u);
	for(int tmp=h[0][u];tmp;tmp=e[0][tmp].next)
		if(!pre[e[0][tmp].to])
		{
			Tarjan(e[0][tmp].to);
			low[u]=min(low[u],low[e[0][tmp].to]);
		}
		else if(!scc[e[0][tmp].to]) low[u]=min(low[u],pre[e[0][tmp].to]);
	if(pre[u]==low[u])
	{
		scc_size++;
		int o;
		int weigh=0;
		do{
			o=s.top();
			s.pop();
			weigh+=ww[o];
			scc[o]=scc_size;
		}while(o!=u);
		w[scc_size]=weigh;
	}
}

void find_scc()
{
	memset(pre,0,sizeof(pre));
	memset(low,0,sizeof(low));
	memset(scc,0,sizeof(scc));
	dfs_clock=scc_size=0;
	for(int i=1;i<=n;i++)
		if(!pre[i]) Tarjan(i);
}

void dfs(int u)
{
	if(f[u]) return;
	f[u]=w[u];
	int mxsum=0;
	for(int tmp=h[1][u];tmp;tmp=e[1][tmp].next)
	{
		if(!f[e[1][tmp].to]) dfs(e[1][tmp].to);
		mxsum=max(mxsum,f[e[1][tmp].to]);
	}
	f[u]+=mxsum;
}

int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++) scanf("%d",ww+i);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",froms+i,tos+i);
		add_edge(froms[i],tos[i],0);
	}
	find_scc();
	for(int i=1;i<=m;i++)
		if(scc[froms[i]]!=scc[tos[i]]) add_edge(scc[froms[i]],scc[tos[i]],1);
	int ans=0;
	for(int i=1;i<=scc_size;i++)
		if(!f[i]) dfs(i),ans=max(ans,f[i]);
	cout<<ans<<endl;
	return 0;
}
