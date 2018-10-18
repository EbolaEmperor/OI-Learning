#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

bool vis[50];
int a[50],n,r;

void dfs(int deep)
{
	if(deep>r)
	{
		for(int i=1;i<=r;i++) printf("%3d",a[i]);
		putchar('\n');
		return;
	}
	for(int i=max(a[deep-1],1);i<=n;i++)
		if(!vis[i])
		{
			vis[i]=1;
			a[deep]=i;
			dfs(deep+1);
			vis[i]=0;
		}
}

int main()
{
	cin>>n>>r;
	memset(vis,0,sizeof(vis));
	dfs(1);
	return 0;
}
