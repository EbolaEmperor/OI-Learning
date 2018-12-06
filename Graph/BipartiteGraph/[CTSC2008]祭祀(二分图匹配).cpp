#include<bits/stdc++.h>
#define R register
using namespace std;

bool G[111][111];
bool vis[111];
int match[111],n;

bool dfs(int u)
{
	for(R int v=1;v<=n;v++)
	{
		if(!G[u][v]||vis[v]) continue;
		vis[v]=1;
		if(!match[v]||dfs(match[v]))
		{
			match[v]=u;
			return 1;
		}
	}
	return 0;
}

int main()
{
	int m,u,v;
	scanf("%d%d",&n,&m);
	for(R int i=1;i<=m;i++)
	{
		scanf("%d%d",&u,&v);
		G[u][v]=1;
	}
	for(R int k=1;k<=n;k++)
		for(R int i=1;i<=n;i++)
			if(G[i][k]) for(R int j=1;j<=n;j++)
				G[i][j]|=G[k][j];
	int ans=0;
	for(R int i=1;i<=n;i++)
	{
		memset(vis,0,sizeof(vis));
		ans+=dfs(i);
	}
	printf("%d\n",n-ans);
	return 0;
}
