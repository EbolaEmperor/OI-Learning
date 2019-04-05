#include<bits/stdc++.h>
using namespace std;

const int N=15;
int a[N],b[N],n,m;
bool vis[N][N];

int dfs(int c,int d,int k)
{
	int res=a[c]+b[d];
	if(vis[c][d]) return res;
	vis[c][d]=1;
	for(int i=1;i<=n;i++)
		if(!vis[i][d]) res=k?max(res,dfs(i,d,k^1)):min(res,dfs(i,d,k^1));
	for(int i=1;i<=m;i++)
		if(!vis[c][i]) res=k?max(res,dfs(c,i,k^1)):min(res,dfs(c,i,k^1));
	vis[c][d]=0;
	return res;
}

int main()
{
	freopen("data.in","r",stdin);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%d",a+i);
	for(int i=1;i<=m;i++) scanf("%d",b+i);
	printf("%d\n",dfs(1,1,0));
	return 0;
}
