#include<bits/stdc++.h>
#define INF 0x7fffffff
using namespace std;

struct Edge{int to,capa,flow,next;} e[4000000];
int h[20010],sum=-1,n,m,S,T;
int mp[110][110],tot=0;
bool vis[20010];
int d[20010],cur[20010];

void AddEdge(int u,int v,int w)
{
	e[++sum].to=v;
	e[sum].capa=w;
	e[sum].flow=0;
	e[sum].next=h[u];
	h[u]=sum;
}

void add_edge(int u,int v,int w)
{
	AddEdge(u,v,w);
	AddEdge(v,u,0);
}

bool BFS()
{
	memset(vis,0,sizeof(vis));
	queue<int> q;
	vis[S]=1;d[S]=0;
	q.push(S);
	while(!q.empty())
	{
		int u=q.front();
		for(int tmp=h[u];~tmp;tmp=e[tmp].next)
			if(!vis[e[tmp].to]&&e[tmp].capa>e[tmp].flow)
			{
				d[e[tmp].to]=d[u]+1;
				vis[e[tmp].to]=1;
				q.push(e[tmp].to);
			}
		q.pop();
	}
	return vis[T+tot];
}

int DFS(int u,int a)
{
	if(u==T+tot||a==0) return a;
	int flow=0,f;
	for(int& tmp=cur[u];~tmp;tmp=e[tmp].next)
		if(d[e[tmp].to]==d[u]+1)
		{
			f=DFS(e[tmp].to,min(a,e[tmp].capa-e[tmp].flow));
			if(f>0)
			{
				flow+=f;a-=f;
				e[tmp].flow+=f;
				e[tmp^1].flow-=f;
				if(a==0) break;
			}
		}
	return flow;
}

int Dinic()
{
	int flow=0;
	while(BFS())
	{
		for(int i=1;i<=2*tot;i++) cur[i]=h[i];
		flow+=DFS(S,INF);
	}
	return flow==INF?-1:flow;
}

int main()
{
	static char s[110];
	scanf("%d%d",&n,&m);
	memset(h,-1,sizeof(h));
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s+1);
		for(int j=1;j<=m;j++)
		{
			if(s[j]!='.') mp[i][j]=++tot;
			if(s[j]=='S') S=tot;
			if(s[j]=='T') T=tot;
		}
	}
	for(int i=1;i<=tot;i++)
		if(i!=S&&i!=T) add_edge(i,i+tot,1);
	add_edge(S,S+tot,INF);
	add_edge(T,T+tot,INF);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			int u=mp[i][j];
			if(!u) continue;
			for(int k=1;k<=n;k++)
				if(k!=i&&mp[k][j])
					add_edge(u+tot,mp[k][j],INF);
			for(int k=1;k<=m;k++)
				if(k!=j&&mp[i][k])
					add_edge(u+tot,mp[i][k],INF);
		}
	printf("%d\n",Dinic());
	return 0;
}
