#include<bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
const int N=40010;
struct Edge{int from,to,next;} e[N<<5];
int h[N<<2],sum=0;
int low[N<<2],pre[N<<2];
int scc[N<<2],dfn,cnt;
int a[2][N],n;
pii Hash[N<<1];
stack<int> stk;
int node[N<<4],tot;

void add_edge(int u,int v)
{
	if(u==v) return;
	e[++sum].to=v;
	e[sum].from=u;
	e[sum].next=h[u];
	h[u]=sum;
}

void Build(int o,int l,int r)
{
	if(l==r)
	{
		node[o]=Hash[l].second;
		return;
	}
	node[o]=++tot;
	int mid=(l+r)/2;
	Build(o<<1,l,mid);
	Build(o<<1|1,mid+1,r);
	add_edge(node[o],node[o<<1]);
	add_edge(node[o],node[o<<1|1]);
}

void link(int o,int l,int r,int nl,int nr,int u)
{
	if(nl>nr) return;
	if(l>=nl&&r<=nr)
	{
		add_edge(u,node[o]);
		return;
	}
	int mid=(l+r)/2;
	if(nl<=mid) link(o<<1,l,mid,nl,nr,u);
	if(nr>mid) link(o<<1|1,mid+1,r,nl,nr,u);
}

void Init()
{
	for(int i=1;i<=n;i++)
	{
		Hash[2*i-1].first=a[0][i];
		Hash[2*i-1].second=i+n;
		Hash[2*i].first=a[1][i];
		Hash[2*i].second=i;
	}
	sort(Hash+1,Hash+1+2*n);
}

void Tarjan(int u)
{
	stk.push(u);
	low[u]=pre[u]=++dfn;
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
		if(!pre[e[tmp].to])
		{
			Tarjan(e[tmp].to);
			low[u]=min(low[u],low[e[tmp].to]);
		}
		else if(!scc[e[tmp].to]) low[u]=min(low[u],pre[e[tmp].to]);
	if(pre[u]==low[u])
	{
		int o;cnt++;
		do{
			o=stk.top();
			stk.pop();
			scc[o]=cnt;
		}while(o!=u);
	}
}

bool check(int x)
{
	sum=dfn=cnt=0;tot=2*n;
	memset(h,0,sizeof(h));
	Build(1,1,2*n);
	for(int i=1;i<=n;i++)
		for(int k=0;k<2;k++)
		{
			int l=lower_bound(Hash+1,Hash+1+2*n,pii(a[k][i]-x+1,0))-Hash;
			int r=upper_bound(Hash+1,Hash+1+2*n,pii(a[k][i]+x-1,2*n+1))-Hash-1;
			int m=lower_bound(Hash+1,Hash+1+2*n,pii(a[k][i],(k^1)*n+i))-Hash;
			link(1,1,2*n,l,m-1,k*n+i);
			link(1,1,2*n,m+1,r,k*n+i);
		}
	while(!stk.empty()) stk.pop();
	memset(pre,0,sizeof(pre));
	memset(low,0,sizeof(low));
	memset(scc,0,sizeof(scc));
	for(int i=1;i<=tot;i++)
		if(!pre[i]) Tarjan(i);
	for(int i=1;i<=n;i++)
		if(scc[i]==scc[i+n]) return 0;
	return 1;
}

int main()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&a[0][i],&a[1][i]);
	Init();
	int l=0,r=int(1e9),mid;
	while(l<r)
	{
		mid=(l+r)/2;
		if(check(mid)) l=mid+1;
		else r=mid-1;
	}
	printf("%d\n",check(l)?l:l-1);
	return 0;
}
