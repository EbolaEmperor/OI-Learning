#include<bits/stdc++.h>
using namespace std;

const int N=3010;
struct Edge{int to,next;} e[N<<1];
int h[N],sum=0;
int a[N],n;
bool sg[N];

void add_edge(int u,int v)
{
	e[++sum].to=v;
	e[sum].next=h[u];
	h[u]=sum;
}

void dfs(int u,int fa)
{
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		int v=e[tmp].to;
		if(v==fa) continue;dfs(v,u);
		if(sg[v]==0&&a[u]>a[v]) sg[u]=1;
	}
}

int main()
{
	int u,v;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",a+i);
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&u,&v);
		add_edge(u,v);
		add_edge(v,u);
	}
	for(int i=1;i<=n;i++)
	{
		memset(sg,0,sizeof(sg));
		dfs(i,0);
		if(sg[i]) printf("%d ",i);
	}
	return 0;
}
