#include<bits/stdc++.h>
#define INF 1000000000
using namespace std;

const int N=3010;
struct Edge{int to,capa,next;} e[N<<1];
int h[N],sum=0,n,k;
int ans=INF;
int f[N][N][3],g[N][3];
int size[N];

inline void upmin(int &x,const int &y){if(y<x) x=y;}

void add_edge(int u,int v,int w)
{
	e[++sum].to=v;
	e[sum].capa=w;
	e[sum].next=h[u];
	h[u]=sum;
}

void merge(int u,int v,int w)
{
	memcpy(g,f[u],sizeof(g));
	int su=min(size[u],k);
	int sv=min(size[v],k);
	for(int i=0;i<=su;i++)
		for(int j=0;j<3;j++)
			for(int ii=0;ii<=min(sv,k-i);ii++)
				for(int jj=0;jj<3-j;jj++)
				{
					int t=2*w;
					if(jj==1) t-=w;
					upmin(g[i+ii][j+jj],f[u][i][j]+f[v][ii][jj]+t);
				}
	memcpy(f[u],g,sizeof(g));
}

void dfs(int u,int fa)
{
	size[u]=1;
	for(int i=0;i<=k;i++) f[u][i][0]=f[u][i][1]=f[u][i][2]=INF;
	f[u][1][0]=f[u][1][1]=f[u][1][2]=0;
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		int v=e[tmp].to;
		if(v==fa) continue;
		dfs(v,u);
		merge(u,v,e[tmp].capa);
		size[u]+=size[v];
	}
	ans=min(ans,f[u][k][2]);
}

int main()
{
	int u,v,w;
	scanf("%d%d",&n,&k);
	for(int i=1;i<n;i++)
	{
		scanf("%d%d%d",&u,&v,&w);
		add_edge(u,v,w);
		add_edge(v,u,w);
	}
	dfs(1,0);
	printf("%d\n",ans);
	return 0;
}
