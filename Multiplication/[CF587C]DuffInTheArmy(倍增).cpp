#include<bits/stdc++.h>
using namespace std;

int depth[100010];
int fa[200010][20];
int num[200010][20][15];
int sz[200010][20];
struct Edge{int to,next;} e[200010];
int h[100010],sum=0,n,m,q;
int ans[15],tp[15];

void add_edge(int u,int v)
{
	sum++;
	e[sum].to=v;
	e[sum].next=h[u];
	h[u]=sum;
}

void dfs(int u,int la,int dep)
{
	fa[u][0]=la;
	depth[u]=dep;
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		if(e[tmp].to==la) continue;
		dfs(e[tmp].to,u,dep+1);
	}
}

void merge(int *a,int *b,int *c,int m1,int m2)
{
	int p1=1,p2=1;
	for(int i=1;i<=10;i++)
		if((a[p1]<b[p2]&&p1<=m1)||p2>m2) c[i]=a[p1],p1++;
		else if(p2<=m2) c[i]=b[p2],p2++;
}

int main()
{
	int u,v,a;
	cin>>n>>m>>q;
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&u,&v);
		add_edge(u,v);
		add_edge(v,u);
	}
	dfs(1,0,1);
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&u);
		int p=sz[u][0]+1;
		for(int j=1;j<=sz[u][0]&&j<=10;j++)
			if(num[u][0][j]>i)
			{
				for(int k=j;k<=sz[u][0]&&k<=10;k++)
					num[u][0][k+1]=num[u][0][k];
				p=j;
				break;
			}
		if(sz[u][0]<10) sz[u][0]++;
		num[u][0][p]=i;
	}
	for(int j=1;j<=17;j++)
		for(int i=1;i<=n;i++)
		{
			fa[i][j]=fa[fa[i][j-1]][j-1];
			merge(num[i][j-1],num[fa[i][j-1]][j-1],num[i][j],sz[i][j-1],sz[fa[i][j-1]][j-1]);
			sz[i][j]=min(sz[i][j-1]+sz[fa[i][j-1]][j-1],10);
		}
	for(int i=1;i<=q;i++)
	{
		scanf("%d%d%d",&u,&v,&a);
		int p1=u,p2=v;
		int cnt=0;
		if(depth[p1]<depth[p2]) swap(p1,p2);
		for(int j=17;j>=0;j--)
			if(depth[fa[p1][j]]>=depth[p2])
			{
				merge(num[p1][j],ans,tp,sz[p1][j],cnt);
				cnt=min(sz[p1][j]+cnt,10);
				for(int k=1;k<=cnt;k++) ans[k]=tp[k];
				p1=fa[p1][j];
			}
		for(int j=17;j>=0;j--)
			if(fa[p1][j]!=fa[p2][j])
			{
				merge(num[p1][j],ans,tp,sz[p1][j],cnt);
				cnt=min(sz[p1][j]+cnt,10);
				for(int k=1;k<=cnt;k++) ans[k]=tp[k];
				p1=fa[p1][j];
				merge(num[p2][j],ans,tp,sz[p2][j],cnt);
				cnt=min(sz[p2][j]+cnt,10);
				for(int k=1;k<=cnt;k++) ans[k]=tp[k];
				p2=fa[p2][j];
			}
		if(p1!=p2)
		{
			merge(num[p1][1],ans,tp,sz[p1][1],cnt);
			cnt=min(sz[p1][1]+cnt,10);
			for(int k=1;k<=cnt;k++) ans[k]=tp[k];
			merge(num[p2][0],ans,tp,sz[p2][0],cnt);
			cnt=min(sz[p2][0]+cnt,10);
			for(int k=1;k<=cnt;k++) ans[k]=tp[k];
			p1=fa[p1][0];
		}
		else
		{
			merge(num[p1][0],ans,tp,sz[p1][0],cnt);
			cnt=min(sz[p1][0]+cnt,10);
			for(int k=1;k<=cnt;k++) ans[k]=tp[k];
		}
		cnt=min(cnt,a);
		printf("%d ",cnt);
		for(int j=1;j<=cnt;j++) printf("%d ",ans[j]);
		putchar('\n');
	}
	return 0;
}
