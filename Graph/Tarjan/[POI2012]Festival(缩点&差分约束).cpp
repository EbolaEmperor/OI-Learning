#include<bits/stdc++.h>
using namespace std;

inline void upmin(int &x,const int &y){if(y<x) x=y;}
inline void upmax(int &x,const int &y){if(y>x) x=y;}

int read()
{
	int x=0;char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	return x;
}

const int N=610,M=200010;
int dis[N][N];
int froms[M],tos[M],nxt[M],cpa[M];
int sum=0,h[N];
int pre[N],low[N],scc[N],dfn=0,cnt=0;
stack<int> sta;

void add_edge(int u,int v,int w)
{
	sum++;
	froms[sum]=u;
	tos[sum]=v;
	cpa[sum]=w;
	nxt[sum]=h[u];
	h[u]=sum;
}

void Tarjan(int u)
{
	pre[u]=low[u]=++dfn;sta.push(u);
	for(int tmp=h[u];tmp;tmp=nxt[tmp])
		if(!pre[tos[tmp]])
		{
			Tarjan(tos[tmp]);
			upmin(low[u],low[tos[tmp]]);
		}
		else if(!scc[tos[tmp]]) upmin(low[u],pre[tos[tmp]]);
	if(pre[u]==low[u])
	{
		int o;cnt++;
		do{
			o=sta.top();
			scc[o]=cnt;
			sta.pop();
		}while(o!=u);
	}
}

int main()
{
	int n,m1,m2,x,y;
	n=read();m1=read();m2=read();
	for(int i=1;i<=m1;i++)
	{
		x=read();y=read();
		add_edge(x,y,1);
		add_edge(y,x,-1);
	}
	for(int i=1;i<=m2;i++)
	{
		x=read();y=read();
		add_edge(y,x,0);
	}
	for(int i=1;i<=n;i++)
		if(!pre[i]) Tarjan(i);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			dis[i][j]=0x3fffffff;
	for(int i=1;i<=sum;i++)
		upmin(dis[froms[i]][tos[i]],cpa[i]);
	for(int i=1;i<=n;i++) dis[i][i]=0;
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				upmin(dis[i][j],dis[i][k]+dis[k][j]);
	for(int i=1;i<=n;i++)
		if(dis[i][i]){puts("NIE");return 0;}
	int dafa=0,mx;
	for(int k=1;k<=cnt;k++)
	{
		mx=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				if(scc[i]==k&&scc[j]==k) upmax(mx,dis[i][j]);
		dafa+=mx+1;
	}
	printf("%d\n",dafa);
	return 0;
}
