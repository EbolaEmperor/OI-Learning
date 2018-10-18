#include<bits/stdc++.h>
using namespace std;

typedef long long LL;

const int N=50010,M=100010;
struct Edge{int to,next;LL capa;} e[M<<1];
int h[N],sum=0,n,m;
bool vis[N];
LL dis[N],base[70];

void add_edge(int u,int v,LL w)
{
	e[++sum].to=v;
	e[sum].capa=w;
	e[sum].next=h[u];
	h[u]=sum;
}

void insert(LL x)
{
	for(int i=60;i>=0;i--)
		if(x&(1ll<<i))
		{
			if(base[i]) x^=base[i];
			else{base[i]=x;break;}
		}
}

void dfs(int u)
{
	vis[u]=1;
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		int v=e[tmp].to;
		if(vis[v]) insert(dis[u]^dis[v]^e[tmp].capa);
		else dis[v]=dis[u]^e[tmp].capa,dfs(v);
	}
}

LL query(LL x)
{
	for(int i=60;i>=0;i--)
		if((x^base[i])>x) x^=base[i];
	return x;
}

int main()
{
	int u,v;LL w;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%lld",&u,&v,&w);
		add_edge(u,v,w);
		add_edge(v,u,w);
	}
	dfs(1);
	printf("%lld\n",query(dis[n]));
	return 0;
}
