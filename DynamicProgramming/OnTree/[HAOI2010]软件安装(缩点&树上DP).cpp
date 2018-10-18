#include<bits/stdc++.h>
using namespace std;

struct Edge{int to,next;} e[300],e2[300];
int h[300],h2[300],sum=0,sum2=0;
int pre[300],low[300],scc[300],deg[300];
int scc_size=0,dfs_clock=0;
stack<int> s;
int w[300],v[300],w2[300],v2[300];
int f[300][1500];
int n,m,d[300],root;
bool G[300][300]={0};

void add_edge(int u,int v)
{
	sum++;
	e[sum].to=v;
	e[sum].next=h[u];
	h[u]=sum;
}

void add_edge2(int u,int v)
{
	sum2++;
	e2[sum2].to=v;
	e2[sum2].next=h2[u];
	h2[u]=sum2;
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
	if(low[u]==pre[u])
	{
		int o;
		scc_size++;
		do{
			o=s.top();
			s.pop();
			w2[scc_size]+=w[o];
			v2[scc_size]+=v[o];
			scc[o]=scc_size;
		}while(u!=o);
	}
}

void DP(int u)
{
	for(int i=w2[u];i<=m;i++) f[u][i]=v2[u];
	for(int tmp=h2[u];tmp;tmp=e2[tmp].next)
	{
		DP(e2[tmp].to);
		for(int i=m-w2[u];i>=0;i--)
			for(int j=0;j<=i;j++)
				f[u][i+w2[u]]=max(f[u][i+w2[u]],f[u][i+w2[u]-j]+f[e2[tmp].to][j]);
	}
}


int main()
{
	cin>>n>>m;
	for(int i=1;i<=n;i++) scanf("%d",w+i);
	for(int i=1;i<=n;i++) scanf("%d",v+i);
	for(int i=1;i<=n;i++)
	{
		scanf("%d",d+i);
		if(d[i]) add_edge(d[i],i);
	}
	for(int i=1;i<=n;i++)
		if(!pre[i]) Tarjan(i);
	root=scc_size+1;
	for(int i=1;i<=n;i++)
		if(d[i]&&scc[i]!=scc[d[i]])
			G[scc[d[i]]][scc[i]]=1;
	for(int i=1;i<=scc_size;i++)
		for(int j=1;j<=scc_size;j++)
			if(G[i][j])
			{
				add_edge2(i,j);
				deg[j]++;
			}
	for(int i=1;i<=scc_size;i++)
		if(deg[i]==0) add_edge2(root,i);
	DP(root);
	cout<<f[root][m]<<endl;
	return 0;
}
