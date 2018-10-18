#include<bits/stdc++.h>
#define pb push_back
using namespace std;

const int N=2010;
struct Edge{int to,next;} e[N];
int h[N],sum=0;
int deg[N],a[N],n;
bool vis[N];

void add_edge(int u,int v)
{
	e[++sum].to=v;
	e[sum].next=h[u];
	h[u]=sum;
}

void dfs(int u)
{
	vis[u]=1;
	for(int i=1;i<=n;i++)
		if(!vis[i]&&__gcd(a[u],a[i])!=1)
			dfs(i),add_edge(u,i),deg[i]++;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",a+i);
	sort(a+1,a+1+n);
	for(int i=1;i<=n;i++)
		if(!vis[i]) dfs(i);
	memset(vis,0,sizeof(vis));
	for(int T=1;T<=n;T++)
	{
		for(int i=n;i>=0;i--)
			if(!vis[i]&&!deg[i])
			{
				printf("%d ",a[i]);
				vis[i]=1;
				for(int tmp=h[i];tmp;tmp=e[tmp].next)
					deg[e[tmp].to]--;
				break;
			}
	}
	return 0;
}
