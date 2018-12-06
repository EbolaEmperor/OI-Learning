#include<bits/stdc++.h>
using namespace std;

struct Edge{int to,capa,next;} e[2000000];
int h[20000],sum=0;
bool vis[20000];
int dis[20000];
int n,m,s;

void add_edge(int u,int v,int w)
{
	sum++;
	e[sum].to=v;
	e[sum].capa=w;
	e[sum].next=h[u];
	h[u]=sum;
}

void spfa()
{
	queue<int> q;
	q.push(s);
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=n;i++) dis[i]=0x7fffffff;
	vis[s]=1;dis[s]=0;
	while(!q.empty())
	{
		int o=q.front();
		for(int tmp=h[o];tmp;tmp=e[tmp].next)
			if(dis[o]+e[tmp].capa<dis[e[tmp].to])
			{
				dis[e[tmp].to]=dis[o]+e[tmp].capa;
				if(!vis[e[tmp].to]) q.push(e[tmp].to),vis[e[tmp].to]=1;
			}
		q.pop();
		vis[o]=0;
	}
	for(int i=1;i<=n;i++) printf("%d ",dis[i]);
}

int main()
{
	cin>>n>>m>>s;
	for(int i=1;i<=m;i++)
	{
		int a,b,c;
		scanf("%d%d%d",&a,&b,&c);
		add_edge(a,b,c);
	}
	spfa();
	return 0;
}
