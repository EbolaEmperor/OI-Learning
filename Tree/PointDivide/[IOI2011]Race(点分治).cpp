#include<bits/stdc++.h>
#define INF 0x7fffffff
using namespace std;

struct Edge{int to,capa,next;} e[400010];
int h[200010],sum=-1,k;
int smer,sumary,mx,root;
int siz[200010];
struct Dist{int len,num;} dis[1000010];
int ans[1000010];
bool done[200010];

void add_edge(int u,int v,int w)
{
	sum++;
	e[sum].to=v;
	e[sum].next=h[u];
	e[sum].capa=w;
	h[u]=sum;
}

bool operator < (Dist a,Dist b){return a.len<b.len||(a.len==b.len&&a.num<b.num);}

void dfs(int u,int fa,int w,int deep)
{
	dis[++sumary].len=w;
	dis[sumary].num=deep;
	for(int tmp=h[u];tmp!=-1;tmp=e[tmp].next)
	{
		if(e[tmp].to==fa||done[e[tmp].to]) continue;
		dfs(e[tmp].to,u,w+e[tmp].capa,deep+1);
	}
}

void solve(int u,int w,int add,int deep)
{
	sumary=0;
	dfs(u,-1,w,deep);
	sort(dis+1,dis+1+sumary);
	int i=1,j=sumary;
	while(i<=j)
	{
		while(i<j&&dis[i].len+dis[j].len>k) j--;
		for(int kk=j;dis[i].len+dis[kk].len==k;kk--) ans[dis[i].num+dis[kk].num]+=add;
		i++;
	}
}

void GetRoot(int u,int fa)
{
	siz[u]=1;
	int mxson=0;
	for(int tmp=h[u];tmp!=-1;tmp=e[tmp].next)
	{
		if(done[e[tmp].to]||e[tmp].to==fa) continue;
		GetRoot(e[tmp].to,u);
		siz[u]+=siz[e[tmp].to];
		mxson=max(mxson,siz[e[tmp].to]);
	}
	mxson=max(mxson,smer-siz[u]);
	if(mxson<mx) mx=mxson,root=u;
}

void Divide(int u)
{
	done[u]=1;
	solve(u,0,1,0);
	for(int tmp=h[u];tmp!=-1;tmp=e[tmp].next)
	{
		if(done[e[tmp].to]) continue;
		solve(e[tmp].to,e[tmp].capa,-1,1);
		mx=INF;smer=siz[e[tmp].to];root=0;
		GetRoot(e[tmp].to,-1);
		Divide(root);
	}
}

int main()
{
	int n,a,b,c;
	cin>>n>>k;
	for(int i=0;i<=n;i++) h[i]=-1;
	for(int i=1;i<n;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		add_edge(a,b,c);
		add_edge(b,a,c);
	}
	memset(done,0,sizeof(done));
	mx=INF;root=0;smer=n;
	GetRoot(1,-1);
	Divide(root);
	for(int i=1;i<=2*n;i++)
		if(ans[i]){printf("%d\n",i);return 0;}
	puts("-1");
	return 0;
}
