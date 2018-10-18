#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<map>
#define INF 0x7fffffff
using namespace std;

map<string,int> f;
int s,t,n,m,sum=-1;
string name[110];
struct Edge{int from,to,capa,flow,cost,next;} e[2000000];
int h[5000];
bool vis[5000];
int d[5000],a[5000],p[5000];
deque<int> ans;

void AddEdge(int u,int v,int w,int c)
{
	sum++;
	e[sum].from=u;
	e[sum].to=v;
	e[sum].capa=w;
	e[sum].flow=0;
	e[sum].cost=c;
	e[sum].next=h[u];
	h[u]=sum;
}

void add_edge(int u,int v,int w,int c)
{
	AddEdge(u,v,w,c);
	AddEdge(v,u,0,-c);
}

bool BellmanFord(int &flow,int &cost)
{
	memset(vis,0,sizeof(vis));
	for(int i=s;i<=t;i++) d[i]=INF;
	d[s]=0;a[s]=INF;vis[s]=1;
	queue<int> q;
	q.push(s);
	while(!q.empty())
	{
		int o=q.front();
		for(int tmp=h[o];tmp!=-1;tmp=e[tmp].next)
		{
			if(e[tmp].capa-e[tmp].flow>0&&d[o]+e[tmp].cost<d[e[tmp].to])
			{
				d[e[tmp].to]=d[o]+e[tmp].cost;
				a[e[tmp].to]=min(a[o],e[tmp].capa-e[tmp].flow);
				p[e[tmp].to]=tmp;
				if(!vis[e[tmp].to]) vis[e[tmp].to]=1,q.push(e[tmp].to);
			}
		}
		q.pop();
		vis[o]=0;
	}
	if(d[t]==INF) return false;
	flow+=a[t];
	cost+=a[t]*d[t];
	for(int u=t;u!=s;u=e[p[u]].from)
	{
		e[p[u]].flow+=a[t];
		e[p[u]^1].flow-=a[t];
	}
	return true;
}

int MincostMaxflow(int &flow)
{
	int cost=0;
	while(BellmanFord(flow,cost));
	return cost;
}

void DFS(int x)
{
	if(x==n+n) return;
	for(int tmp=h[x];tmp!=-1;tmp=e[tmp].next)
	{
		if(e[tmp].flow>0)
		{
			e[tmp].flow--;
			if(e[tmp].to<=n) ans.push_back(e[tmp].to);
			DFS(e[tmp].to);
		}
	}
}

int main()
{
	string x,y;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cin>>x;
		f[x]=i;
		name[i]=x;
	}
	s=0;t=2*n+1;
	for(int i=s;i<=t;i++) h[i]=-1;
	for(int i=1;i<=n;i++) add_edge(i,i+n,1,-1);
	for(int i=1;i<=m;i++)
	{
		cin>>x>>y;
		add_edge(f[x]+n,f[y],INF,0);
	}
	add_edge(1,1+n,1,-1);
	add_edge(n,n+n,1,-1);
	add_edge(s,1,2,0);
	add_edge(n+n,t,2,0);
	int flow=0;
	int num=MincostMaxflow(flow);
	if(flow<2)
		puts("No Solution!");
	else
	{
		cout<<-(num+2)<<endl;
		ans.push_back(1);
		DFS(1);
		while(1)
		{
			cout<<name[ans.front()]<<endl;
			if(ans.front()==n) break;
			ans.pop_front();
		}
		ans.pop_front();
		ans.pop_back();
		while(!ans.empty())
		{
			cout<<name[ans.back()]<<endl;
			ans.pop_back();
		}
		cout<<name[1]<<endl;
	}
	return 0;
}
