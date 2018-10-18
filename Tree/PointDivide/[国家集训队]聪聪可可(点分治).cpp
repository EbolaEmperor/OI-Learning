#include<bits/stdc++.h>
#define INF 0x7fffffff
using namespace std;

struct Edge{int to,capa,next;} e[40010];
int h[20010],sum=0;
int sim[20010];
int ans=0;
int sumary,mx,root,smer;
int dis[20010];
bool done[20010];

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
	for(int i=1;i<sumary;i++)
		for(int j=i+1;j<=sumary;j++)
			if((dis[i]+dis[j])%3==0) ans+=add;
}

void GetRoot(int u,int fa)
{
	sim[u]=1;
	int mxson=0;
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		if(e[tmp].to==fa||done[e[tmp].to]) continue;
		GetRoot(e[tmp].to,u);
		sim[u]+=sim[e[tmp].to];
		mxson=max(mxson,sim[e[tmp].to]);
	}
	mxson=max(mxson,smer-sim[u]);
	if(mxson<mx) mx=mxson,root=u;
}

void Devide(int u)
{
	done[u]=1;
	solve(u,0,1);
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		if(done[e[tmp].to]) continue;
		solve(e[tmp].to,e[tmp].capa,-1);
		root=0;mx=INF;
		smer=sim[e[tmp].to];
		GetRoot(e[tmp].to,0);
		Devide(root);
	}
}

int Gcd(int a,int b){return b==0?a:Gcd(b,a%b);}

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
	mx=INF;root=0;smer=n;
	GetRoot(1,0);
	Devide(root);
	int k=Gcd(2*ans+n,n*n);
	printf("%d/%d\n",(2*ans+n)/k,n*n/k);
	return 0;
}
