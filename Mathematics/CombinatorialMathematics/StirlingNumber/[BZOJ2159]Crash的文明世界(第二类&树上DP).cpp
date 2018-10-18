#include<bits/stdc++.h>
#define Mod 10007
using namespace std;

const int N=50010,K=160;
struct Edge{int to,next;} e[N<<1];
int h[N],sum=0;
int f[N][K],g[N][K];
int stl[K][K],fac[N];
int n,k;

void add_edge(int u,int v)
{
	e[++sum].to=v;
	e[sum].next=h[u];
	h[u]=sum;
}

void dfs1(int u,int fa)
{
	f[u][0]=1;
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		int v=e[tmp].to;
		if(v==fa) continue;
		dfs1(v,u);
		f[u][0]=(f[u][0]+f[v][0])%Mod;
		for(int j=1;j<=k;j++)
			f[u][j]=(f[u][j]+f[v][j]+f[v][j-1])%Mod;
	}
}

void dfs2(int u,int fa)
{
	g[u][0]=n-f[u][0];
	if(fa)for(int j=1;j<=k;j++)
		g[u][j]=(g[fa][j]+g[fa][j-1]+f[fa][j-1]+f[fa][j]-f[u][j]-2*f[u][j-1]-(j==1?0:f[u][j-2]))%Mod;
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
		if(e[tmp].to!=fa) dfs2(e[tmp].to,u);
}

void Init()
{
	stl[0][0]=1;
	for(int i=1;i<=k;i++)
		for(int j=1;j<=i;j++)
			stl[i][j]=(stl[i-1][j-1]+stl[i-1][j]*j%Mod)%Mod;
	fac[0]=1;
	for(int i=1;i<=n;i++) fac[i]=fac[i-1]*i%Mod;
}

int main()
{
	int u,v,L,now,A,B,Q,tmp;
	scanf("%d%d%d",&n,&k,&L);
	scanf("%d%d%d%d",&now,&A,&B,&Q);
	for(int i=1;i<n;i++)
	{
		now=(now*A+B)%Q;
		tmp=(i<L)?i:L;
		u=i-now%tmp;v=i+1;
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs1(1,0);dfs2(1,0);Init();
	for(int i=1;i<=n;i++)
	{
		int ans=0;
		for(int j=1;j<=k;j++)
			ans=(ans+stl[k][j]*fac[j]%Mod*(f[i][j]+g[i][j]))%Mod;
		printf("%d\n",(ans+Mod)%Mod);
	}
	return 0;
}
