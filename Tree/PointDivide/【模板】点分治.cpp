#include<bits/stdc++.h>
#define INF 0x7fffffff
using namespace std;

struct Edge{int to,capa,next;} e[20010];
int h[10010],tot=0,n;
int sum[10000010];
int sumary,smer,root,mn;
int sim[10010];
int dis[10010];
bool done[10010];

void add_edge(int u,int v,int w)
{
	tot++;
	e[tot].to=v;
	e[tot].capa=w;
	e[tot].next=h[u];
	h[u]=tot;
}

void GetRoot(int u,int fa)
{
	sim[u]=1;
	int mxson=0;
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		if(e[tmp].to==fa||done[e[tmp].to]) continue;
		GetRoot(e[tmp].to,u);
		sim[u]+=sim[e[tmp].to];
		mxson=max(mxson,sim[e[tmp].to]);
	}
	mxson=max(mxson,smer-sim[u]);
	if(mxson<mn) mn=mxson,root=u;
}

void dfs(int u,int fa,int w)
{
	dis[++sumary]=w;
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		if(e[tmp].to==fa||done[e[tmp].to]) continue;
		dfs(e[tmp].to,u,w+e[tmp].capa);
	}
}

void solve(int u,int w,int add)
{
	sumary=0;
	dfs(u,0,w);
	for(int i=1;i<sumary;i++)
		for(int j=i+1;j<=sumary;j++)
			sum[dis[i]+dis[j]]+=add;
}

void Divide(int u)
{
	done[u]=1;
	solve(u,0,1);
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		if(done[e[tmp].to]) continue;
		solve(e[tmp].to,e[tmp].capa,-1);
		root=0;mn=INF;smer=sim[e[tmp].to];
		GetRoot(e[tmp].to,0);
		Divide(root);
	}
}

int main()
{
	int a,b,c,m;
	cin>>n>>m;
	for(int i=1;i<n;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		add_edge(a,b,c);
		add_edge(b,a,c);
	}
	memset(done,0,sizeof(done));
	root=0;smer=n;mn=INF;
	GetRoot(1,0);
	Divide(root);
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&a);
		puts(sum[a]?"AYE":"NAY");
	}
	return 0;
}
