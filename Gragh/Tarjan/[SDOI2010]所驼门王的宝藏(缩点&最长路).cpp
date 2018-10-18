#include<bits/stdc++.h>
#define pii pair<int,int>
using namespace std;

int read()
{
	int x=0;char c=getchar();
	while(c<'0'||c>'9') c=getchar();
	while(c>='0'&&c<='9')x=x*10+c-'0',c=getchar();
	return x;
}

const int N=100010;
struct Edge{int from,to,next;} e[100*N];
int h[N],sum=0;
struct DOOR{int x,y,ty,id;} door[N];
int pre[N],low[N],dfn=0;
int scc[N],w[N],tot=0;
stack<int> sta;
int deg[N],dp[N];
map<pii,int> H;
map<pii,bool> mat;
map<pii,bool>::iterator it;

bool cmp1(const DOOR &a,const DOOR &b)
{
	if(a.x!=b.x) return a.x<b.x;
	if(a.ty==1) return 1;
	if(b.ty==1) return 0;
	return a.y<b.y;
}

bool cmp2(const DOOR &a,const DOOR &b)
{
	if(a.y!=b.y) return a.y<b.y;
	if(a.ty==2) return 1;
	if(b.ty==2) return 0;
	return a.x<b.x;
}

void add_edge(int u,int v)
{
	sum++;
	e[sum].from=u;
	e[sum].to=v;
	e[sum].next=h[u];
	h[u]=sum;
}

void Tarjan(int u)
{
	pre[u]=low[u]=++dfn;
	sta.push(u);
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
		if(!pre[e[tmp].to])
		{
			Tarjan(e[tmp].to);
			low[u]=min(low[u],low[e[tmp].to]);
		}
		else if(!scc[e[tmp].to]) low[u]=min(low[u],pre[e[tmp].to]);
	if(pre[u]==low[u])
	{
		int o;
		tot++;
		do{
			o=sta.top();
			scc[o]=tot;
			w[tot]++;
			sta.pop();
		}while(u!=o);
	}
}

void dfs(int u,int fa)
{
	if(dp[u]>w[u]) return;
	dp[u]=w[u];
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		int v=e[tmp].to;
		if(v==fa) continue;
		dfs(v,u);
		dp[u]=max(dp[u],dp[v]+w[u]);
	}
}

int main()
{
	int n=read(),r=read(),c=read();
	for(int i=1;i<=n;i++)
	{
		door[i].x=read();
		door[i].y=read();
		door[i].ty=read();
		door[i].id=i;
		H[pii(door[i].x,door[i].y)]=i;
	}
	sort(door+1,door+1+n,cmp1);
	int first=1,last=1;
	for(int i=1;i<=n;i++)
		if(door[i].x!=door[i+1].x)
		{
			if(last!=first) add_edge(door[last].id,door[first].id);
			last=first=i+1;
		}
		else
		{
			if(door[last].ty==1) add_edge(door[last].id,door[i+1].id);
			if(door[i+1].ty==1) last=i+1;
			if(door[first].ty!=1) last=first=i+1;
		}
	sort(door+1,door+1+n,cmp2);
	first=1,last=1;
	for(int i=1;i<=n;i++)
		if(door[i].y!=door[i+1].y)
		{
			if(last!=first) add_edge(door[last].id,door[first].id);
			last=first=i+1;
		}
		else
		{
			if(door[last].ty==2) add_edge(door[last].id,door[i+1].id);
			if(door[i+1].ty==2) last=i+1;
			if(door[first].ty!=2) last=first=i+1;
		}
	for(int i=1;i<=n;i++)
		if(door[i].ty==3)
		{
			int x=door[i].x,y=door[i].y;
			if(H.count(pii(x-1,y-1))) add_edge(door[i].id,H[pii(x-1,y-1)]);
			if(H.count(pii(x-1,y))) add_edge(door[i].id,H[pii(x-1,y)]);
			if(H.count(pii(x-1,y+1))) add_edge(door[i].id,H[pii(x-1,y+1)]);
			if(H.count(pii(x,y-1))) add_edge(door[i].id,H[pii(x,y-1)]);
			if(H.count(pii(x,y+1))) add_edge(door[i].id,H[pii(x,y+1)]);
			if(H.count(pii(x+1,y-1))) add_edge(door[i].id,H[pii(x+1,y-1)]);
			if(H.count(pii(x+1,y))) add_edge(door[i].id,H[pii(x+1,y)]);
			if(H.count(pii(x+1,y+1))) add_edge(door[i].id,H[pii(x+1,y+1)]);
		}
	for(int i=1;i<=n;i++)
		if(!pre[i]) Tarjan(i);
	for(int i=1;i<=sum;i++)
	{
		int u=e[i].from,v=e[i].to;
		if(scc[u]!=scc[v]) mat[pii(scc[u],scc[v])]=1;
	}
	memset(h,0,sizeof(h));sum=0;
	for(it=mat.begin();it!=mat.end();it++)
	{
		add_edge(it->first.first,it->first.second);
		deg[it->first.second]++;
	}
	int ans=0;
	for(int i=1;i<=tot;i++)
		if(deg[i]==0)
		{
			dfs(i,0);
			ans=max(ans,dp[i]);
		}
	cout<<ans<<endl;
	return 0;
}
