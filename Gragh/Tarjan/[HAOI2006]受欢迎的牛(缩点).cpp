#include<bits/stdc++.h>
using namespace std;

struct Edge{int to,next;} e[50010];
int h[10010],sum=0,n,m;
int froms[50010],tos[50010];
int pre[10010],low[10010];
int scc_size,dfs_clock;
int scc[10010];
stack<int> s;
int deg[10010];

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
		if(pre[e[tmp].to]==0)
		{
			Tarjan(e[tmp].to);
			low[u]=min(low[u],low[e[tmp].to]);
		}
		else if(scc[e[tmp].to]==0) low[u]=min(low[u],pre[e[tmp].to]);
	if(pre[u]==low[u])
	{
		scc_size++;
		int o;
		do{
			o=s.top();
			scc[o]=scc_size;
			s.pop();
		}while(o!=u);
	}
}

void find_scc()
{
	memset(pre,0,sizeof(pre));
	memset(low,0,sizeof(low));
	memset(scc,0,sizeof(scc));
	scc_size=dfs_clock=0;
	for(int i=1;i<=n;i++)
		if(pre[i]==0) Tarjan(i);
}

int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",froms+i,tos+i);
		add_edge(froms[i],tos[i]);
	}
	find_scc();
	memset(deg,0,sizeof(deg));
	for(int i=1;i<=m;i++)
		if(scc[froms[i]]!=scc[tos[i]]) deg[scc[froms[i]]]++;
	int cnt=0,p;
	for(int i=1;i<=scc_size;i++)
		if(deg[i]==0) cnt++,p=i;
	if(cnt>1){puts("0");return 0;}
	cnt=0;
	for(int i=1;i<=n;i++)
		cnt+=(scc[i]==p);
	cout<<cnt<<endl;
	return 0;
}
