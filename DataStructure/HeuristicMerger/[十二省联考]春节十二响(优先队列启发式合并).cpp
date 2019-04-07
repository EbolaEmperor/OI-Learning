#include<bits/stdc++.h>
using namespace std;

typedef priority_queue<int> pq;
const int N=200010;
vector<int> g[N];
int n,val[N],lson[N];

void merge(pq &a,pq b)
{
	static int c[N];int tot=0;
	while(!b.empty())
		c[++tot]=max(a.top(),b.top()),a.pop(),b.pop();
	for(int i=1;i<=tot;i++)
		a.push(c[i]);
}

int dfs1(int u)
{
	int d=1;
	for(int v : g[u])
	{
		int tmp=dfs1(v)+1;
		if(tmp>d) lson[u]=v;
		d=max(d,tmp);
	}
	return d;
}

pq dfs2(int u)
{
	pq res;
	if(lson[u]) res=dfs2(lson[u]);
	for(int v : g[u])
		if(v!=lson[u]) merge(res,dfs2(v));
	res.push(val[u]);
	return res;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++) scanf("%d",val+i);
	for(int i=2,fa;i<=n;i++) scanf("%d",&fa),g[fa].push_back(i);
	dfs1(1);
	pq res=dfs2(1);
	long long ans=0;
	while(!res.empty())
		ans+=res.top(),res.pop();
	printf("%lld\n",ans);
	return 0;
}
