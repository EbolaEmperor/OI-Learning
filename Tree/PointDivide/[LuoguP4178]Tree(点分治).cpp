#include<bits/stdc++.h>
#define INF 0x7fffffff
using namespace std;

struct Edge{int to,capa,next;} e[80010];
int h[40010],sum=0;
int sim[40010];
int dis[40010];
bool done[40010];
int mx,root,smer,sumary;
int ans=0,k;

void add_edge(int u,int v,int w)
{
	sum++;
	e[sum].to=v;
	e[sum].capa=w;
	e[sum].next=h[u];
	h[u]=sum;
}

void dfs(int u,int fa,int w)
{
	if(w>k) return;
	dis[++sumary]=w;
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		if(e[tmp].to==fa||done[e[tmp].to]) continue;
		dfs(e[tmp].to,u,w+e[tmp].capa);
	}
}

void solve(int u,int w,int add)
{
	sumary=0;
	dfs(u,0,w);
	sort(dis+1,dis+1+sumary);
	int i=1,j=sumary;
	while(i<j)
		if(dis[i]+dis[j]<=k) ans+=add*(j-i),i++;
		else j--;
}

void GetRoot(int u,int fa)
{
	int mxson=0;
	sim[u]=1;
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		if(done[e[tmp].to]||e[tmp].to==fa) continue;
		GetRoot(e[tmp].to,u);
		sim[u]+=sim[e[tmp].to];
		mxson=max(mxson,sim[e[tmp].to]);
	}
	mxson=max(mxson,smer-sim[u]);
	if(mxson<mx) mx=mxson,root=u;
}

void Divide(int u)
{
	done[u]=1;
	solve(u,0,1);
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		if(done[e[tmp].to]) continue;
		solve(e[tmp].to,e[tmp].capa,-1);
		mx=INF;root=0;
		smer=sim[e[tmp].to];
		GetRoot(e[tmp].to,0);
		Divide(root);
	}
}

int main()
{
	memset(done,0,sizeof(done));
	int n,a,b,c;
	cin>>n;
	for(int i=1;i<n;i++)
	{
		scanf("%d%d%d",&a,&b,&c);
		add_edge(a,b,c);
		add_edge(b,a,c);
	}
	cin>>k;
	mx=INF;root=0;smer=n;
	GetRoot(1,0);
	Divide(root);
	cout<<ans<<endl;
	return 0;
}
