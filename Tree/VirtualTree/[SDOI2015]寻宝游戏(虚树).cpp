#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
struct Edge{int to,next;LL capa;} e[200010];
int h[100010],sum=0;
int mul[100010][20],dep[100010];
LL dis[100010];
int dfn[100010],dfs_clock=0,idex[100010];
bool has[100010];
set<int> s;
set<int>::iterator it1,it2,ed;

void add_edge(int u,int v,int w)
{
	sum++;
	e[sum].to=v;
	e[sum].capa=(LL)w;
	e[sum].next=h[u];
	h[u]=sum;
}

void dfs(int u)
{
	dfn[u]=++dfs_clock;
	idex[dfn[u]]=u;
	for(int j=1;j<=16;j++) mul[u][j]=mul[mul[u][j-1]][j-1];
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		if(e[tmp].to==mul[u][0]) continue;
		mul[e[tmp].to][0]=u;
		dis[e[tmp].to]=dis[u]+e[tmp].capa;
		dep[e[tmp].to]=dep[u]+1;
		dfs(e[tmp].to);
	}
}

int LCA(int p1,int p2)
{
	if(dep[p1]<dep[p2]) swap(p1,p2);
	for(int j=16;j>=0;j--)
		if(dep[mul[p1][j]]>=dep[p2]) p1=mul[p1][j];
	for(int j=16;j>=0;j--)
		if(mul[p1][j]!=mul[p2][j]) p1=mul[p1][j],p2=mul[p2][j];
	if(p1!=p2) p1=mul[p1][0];
	return p1;
}

LL getdist(int a,int b){return dis[a]+dis[b]-2*dis[LCA(a,b)];}

int main()
{
	int n,m,u,v,w,l,r;
	cin>>n>>m;
	for(int i=1;i<n;i++)
	{
		scanf("%d%d%d",&u,&v,&w);
		add_edge(u,v,w);
		add_edge(v,u,w);
	}
	dfs(1);
	memset(has,0,sizeof(has));
	LL ans=0;
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&u);
		if(!has[u]) s.insert(dfn[u]);
		it1=it2=s.lower_bound(dfn[u]);
		if(it1==s.begin()) it1=s.end();it1--;l=*it1;
		ed=s.end();ed--;
		if(it2==ed) r=*s.begin();
		else it2++,r=*it2;
		if(!has[u])
		{
			has[u]=1;
			ans-=getdist(idex[l],idex[r]);
			ans+=getdist(idex[l],u)+getdist(idex[r],u);
		}
		else
		{
			has[u]=0;
			s.erase(dfn[u]);
			ans-=getdist(idex[l],u)+getdist(idex[r],u);
			ans+=getdist(idex[l],idex[r]);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
