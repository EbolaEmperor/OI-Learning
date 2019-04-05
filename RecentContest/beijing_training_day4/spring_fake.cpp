#include<bits/stdc++.h>
using namespace std;

const int N=210,M=100000;
struct Edge{int from,to,capa,flow,next,id;} e[M],pk[M];
int h[N],n,m,fff,k,s,t,tot=-1;
int dep[N],vis[N],cur[N];
int col[M],deg[N];

void add_edge(int u,int v,int w,int id=0)
{
	e[++tot]={u,v,w,0,h[u],id};h[u]=tot;
	e[++tot]={v,u,0,0,h[v],id};h[v]=tot;
}

bool bfs()
{
	queue<int> q;
	memset(vis,0,sizeof(vis));
	q.push(s);vis[s]=1;dep[s]=0;
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(int i=h[u];~i;i=e[i].next)
			if(e[i].capa>e[i].flow&&!vis[e[i].to])
			{
				dep[e[i].to]=dep[u]+1;
				vis[e[i].to]=1;
				q.push(e[i].to);
			}
	}
	return vis[t];
}

int dfs(int u,int a)
{
	if(u==t||a==0) return a;
	int res=0,tmp;
	for(int &i=cur[u];~i;i=e[i].next)
		if(dep[e[i].to]==dep[u]+1)
		{
			tmp=dfs(e[i].to,min(a,e[i].capa-e[i].flow));
			if(!tmp) continue;
			res+=tmp;a-=tmp;
			e[i].flow+=tmp;
			e[i^1].flow-=tmp;
			if(!a) break;
		}
	return res;
}

int dinic()
{
	int res=0;
	while(bfs())
	{
		memcpy(cur,h,sizeof(cur));
		res+=dfs(s,INT_MAX);
	}
	return res;
}

void gao(int c)
{
	tot=-1;
	memset(h,-1,sizeof(h));
	for(int i=1;i<=n/2;i++) add_edge(s,i,1,0);
	for(int i=n/2+1;i<=n;i++) add_edge(i,t,1,0);
	for(int i=1;i<=m;i++) if(!col[i]) add_edge(pk[i].from,pk[i].to,1,i);
	dinic();
	for(int i=0;i<=tot;i+=2)
		if(e[i].from!=s&&e[i].to!=t&&e[i].flow) col[e[i].id]=c;
}

int main()
{
	scanf("%d%d%d",&n,&m,&k);
	if(n&1) n++,fff=1;
	memset(h,-1,sizeof(h));s=0;t=n+1;
	for(int i=1;i<=n/2;i++) add_edge(s,i,k);
	for(int i=n/2+1;i<=n;i++) add_edge(i,t,k);
	for(int i=1,u,v;i<=m;i++)
	{
		scanf("%d%d",&u,&v);
		add_edge(u,v+fff,1,i);
		pk[i]={u,v+fff};
	}
	int ans=dinic();
	for(int i=0;i<=tot;i+=2)
		if(e[i].from!=s&&e[i].to!=t)
			e[i].flow?(deg[e[i].from]++,deg[e[i].to]++):col[e[i].id]=-1;
	int A=m,B=m,pm=m;
	for(int i=1;i<=n/2;i++)
		while(deg[i]<k) deg[i]++,pk[++A].from=i;
	for(int i=n/2+1;i<=n;i++)
		while(deg[i]<k) deg[i]++,pk[++B].to=i;
	m=A;
	for(int i=1;i<=k;i++) gao(i);
	printf("%d\n",ans);
	for(int i=1;i<=pm;i++)
		if(col[i]>0) printf("%d %d\n",i,col[i]);
	return 0;
}
