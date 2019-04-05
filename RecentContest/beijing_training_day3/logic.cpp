#include<bits/stdc++.h>
using namespace std;

const int N=400010;
vector<int> g[N];
int dfn[N],low[N],scc[N],sdfc,sccn;
stack<int> stk;
int dfn1[N],dfn2[N],idx[N],dfc;
int top[N],fa[N],sz[N];
int vtx[N],ind[N],tot;
int p[N],q[N],a[N],b[N];
int ch[N][2];
int n,m,ans[N];

void Tarjan(int u)
{
	stk.push(u);
	low[u]=dfn[u]=++sdfc;
	for(int v : g[u])
		if(!dfn[v]) Tarjan(v),low[u]=min(low[u],low[v]);
		else if(!scc[v]) low[u]=min(low[u],dfn[v]);
	if(dfn[u]==low[u])
	{
		int o;sccn++;
		do{
			o=stk.top();
			scc[o]=sccn;
			stk.pop();
		}while(o!=u);
	}
}

bool check(int u)
{
	tot=0;
	for(int i=dfn1[u];i<=dfn2[u];i++)
	{
		int x=idx[i];
		if(!ind[p[x]]) vtx[ind[p[x]]=++tot]=p[x];
		if(!ind[q[x]]) vtx[ind[q[x]]=++tot]=q[x];
		g[p[x]+n*a[x]].push_back(q[x]+n*(b[x]^1));
		g[q[x]+n*b[x]].push_back(p[x]+n*(a[x]^1));
	}
	for(int i=1;i<=tot;i++)
	{
		if(!dfn[vtx[i]]) Tarjan(vtx[i]);
		if(!dfn[vtx[i]+n]) Tarjan(vtx[i]+n);
	}
	bool res=1;
	for(int i=1;i<=tot;i++)
		if(scc[vtx[i]]==scc[vtx[i]+n]) res=0;
	for(int i=1;i<=tot;i++)
	{
		int x=vtx[i];
		g[x].clear();
		g[x+n].clear();
		scc[x]=dfn[x]=low[x]=0;
		scc[x+n]=dfn[x+n]=low[x+n]=0;
		ind[x]=0;
	}
	sdfc=sccn=0;
	return res;
}

void dfs1(int u)
{
	sz[u]=1;
	if(u<=m) return;
	dfs1(ch[u][0]);
	dfs1(ch[u][1]);
	sz[u]+=sz[ch[u][0]]+sz[ch[u][1]];
	if(sz[ch[u][0]]<sz[ch[u][1]])
		swap(ch[u][0],ch[u][1]);
}

void dfs2(int u,int tp)
{
	top[u]=tp;
	if(u<=m)
	{
		dfn1[u]=dfn2[u]=++dfc;
		idx[dfc]=u;
		return;
	}
	dfs2(ch[u][0],tp);
	dfs2(ch[u][1],ch[u][1]);
	dfn1[u]=dfn1[ch[u][0]];
	dfn2[u]=dfn2[ch[u][1]];
}

void dfs(int u)
{
	if(u<=m) return;
	ans[u]=1;
	dfs(ch[u][0]);
	dfs(ch[u][1]);
}

void gao(int u)
{
	static int ao[N];int cnt=0;
	for(int x=u;x>m;x=ch[x][0]) ao[++cnt]=x;
	int l=1,r=cnt,mid;
	while(l<=r)
	{
		mid=(l+r)/2;
		if(check(ao[mid])) r=mid-1;
		else l=mid+1;
	}
	for(int i=1;i<l;i++) ans[ao[i]]=0;
	dfs(ao[l]);
}

void gaogaogao()
{
	dfs1(2*m-1);
	dfs2(2*m-1,2*m-1);
	static int ao[N];
	for(int i=m+1;i<2*m;i++) ao[i-m]=i;
	sort(ao+1,ao+m,[](int a,int b){return sz[ch[a][0]]>sz[ch[b][0]];});
	memset(ans,-1,sizeof(ans));
	for(int i=1;i<m;i++)
		if(ans[ao[i]]==-1) gao(ao[i]);
}

int main()
{
	scanf("%d%d",&n,&m);
	for(int i=1,x,y;i<=m;i++)
	{
		scanf("%d%d",&x,&y);
		p[i]=abs(x);a[i]=(x<0);
		q[i]=abs(y);b[i]=(y<0);
	}
	for(int i=m+1;i<2*m;i++)
		scanf("%d%d",ch[i],ch[i]+1);
	gaogaogao();
	for(int i=m+1;i<2*m;i++)
		printf("%d",ans[i]);
	return puts(""),0;
}
