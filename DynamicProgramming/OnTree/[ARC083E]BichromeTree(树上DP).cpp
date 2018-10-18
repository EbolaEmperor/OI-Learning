#include<bits/stdc++.h>
using namespace std;

const int N=1010;
struct Edge{int to,next;} e[N<<1];
int h[N],sum=0,n;
int g[2][5010],k=0;
int w[N],X[N];

void add_edge(int u,int v)
{
	e[++sum].to=v;
	e[sum].next=h[u];
	h[u]=sum;
}

void mem(int k){memset(g[k],0x3f,sizeof(g[k]));}
inline void upmin(int &x,const int &y){if(y<x) x=y;}

bool dfs(int u)
{
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
		if(!dfs(e[tmp].to)) return 0;
	k=1;mem(k);g[k][0]=0;
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		k^=1;mem(k);int v=e[tmp].to;
		for(int i=0;i<=X[u];i++)
		{
			if(i>=X[v]) upmin(g[k][i],g[k^1][i-X[v]]+w[v]);
			if(i>=w[v]) upmin(g[k][i],g[k^1][i-w[v]]+X[v]);
		}
	}
	int res=0x3f3f3f3f;
	for(int i=0;i<=X[u];i++)
		upmin(res,g[k][i]);
	if(res==0x3f3f3f3f) return 0;
	w[u]=res;return 1; 
}

int main()
{
	int fa;
	scanf("%d",&n);
	for(int i=2;i<=n;i++)
	{
		scanf("%d",&fa);
		add_edge(fa,i);
	}
	for(int i=1;i<=n;i++) scanf("%d",X+i);
	puts(dfs(1)?"POSSIBLE":"IMPOSSIBLE");
	return 0;
}
