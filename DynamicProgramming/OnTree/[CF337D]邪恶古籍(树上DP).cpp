#include<bits/stdc++.h>
using namespace std;

const int S=(1<<20)+5;
char buf[S],*H,*T;
inline char Get()
{
	if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
	if(H==T) return -1;return *H++;
}
inline int read()
{
	int x=0;char c=Get();
	while(!isdigit(c)) c=Get();
	while(isdigit(c)) x=x*10+c-'0',c=Get();
	return x;
}

inline void upmax(int &x,const int &y){if(y>x) x=y;}
inline int mymax(const int &x,const int &y){return x>y?x:y;}

const int N=100010;
struct Edge{int to,next;} e[N<<1];
int h[N],sum=0,n,m,d;
int mx1[N],mx2[N],dis[N];
bool fuck[N];

void add_edge(int u,int v)
{
	e[++sum].to=v;
	e[sum].next=h[u];
	h[u]=sum;
}

void dfs1(int u,int fa)
{
	if(fuck[u]) mx1[u]=mx2[u]=0;
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		int v=e[tmp].to;
		if(v==fa) continue;
		dfs1(v,u);
		if(mx1[v]+1>mx1[u])
			mx2[u]=mx1[u],mx1[u]=mx1[v]+1;
		else upmax(mx2[u],mx1[v]+1);
	}
}

void dfs2(int u,int fa)
{
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		int v=e[tmp].to;
		if(v==fa) continue;
		if(mx1[v]+1==mx1[u]) dis[v]=mymax(dis[u]+1,mx2[u]+1);
		else dis[v]=mymax(dis[u]+1,mx1[u]+1);
		dfs2(v,u);
	}
}

int main()
{
	int u,v;
	memset(mx1,128,sizeof(mx1));
	memset(mx2,128,sizeof(mx2));
	memset(dis,128,sizeof(dis));
	n=read();m=read();d=read();
	for(int i=1;i<=m;i++) fuck[read()]=1;
	for(int i=1;i<n;i++)
	{
		u=read();v=read();
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs1(1,0);dfs2(1,0);
	int ans=0;
	for(int i=1;i<=n;i++)
		ans+=(mx1[i]<=d&&dis[i]<=d);
	printf("%d\n",ans);
	return 0;
}
