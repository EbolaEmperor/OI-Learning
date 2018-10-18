#include<bits/stdc++.h>
#define INF 0x7fffffff
#define pb push_back
using namespace std;

struct Node
{
	int v,w;
	Node(int a=0,int b=0):v(a),w(b){}
	friend bool operator < (const Node &a,const Node &b){return a.w>b.w||a.w==b.w&&a.v<b.v;}
};
vector<Node> g[100010];
int n,m,s,dis[100010];
bool vis[100010];

void Dijkstra()
{
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++) dis[i]=INF;
	priority_queue<Node> q;
	q.push(Node(s,0));dis[s]=0;
	while(!q.empty())
	{
		Node tmp=q.top();q.pop();
		int u=tmp.v,d=tmp.w;
		if(vis[u]) continue;
		vis[u]=1;
		for(int i=0;i<g[u].size();i++)
			if(d+g[u][i].w<dis[g[u][i].v])
			{
				dis[g[u][i].v]=d+g[u][i].w;
				q.push(Node(g[u][i].v,dis[g[u][i].v]));
			}
	}
}

int main()
{
	int u,v,w;
	scanf("%d%d%d",&n,&m,&s);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&u,&v,&w);
		g[u].pb(Node(v,w));
	}
	Dijkstra();
	for(int i=1;i<=n;i++)
		printf("%d ",dis[i]);
	return 0;
}
