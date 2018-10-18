#include<bits/stdc++.h>
#define INF 0x3fffffff
using namespace std;

typedef long long LL;
struct Edge{int to,next;} e[2000010];
int h[1000010],sum=0;
int sta[1000010],top=0;
int mul[1000010][20],dep[1000010];
int dfn[1000010],dfs_clock=0;
int a[1000010],m;
bool chos[1000010];
int size[1000010],mn[1000010],mx[1000010];
LL f[1000010];
int ans1,ans2;

void add_edge(int u,int v)
{
	if(u==v) return;
	sum++;
	e[sum].to=v;
	e[sum].next=h[u];
	h[u]=sum;
}

void pre(int u)
{
	dfn[u]=++dfs_clock;
	for(int j=1;j<=19;j++) mul[u][j]=mul[mul[u][j-1]][j-1];
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		if(e[tmp].to==mul[u][0]) continue;
		mul[e[tmp].to][0]=u;
		dep[e[tmp].to]=dep[u]+1;
		pre(e[tmp].to);
	}
}

int LCA(int p1,int p2)
{
	if(dep[p1]<dep[p2]) swap(p1,p2);
	for(int j=19;j>=0;j--)
		if(dep[mul[p1][j]]>=dep[p2]) p1=mul[p1][j];
	if(p1==p2) return p1;
	for(int j=19;j>=0;j--)
		if(mul[p1][j]!=mul[p2][j]) p1=mul[p1][j],p2=mul[p2][j];
	if(p1!=p2) p1=mul[p1][0];
	return p1;
}

bool cmp(const int &a,const int &b){return dfn[a]<dfn[b];}

void dfs(int u)
{
	size[u]=chos[u];mx[u]=0;mn[u]=INF;f[u]=0;
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		int v=e[tmp].to,d=dep[v]-dep[u];
		dfs(v);size[u]+=size[v];
		ans1=min(ans1,mn[u]+mn[v]+d);
		mn[u]=min(mn[u],mn[v]+d);
		ans2=max(ans2,mx[u]+mx[v]+d);
		mx[u]=max(mx[u],mx[v]+d);
		f[u]+=f[v]+(LL)size[v]*(m-size[v])*d;
	}
	if(chos[u]) ans1=min(ans1,mn[u]),ans2=max(ans2,mx[u]),mn[u]=0;
	h[u]=0;
}

void work()
{
	sum=0;scanf("%d",&m);
	for(int i=1;i<=m;i++) scanf("%d",a+i),chos[a[i]]=1;
	sort(a+1,a+1+m,cmp);
	for(int i=1;i<=m;i++)
	{
		if(top==0){sta[++top]=a[i];continue;}
		int f=LCA(sta[top],a[i]);
		while(dep[f]<dep[sta[top]])
		{
			if(dep[f]>=dep[sta[top-1]])
			{
				add_edge(f,sta[top]);top--;
				if(f!=sta[top]) sta[++top]=f;
				break;
			}
			add_edge(sta[top-1],sta[top]);top--;
		}
		if(a[i]!=sta[top]) sta[++top]=a[i];
	}
	while(top>1) add_edge(sta[top-1],sta[top]),top--;
	ans1=INF;ans2=0;dfs(sta[top]);
	printf("%lld %d %d\n",f[sta[top]],ans1,ans2);top--;
	for(int i=1;i<=m;i++) chos[a[i]]=0;
}

int main()
{
	int q,n,u,v;
	cin>>n;
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&u,&v);
		add_edge(u,v);
		add_edge(v,u);
	}
	dep[1]=1;pre(1);
	memset(h,0,sizeof(h));
	memset(chos,0,sizeof(chos));
	for(cin>>q;q;q--) work();
	return 0;
}
