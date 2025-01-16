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
struct Edge{int to,next;} e[N<<1];
int h[N],tot=0,n,m;
int col[N],sum[N],diff[N];
int s1,s2;

void add_edge(int u,int v)
{
	e[++tot].to=v;
	e[tot].next=h[u];
	h[u]=tot;
}

void dfs1(int u,int fa)
{
	sum[u]=col[u];
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		int v=e[tmp].to;
		if(v==fa) continue;
		if(col[v]){s1=u;s2=v;continue;}
		col[v]=-col[u];
		dfs1(v,u);
		sum[u]+=sum[v];
	}
}

void dfs2(int u,int fa)
{
	sum[u]=col[u];
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		int v=e[tmp].to;
		if(v==fa) continue;
		if(u==s1&&v==s2||u==s2&&v==s1) continue;
		dfs2(v,u);
		sum[u]+=sum[v];
		diff[u]+=diff[v];
	}
}

int gao()
{
	if(n&1) return -1;
	int ans=0;
	col[1]=1;dfs1(1,0);
	if(m==n-1)
	{
		if(sum[1]) return -1;
		for(int i=2;i<=n;i++)
			ans+=abs(sum[i]);
		return ans;
	}
	if(col[s1]==col[s2])
	{
		if(sum[1])
		{
			ans=abs(sum[1]/2);
			col[s1]-=sum[1]/2;
			col[s2]-=sum[1]/2;
			dfs2(1,0);
		}
		for(int i=2;i<=n;i++)
			ans+=abs(sum[i]);
		return ans;
	}
	if(sum[1]) return -1;
	diff[s1]=1;diff[s2]=-1;
	dfs2(1,0);
	static int c[N],cnt=0;
	for(int i=2;i<=n;i++)
		if(diff[i]) c[cnt++]=sum[i]*diff[i];
		else ans+=abs(sum[i]);
	nth_element(c,c+(cnt>>1),c+cnt);
	int x=c[cnt>>1];
	for(int i=0;i<cnt;i++)
		ans+=abs(c[i]-x);
	return ans+abs(x);
}

int main()
{
	int u,v;
	n=read();m=read();
	for(int i=1;i<=m;i++)
	{
		u=read();v=read();
		add_edge(u,v);
		add_edge(v,u);
	}
	printf("%d\n",gao());
	return 0;
}
