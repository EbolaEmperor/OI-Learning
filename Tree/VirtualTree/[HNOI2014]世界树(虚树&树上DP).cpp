#include<bits/stdc++.h>
using namespace std;

int read()
{
	int x=0;
	char c=getchar();
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9') x=x*10+c-'0',c=getchar();
	return x;
}

struct Edge{int to,next;} e[600010],t[600010];
int h1[300010],h2[300010],sum1=0,sum2=0,n;
int mul[300010][20],dep[300010];
int dfn[300010],dfs_clock=0;
int a[300010],b[300010],belong[300010];
int sta[300010],top=0;
int dp[300010];
int c[300010],cnt;
int size[300010];
int g[300010];

int tot;

void add1(int u,int v){sum1++;e[sum1].to=v;e[sum1].next=h1[u];h1[u]=sum1;}
void add2(int u,int v){if(u==v) return;sum2++;t[sum2].to=v;t[sum2].next=h2[u];h2[u]=sum2;}

bool cmp(const int &x,const int &y){return dfn[x]<dfn[y];}

void pre(int u,int fa)
{
	size[u]=1;
	dfn[u]=++dfs_clock;
	for(int j=1;j<=18;j++) mul[u][j]=mul[mul[u][j-1]][j-1];
	for(int tmp=h1[u];tmp;tmp=e[tmp].next)
	{
		if(e[tmp].to==fa) continue;
		mul[e[tmp].to][0]=u;
		dep[e[tmp].to]=dep[u]+1;
		pre(e[tmp].to,u);
		size[u]+=size[e[tmp].to];
	}
}

int LCA(int p1,int p2)
{
	if(dep[p1]<dep[p2]) swap(p1,p2);
	for(int j=18;j>=0;j--)
		if(dep[mul[p1][j]]>=dep[p2]) p1=mul[p1][j];
	if(p1==p2) return p1;
	for(int j=18;j>=0;j--)
		if(mul[p1][j]!=mul[p2][j]) p1=mul[p1][j],p2=mul[p2][j];
	if(p1!=p2) p1=mul[p1][0];
	return p1;
}

int getdist(int x,int y){return dep[x]+dep[y]-2*dep[LCA(x,y)];}

void dfs1(int u,int fa)
{
	c[++cnt]=u;g[u]=size[u];
	for(int tmp=h2[u];tmp;tmp=t[tmp].next)
	{
		int v=t[tmp].to;
		if(v==fa) continue;
		dfs1(v,u);
		if(belong[v]==0) continue;
		if(belong[u]==0){belong[u]=belong[v];continue;}
		int d1=getdist(u,belong[u]),d2=getdist(u,belong[v]);
		if((d1>d2)||(d1==d2&&belong[v]<belong[u])) belong[u]=belong[v];
	}
}

void dfs2(int u,int fa)
{
	for(int tmp=h2[u];tmp;tmp=t[tmp].next)
	{
		int v=t[tmp].to;
		if(v==fa) continue;
		if(belong[v]==0) belong[v]=belong[u];
		else
		{
			int d1=getdist(belong[v],v),d2=getdist(belong[u],v);
			if((d1>d2)||(d1==d2&&belong[u]<belong[v])) belong[v]=belong[u];
		}
		dfs2(v,u);
	}
}

void solve(int fa,int u)
{
	int son=u,mid=u,tem;
	for(int j=18;j>=0;j--)
		if(dep[mul[son][j]]>dep[fa]) son=mul[son][j];
	g[fa]-=size[son];
	if(belong[fa]==belong[u]){dp[belong[fa]]+=size[son]-size[u];return;}
	for(int j=18;j>=0;j--)
	{
		tem=mul[mid][j];
		if(dep[tem]<=dep[fa]) continue;
		int d1=getdist(tem,belong[fa]),d2=getdist(tem,belong[u]);
		if((d1>d2)||(d1==d2&&belong[u]<belong[fa])) mid=tem;
	}
	dp[belong[fa]]+=size[son]-size[mid];
	dp[belong[u]]+=size[mid]-size[u];
}

void work()
{
	cnt=sum2=0;
	int m=read();
	for(int i=1;i<=m;i++) a[i]=read(),belong[a[i]]=a[i],b[i]=a[i];
	sort(a+1,a+1+m,cmp);
	if(belong[1]!=1) sta[++top]=1;
	for(int i=1;i<=m;i++)
	{
		if(top==0){sta[++top]=a[i];continue;}
		int f=LCA(a[i],sta[top]);
		while(true)
		{
			if(dep[sta[top-1]]<=dep[f])
			{
				add2(f,sta[top]);top--;
				if(sta[top]!=f) sta[++top]=f;
				break;
			}
			add2(sta[top-1],sta[top]);top--;
		}
		if(sta[top]!=a[i]) sta[++top]=a[i];
	}
	while(top>1) add2(sta[top-1],sta[top]),top--;top--;
	dfs1(1,0);
	dfs2(1,0);
	for(int i=1;i<=cnt;i++)
		for(int tmp=h2[c[i]];tmp;tmp=t[tmp].next)
			solve(c[i],t[tmp].to);
	for(int i=1;i<=cnt;i++) dp[belong[c[i]]]+=g[c[i]];
	for(int i=1;i<=m;i++) printf("%d ",dp[b[i]]);putchar('\n');
	for(int i=1;i<=cnt;i++) dp[c[i]]=h2[c[i]]=g[c[i]]=belong[c[i]]=0;
}

int main()
{
	int q,u,v;
	n=read();
	for(int i=1;i<n;i++)
	{
		u=read();v=read();
		add1(u,v);
		add1(v,u);
	}
	dep[1]=1;
	pre(1,0);
	q=read();
	for(int i=1;i<=q;i++) work();
	return 0;
}
