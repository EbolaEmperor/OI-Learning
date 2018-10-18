#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;

struct Edge{int to,next;} e[500000];
int h[200000];
int n,m,sum=0,cnt=0;
bool del[200000];
int dfs_clock=0;
int pre[200000],low[200000];

void add_edge(int u,int v)
{
	sum++;
	e[sum].to=v;
	e[sum].next=h[u];
	h[u]=sum;
}

void DFS(int u,int fa)
{
	low[u]=pre[u]=++dfs_clock;
	int child=0;
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		int v=e[tmp].to;
		if(pre[v]!=0) pre[u]=min(pre[u],low[v]);
		else
		{
			child++;
			DFS(v,u);
			pre[u]=min(pre[u],pre[v]);
			if(fa==-1&&child>1||fa!=-1&&pre[v]==low[u])
			{
				if(!del[u]) cnt++;
				del[u]=1;
			}
		}
	}
}

int main()
{
	memset(h,0,sizeof(h));
	memset(del,0,sizeof(del));
	memset(pre,0,sizeof(pre));
	memset(low,0,sizeof(low));
	int x,y;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		add_edge(x,y);
		add_edge(y,x);
	}
	for(int i=1;i<=n;i++)
		if(!low[i]) DFS(i,-1);
	printf("%d\n",cnt);
	for(int i=1;i<=n;i++)
		if(del[i]) printf("%d ",i);
	return 0;
}
