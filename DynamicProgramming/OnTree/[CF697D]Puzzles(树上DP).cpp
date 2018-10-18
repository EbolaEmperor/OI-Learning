#include<bits/stdc++.h>
using namespace std;

const int N=100010;
struct Edge{int to,next;} e[N];
int h[N],sum=0,n;
int size[N];
double ans[N];

void add_edge(int u,int v)
{
	e[++sum].to=v;
	e[sum].next=h[u];
	h[u]=sum;
}

void dfs1(int u)
{
	size[u]=1;
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
		dfs1(e[tmp].to),size[u]+=size[e[tmp].to];
}

void dfs2(int u,int fa)
{
	ans[u]=(u==1)?1:ans[fa]+1+0.5*(size[fa]-size[u]-1);
	for(int tmp=h[u];tmp;tmp=e[tmp].next) dfs2(e[tmp].to,u);
}

int main()
{
	int x;
	scanf("%d",&n);
	for(int i=2;i<=n;i++)
	{
		scanf("%d",&x);
		if(i==1) continue;
		add_edge(x,i);
	}
	dfs1(1);dfs2(1,0);
	for(int i=1;i<=n;i++)
		printf("%.2lf ",ans[i]);
	return 0;
}
