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

const int N=200010;
struct Edge{int to,capa,next;} e[N];
int h[N],sum=0,n,m;
bool vis[N];
int cmt,cnt,col[N],c[3];
bool falun;

inline int color(const int &x)
{
	if(x>=3) return x-3;
	if(x<0) return x+3;
	return x;
}

void add_edge(int u,int v,int w)
{
	e[++sum].to=v;
	e[sum].capa=w;
	e[sum].next=h[u];
	h[u]=sum;
}

void dfs(int u)
{
	c[col[u]]++;vis[u]=1;cnt++;
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		cmt+=(e[tmp].capa==1);
		int v=e[tmp].to;
		if(!vis[v]) col[v]=color(col[u]+e[tmp].capa),dfs(v);
		else if(col[v]!=color(col[u]+e[tmp].capa)) falun=0;
	}
}

int main()
{
	int u,v;
	n=read();m=read();
	for(int i=1;i<=m;i++)
	{
		u=read();v=read();
		add_edge(u,v,1);
		add_edge(v,u,-1);
	}
	long long ans=0;
	for(int i=1;i<=n;i++)
	{
		if(vis[i]) continue;
		memset(c,0,sizeof(c));
		cmt=cnt=0;falun=1;
		dfs(i);
		if(!falun) ans+=1ll*cnt*cnt;
		else if(c[0]&&c[1]&&c[2]) ans+=1ll*c[0]*c[1]+1ll*c[1]*c[2]+1ll*c[2]*c[0];
		else ans+=cmt;
	}
	printf("%lld\n",ans);
	return 0;
}
