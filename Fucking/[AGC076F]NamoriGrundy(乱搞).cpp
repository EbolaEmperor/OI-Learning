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
inline void upmin(int &x,const int &y){if(y<x) x=y;}

const int N=200010;
struct Edge{int to,next;} e[N];
int h[N],sum=0,n;
int fa[N],mex[N];
bool vis[N],loop[N];
bool have[N];

void add_edge(int u,int v)
{
	e[++sum].to=v;
	e[sum].next=h[u];
	h[u]=sum;
}

void dfs(int u)
{
	for(int t=h[u];t;t=e[t].next)
		if(!loop[e[t].to]) dfs(e[t].to);
	for(int t=h[u];t;t=e[t].next)
		if(!loop[e[t].to]) have[mex[e[t].to]]=1;
	while(have[mex[u]]) mex[u]++;
	for(int t=h[u];t;t=e[t].next)
		if(!loop[e[t].to]) have[mex[e[t].to]]=0;
}

int main()
{
	int n,x=1;
	n=read();
	for(int i=1;i<=n;i++)
	{
		fa[i]=read();
		add_edge(fa[i],i);
	}
	while(!vis[x]) vis[x]=1,x=fa[x];
	while(!loop[x]) loop[x]=1,x=fa[x];
	int mx=-1,mn=n+1,cnt=0;
	for(int i=1;i<=n;i++)
	{
		if(!loop[i]) continue;
		dfs(i);cnt++;
		upmax(mx,mex[i]);
		upmin(mn,mex[i]);
	}
	puts(mx==mn&&(cnt&1)?"IMPOSSIBLE":"POSSIBLE");
	return 0;
}
