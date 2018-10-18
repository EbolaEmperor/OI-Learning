#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=5010;
struct Edge{int to,next;} e[N<<1];
int h[N],sum=0;
int dep[N],deep;
LL t[N],cnt[N];

void add_edge(int u,int v)
{
	e[++sum].to=v;
	e[sum].next=h[u];
	h[u]=sum;
}

void dfs(int u,int fa,int d)
{
	dep[d]++;deep=max(deep,d);
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		int v=e[tmp].to;
		if(v==fa) continue;
		dfs(v,u,d+1);
	}
}

int main()
{
	int n,u,v;
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		scanf("%d%d",&u,&v);
		add_edge(u,v);
		add_edge(v,u);
	}
	LL ans=0;
	for(int i=1;i<=n;i++)
	{
		memset(t,0,sizeof(t));
		memset(cnt,0,sizeof(cnt));
		for(int tmp=h[i];tmp;tmp=e[tmp].next)
		{
			memset(dep,0,sizeof(dep));
			dfs(e[tmp].to,i,1);
			for(int k=1;k<=deep;k++)
			{
				ans+=t[k]*dep[k];
				t[k]+=cnt[k]*dep[k];
				cnt[k]+=dep[k];
			}
		}
	}
	cout<<ans<<endl;
	return 0;
}
