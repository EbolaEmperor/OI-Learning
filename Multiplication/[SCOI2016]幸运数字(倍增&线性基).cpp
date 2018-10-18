#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=20010;
struct Edge{int to,next;} e[N<<1];
int h[N],sum=0;
int mul[16][N],dep[N];

struct Base
{
	LL b[65];
	Base(){memset(b,0,sizeof(b));}
	void insert(LL x)
	{
		for(int i=60;i>=0;i--)
			if(x&(1ll<<i))
			{
				if(b[i]) x^=b[i];
				else{b[i]=x;break;}
			}
	}
	void merge(Base &a)
	{
		for(int i=60;i>=0;i--)
			if(a.b[i]) insert(a.b[i]);
			//The "if" made my program from 60s+ down to 30s-??? 
	}
	LL query()
	{
		LL ans=0;
		for(int i=60;i>=0;i--)
			if((ans^b[i])>ans) ans^=b[i];
		return ans;
	}
} num[16][N];

void add_edge(int u,int v)
{
	e[++sum].to=v;
	e[sum].next=h[u];
	h[u]=sum;
}

void dfs(int u,int fa)
{
	for(int j=1;j<=14;j++)
	{
		mul[j][u]=mul[j-1][mul[j-1][u]];
		num[j][u]=num[j-1][u];
		num[j][u].merge(num[j-1][mul[j-1][u]]);
	}
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		int v=e[tmp].to;
		if(v==fa) continue;
		mul[0][v]=u;
		dep[v]=dep[u]+1;
		dfs(v,u);
	}
}

Base LCA(int p1,int p2)
{
	Base ans;
	if(dep[p1]<dep[p2]) swap(p1,p2);
	for(int j=14;j>=0;j--)
		if(dep[mul[j][p1]]>=dep[p2])
		{
			ans.merge(num[j][p1]);
			p1=mul[j][p1];
		}
	for(int j=14;j>=0;j--)
		if(mul[j][p1]!=mul[j][p2])
		{
			ans.merge(num[j][p1]);
			p1=mul[j][p1];
			ans.merge(num[j][p2]);
			p2=mul[j][p2];
		}
	if(p1!=p2)
	{
		ans.merge(num[1][p1]);
		ans.merge(num[0][p2]);
	}
	else ans.merge(num[0][p1]);
	return ans;
}

int main()
{
	int n,q,u,v;LL x;
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)
	{
		scanf("%lld",&x);
		num[0][i].insert(x);
	}
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&u,&v);
		add_edge(u,v);
		add_edge(v,u);
	}
	dep[1]=1;dfs(1,0);
	for(int i=1;i<=q;i++)
	{
		scanf("%d%d",&u,&v);
		Base lca=LCA(u,v);
		printf("%lld\n",lca.query());
	}
	return 0;
}
