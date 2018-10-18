#include<bits/stdc++.h>
using namespace std;

struct Edge{int to,capa,next;} e[1000010];
int h[200010],sum=0,n,m;
int scc[200010],pre[200010],low[200010];
int scc_size=0,dfs_clock=0;
stack<int> s;
int froms[1000010],tos[1000010],capas[1000010];
bool vis[200010]={0};
int d[200010];

void add_edge(int u,int v,int w)
{
	sum++;
	e[sum].to=v;
	e[sum].next=h[u];
	e[sum].capa=w;
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
			s.pop();
			scc[o]=scc_size;
		}while(o!=u);
	}
}

int spfa(int s)
{
	for(int i=1;i<=scc_size;i++) d[i]=0x7fffffff;
	d[s]=0;
	vis[s]=1;
	queue<int> q;
	q.push(s);
	while(!q.empty())
	{
		int o=q.front();
		for(int tmp=h[o];tmp;tmp=e[tmp].next)
			if(d[o]+e[tmp].capa<d[e[tmp].to])
			{
				d[e[tmp].to]=d[o]+e[tmp].capa;
				if(!vis[e[tmp].to]) vis[e[tmp].to]=1,q.push(e[tmp].to);
			}
		q.pop();
		vis[o]=0;
	}
	return d[scc[n]];
}

int main()
{
	cin>>n>>m;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",froms+i,tos+i,capas+i);
		add_edge(froms[i],tos[i],capas[i]);
	}
	for(int i=1;i<=n;i++)
		if(!pre[i]) Tarjan(i);
	sum=0;
	memset(h,0,sizeof(h));
	for(int i=1;i<=m;i++)
		if(scc[froms[i]]!=scc[tos[i]])
			add_edge(scc[froms[i]],scc[tos[i]],capas[i]);
	cout<<spfa(scc[1])<<endl;
	return 0;
}
