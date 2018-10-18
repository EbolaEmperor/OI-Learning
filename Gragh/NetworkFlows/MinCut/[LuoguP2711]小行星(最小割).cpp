#include<bits/stdc++.h>
#define INF 0x7fffffff
using namespace std;

struct Edge{int to,capa,flow,next;} e[2000000];
int h[5000],sum=-1,s,t;
int cur[5000],d[5000];
bool vis[5000];
bool f1[510][510],f2[510][510];

void AddEdge(int u,int v,int w)
{
	sum++;
	e[sum].to=v;
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
	vis[s]=1;d[s]=0;
	queue<int> q;
	q.push(s);
	while(!q.empty())
	{
		int o=q.front();
		for(int tmp=h[o];tmp!=-1;tmp=e[tmp].next)
			if((!vis[e[tmp].to])&&e[tmp].capa>e[tmp].flow)
			{
				vis[e[tmp].to]=1;
				d[e[tmp].to]=d[o]+1;
				q.push(e[tmp].to);
			}
		q.pop();
	}
	return vis[t];
}

int DFS(int u,int a)
{
	if(u==t||a==0) return a;
	int flow=0,f;
	for(int &tmp=cur[u];tmp!=-1;tmp=e[tmp].next)
		if(d[e[tmp].to]==d[u]+1)
		{
			f=DFS(e[tmp].to,min(a,e[tmp].capa-e[tmp].flow));
			if(f>0)
			{
				flow+=f;
				a-=f;
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
		for(int i=s;i<=t;i++) cur[i]=h[i];
		flow+=DFS(s,INF);
	}
	return flow;
}

int getn(int x,int c){return x+(c-1)*500;}

int main()
{
	int n;
	cin>>n;
	s=0;t=getn(1,5)+10;
	for(int i=s;i<=t;i++) h[i]=-1;
	for(int i=1;i<=500;i++)
	{
		add_edge(s,getn(i,1),1);
		add_edge(getn(i,2),getn(i,3),1);
		add_edge(getn(i,4),t,1);
	}
	int x,y,z;
	memset(f1,0,sizeof(f1));
	memset(f2,0,sizeof(f2));
	for(int i=1;i<=n;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		f1[x][y]=true;
		f2[y][z]=true;
	}
	for(int i=1;i<=500;i++)
		for(int j=1;j<=500;j++)
		{
			if(f1[i][j]) add_edge(getn(i,1),getn(j,2),INF);
			if(f2[i][j]) add_edge(getn(i,3),getn(j,4),INF);
		}
	cout<<Dinic()<<endl;
	return 0;
}
