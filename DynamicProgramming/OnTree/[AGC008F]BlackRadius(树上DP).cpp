#include<bits/stdc++.h>
using namespace std;

const int S=1<<20;
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
inline void reads(char *s)
{
	char c=Get();int tot=0;
	while(c<'0'||c>'1') c=Get();
	while(c>='0'&&c<='1') s[++tot]=c,c=Get();
	s[++tot]='\0';
}

inline void upmin(int &x,const int &y){if(y<x) x=y;}
inline void upmax(int &x,const int &y){if(y>x) x=y;}
inline int mymin(const int &x,const int &y){return x<y?x:y;}

typedef long long LL;
const int N=200010;
struct Edge{int to,next;} e[N<<1];
int h[N],sum=0,n;
int mx1[N],mx2[N],mn[N],num[N];
char black[N];
long long ans=0;

inline void add_edge(int u,int v)
{
	e[++sum].to=v;
	e[sum].next=h[u];
	h[u]=sum;
}

void dfs1(int u,int last)
{
	if(black[u]=='1') mn[u]=0,num[u]++;
	for(int t=h[u];t;t=e[t].next)
	{
		int v=e[t].to;
		if(v==last) continue;
		dfs1(v,u);
		num[u]+=num[v];
		if(mx1[v]+1>mx1[u])
		{
			mx2[u]=mx1[u];
			mx1[u]=mx1[v]+1;
		}
		else upmax(mx2[u],mx1[v]+1);
		if(num[v]) upmin(mn[u],mx1[v]+1);
	}
}

void dfs2(int u,int last)
{
	for(int t=h[u];t;t=e[t].next)
	{
		int v=e[t].to;
		if(v==last) continue;
		int len=((mx1[u]==mx1[v]+1)?mx2[u]:mx1[u])+1;
		if(len>mx1[v]) mx2[v]=mx1[v],mx1[v]=len;
		else upmax(mx2[v],len);
		if(num[v]<num[1]) upmin(mn[v],len);
		dfs2(v,u);
	}
	int up=mymin(mx2[u]+1,mx1[u]-1);
	if(up>=mn[u]) ans+=up-mn[u]+1;
}

int main()
{
	int x,y,up;
	n=read();
	for(int i=1;i<n;i++)
	{
		x=read();y=read();
		add_edge(x,y);
		add_edge(y,x);
	}
	reads(black);
	memset(mn,0x3f,sizeof(mn));
	dfs1(1,0);dfs2(1,0);
	printf("%lld\n",ans+1);
	return 0;
}
