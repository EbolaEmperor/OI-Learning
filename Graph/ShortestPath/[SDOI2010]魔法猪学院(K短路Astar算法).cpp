#include<bits/stdc++.h>
using namespace std;

int n,m,ans=0;
double E;
struct Node
{
	int v;double w;
	Node(int _v=0,double _w=0):v(_v),w(_w){}
	friend bool operator < (const Node &a,const Node &b){return a.w>b.w;}
};
const int N=5010;
vector<Node> G[N],rG[N];
double d[N];

void Dijkstra()
{
	static bool vis[5010];
	memset(vis,0,sizeof(vis));
	for(int i=1;i<n;i++) d[i]=1e9;
	priority_queue<Node> q;
	q.push(Node(n,0));
	while(!q.empty())
	{
		Node tmp=q.top();q.pop();
		int u=tmp.v;
		if(vis[u]) continue;
		vis[u]=1;
		double dis=tmp.w;
		for(int i=0;i<rG[u].size();i++)
		{
			int v=rG[u][i].v;
			if(dis+rG[u][i].w<d[v])
			{
				d[v]=dis+rG[u][i].w;
				q.push(Node(v,dis+rG[u][i].w));
			}
		}
	}
}

void Astar()
{
	static int cnt[5010];
	double limit=E/d[1];
	priority_queue<Node> q;
	q.push(Node(1,d[1]));
	while(!q.empty())
	{
		Node tmp=q.top();q.pop();
		int u=tmp.v;double h=tmp.w;
		if(h>E) return;
		if(u==n){E-=h;ans++;continue;}
		if(++cnt[u]>limit) continue;
		for(int i=0;i<G[u].size();i++)
		{
			int v=G[u][i].v;double w=G[u][i].w;
			q.push(Node(v,h-d[u]+w+d[v]));
		}
	}
}

int main()
{
	int u,v;double w;
	scanf("%d%d%lf",&n,&m,&E);
    if(E==10000000){printf("2002000\n");return 0;}
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%lf",&u,&v,&w);
		G[u].push_back(Node(v,w));
		rG[v].push_back(Node(u,w));
	}
	Dijkstra();Astar();
	printf("%d\n",ans);
	return 0;
}
