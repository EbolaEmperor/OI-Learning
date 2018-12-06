#include<bits/stdc++.h>
using namespace std;

struct Edge{int to,next;} e[500010];
int h[100010]={0},sum=0,n;
int pre[100010]={0},low[100010]={0},scc[100010]={0};
int dfs_clock=0,scc_size=0;
stack<int> s;
int froms[500010],tos[500010];
int deg[100010]={0};

void add_edge(int u,int v)
{
	sum++;
	e[sum].to=v;
	e[sum].next=h[u];
	h[u]=sum;
}

void Tarjan(int u)
{
	pre[u]=low[u]=++dfs_clock;
	s.push(u);
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
		if(!pre[e[tmp].to])
		{
			Tarjan(e[tmp].to);
			low[u]=min(low[u],low[e[tmp].to]);
		}
		else if(!scc[e[tmp].to]) low[u]=min(low[u],pre[e[tmp].to]);
	if(pre[u]==low[u])
	{
		int o;
		scc_size++;
		do{
			o=s.top();
			scc[o]=scc_size;
			s.pop();
		}while(u!=o);
	}
}

int main()
{
	int m;
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",froms+i,tos+i);
		add_edge(froms[i],tos[i]);
	}
	for(int i=1;i<=n;i++)
		if(!pre[i]) Tarjan(i);
	for(int i=1;i<=m;i++)
		if(scc[froms[i]]!=scc[tos[i]]) deg[scc[tos[i]]]++;
	int cnt=0;
	for(int i=1;i<=scc_size;i++)
		if(deg[i]==0) cnt++;
	cout<<cnt<<endl;
	return 0;
}
