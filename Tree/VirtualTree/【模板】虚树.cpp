#include<bits/stdc++.h>
using namespace std;

const int N=100010;
struct Edge{int to,capa,next;} e[N<<1];
int h[N],sum=0,n,m;
int fa[N],dep[N],top[N],dfn[N],clk=0;
int hson[N],size[N],dis[N];
int sta[N],st,a[N];

bool cmp(int a,int b){return dfn[a]<dfn[b];}

void add_edge(int u,int v,int w)
{
	e[++sum].to=v;
	e[sum].capa=w;
	e[sum].next=h[u];
	h[u]=sum;
}

void dfs1(int u,int la)
{
	size[u]=0;int mx=0;
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		int v=e[tmp].to;
		if(v==la) continue;
		dep[v]=dep[u]+1;
		dis[v]=dis[u]+e[tmp].capa;
		dfs1(v,u);fa[v]=u;
		size[u]+=size[v];
		if(size[v]>mx) mx=size[v],hson[u]=v;
	}
}

void dfs2(int u,int tp)
{
	top[u]=tp;dfn[u]=++clk;
	if(hson[u]) dfs2(hson[u],tp);
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
		if(e[tmp].to!=fa[u]&&e[tmp].to!=hson[u])
			dfs2(e[tmp].to,e[tmp].to);
}

int LCA(int u,int v)
{
	while(top[u]!=top[v])
	{
		if(dep[top[u]]<dep[top[v]]) swap(u,v);
		u=fa[top[u]];
	}
	if(dep[u]>dep[v]) swap(u,v);
	return u;
}

void gao(int k)
{
	st=0;
	for(int i=1;i<=k;i++) scanf("%d",a+i);
	sort(a+1,a+1+k,cmp);
	int ans=0;
	for(int i=1;i<=k;i++)
	{
		if(st==0){sta[++st]=a[i];continue;}
		int f=LCA(a[i],sta[st]);
		while(dep[f]<dep[sta[st]])
		{
			if(dep[f]>=dep[sta[st-1]])
			{
				ans+=dis[sta[st--]]-dis[f];
				if(f!=sta[st]) sta[++st]=f;
				break;
			}
			ans+=dis[sta[st]]-dis[sta[st-1]];st--;
		}
		if(a[i]!=sta[st]) sta[++st]=a[i];
	}
	for(;st;st--) ans+=dis[sta[st]]-dis[sta[st-1]];
	printf("%d\n",ans);
}

int main()
{
	int u,v,w,k;
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		scanf("%d%d%d",&u,&v,&w);
		add_edge(u,v,w);
		add_edge(v,u,w);
	}
	dep[1]=1;dfs1(1,0);dfs2(1,1);
	scanf("%d",&m);sum=0;
	memset(h,0,sizeof(h));
	while(m--) scanf("%d",&k),gao(k);
	return 0;
}
