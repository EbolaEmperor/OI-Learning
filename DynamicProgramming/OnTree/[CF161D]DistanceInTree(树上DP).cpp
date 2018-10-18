#include<bits/stdc++.h>
using namespace std;

const int N=50010;
struct Edge{int to,next;} e[N<<1];
int h[N],sum,n,k;
long long ans=0;
long long f[N][510];

void add_edge(int u,int v)
{
	e[++sum].to=v;
	e[sum].next=h[u];
	h[u]=sum;
}

void dfs(int u,int la)
{
	f[u][0]=1;
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		int v=e[tmp].to;
		if(v==la) continue;
		dfs(v,u);
		for(int i=0;i<k;i++)
			ans+=f[u][i]*f[v][k-i-1];
		for(int i=1;i<k;i++)
			f[u][i]+=f[v][i-1];
	}
}

int main()
{
	int u,v;
	scanf("%d%d",&n,&k);
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&u,&v);
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs(1,0);
	printf("%lld\n",ans);
	return 0;
}
