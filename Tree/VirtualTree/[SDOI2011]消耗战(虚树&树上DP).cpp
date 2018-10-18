#include<bits/stdc++.h>
#define INF (1ll<<60)
using namespace std;

typedef long long LL;
struct Edge{int to,capa,next;} e[500010],t[500010];
int h1[250010],sum1=0,h2[250010],sum2=0,n;
int mul[250010][20],dep[250010];
int dfn[250010],dfs_clock=0;
LL mn[250010],f[250010];
int a[250010];
int sta[250010],top=0;

void add1(int u,int v,int w){sum1++;e[sum1].to=v;e[sum1].capa=w;e[sum1].next=h1[u];h1[u]=sum1;}
void add2(int u,int v){if(u==v) return;sum2++;t[sum2].to=v;t[sum2].next=h2[u];h2[u]=sum2;}

bool cmp(const int &x,const int &y){return dfn[x]<dfn[y];}

void pre(int u)
{
	dfn[u]=++dfs_clock;
	for(int j=1;j<=18;j++) mul[u][j]=mul[mul[u][j-1]][j-1];
	for(int tmp=h1[u];tmp;tmp=e[tmp].next)
	{
		if(e[tmp].to==mul[u][0]) continue;
		mul[e[tmp].to][0]=u;
		dep[e[tmp].to]=dep[u]+1;
		mn[e[tmp].to]=min(mn[u],(LL)e[tmp].capa);
		pre(e[tmp].to);
	}
}

int LCA(int p1,int p2)
{
	if(dep[p1]<dep[p2]) swap(p1,p2);
	for(int j=18;j>=0;j--)
		if(dep[mul[p1][j]]>=dep[p2]) p1=mul[p1][j];
	for(int j=18;j>=0;j--)
		if(mul[p1][j]!=mul[p2][j]) p1=mul[p1][j],p2=mul[p2][j];
	if(p1!=p2) p1=mul[p1][0];
	return p1;
}

void dp(int u)
{
	f[u]=mn[u];
	LL sum=0;
	for(int tmp=h2[u];tmp;tmp=t[tmp].next)
	{
		dp(t[tmp].to);
		sum+=f[t[tmp].to];
	}
	h2[u]=0;
	if(sum!=0&&sum<f[u]) f[u]=sum;
}

void work()
{
	sum2=0;
	int k;
	scanf("%d",&k);
	for(int i=1;i<=k;i++) scanf("%d",a+i);
	sort(a+1,a+1+k,cmp);
	int tot=1;
	for(int i=2;i<=k;i++)
		if(LCA(a[i],a[tot])!=a[tot]) a[++tot]=a[i];
	sta[++top]=1;
	for(int i=1;i<=tot;i++)
	{
		int now=a[i],f=LCA(now,sta[top]);
		while(true)
		{
			if(dep[f]>=dep[sta[top-1]])
			{
				add2(f,sta[top--]);
				if(sta[top]!=f) sta[++top]=f;
				break;
			}
			add2(sta[top-1],sta[top]);top--;
		}
		if(sta[top]!=now) sta[++top]=now;
	}
	while(--top) add2(sta[top],sta[top+1]);
	dp(1);
	printf("%lld\n",f[1]);
}

int main()
{
	int m,u,v,w;
	cin>>n;
	for(int i=1;i<n;i++)
	{
		scanf("%d%d%d",&u,&v,&w);
		add1(u,v,w);
		add1(v,u,w);
	}
	mn[1]=INF;dep[1]=1;
	pre(1);
	cin>>m;
	for(int i=1;i<=m;i++) work();
	return 0;
}
