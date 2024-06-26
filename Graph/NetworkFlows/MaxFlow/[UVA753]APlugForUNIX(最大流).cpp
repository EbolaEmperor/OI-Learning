#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
#include<queue>
#define INF 0x7fffffff
using namespace std;

struct Edge{int from,to,capa,flow,next;} e[2000000];
int h[5000];
int n,m,s,t,sum=-1;
int d[5000],cur[5000];
bool vis[5000];
map<string,int> f;

void AddEdge(int u,int v,int w)
{
	sum++;
	e[sum].from=u;
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
	queue<int> q;
	memset(vis,0,sizeof(vis));
	vis[s]=1;
	d[s]=0;
	q.push(s);
	while(!q.empty())
	{
		int o=q.front();
		for(int tmp=h[o];tmp!=-1;tmp=e[tmp].next)
		{
			if(e[tmp].capa>e[tmp].flow&&vis[e[tmp].to]==0)
			{
				vis[e[tmp].to]=1;
				d[e[tmp].to]=d[o]+1;
				q.push(e[tmp].to);
			}
		}
		q.pop();
	}
	return vis[t];
}

int DFS(int u,int a)
{
	int flow=0,f;
	if(u==t||a==0) return a;
	for(int &tmp=cur[u];tmp!=-1;tmp=e[tmp].next)
	{
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

int main()
{
	int T;
	bool flag=0;
	string s1,s2;
	for(cin>>T;T;T--)
	{
		if(flag) putchar('\n');
		s=0;t=3000;
		sum=-1;
		for(int i=s;i<=t;i++) h[i]=-1;
		f.clear();
		int cnt=1;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			cin>>s1;
			if(!f.count(s1)) f[s1]=cnt++;
			add_edge(s,f[s1],1);
		}
		scanf("%d",&m);
		for(int i=1;i<=m;i++)
		{
			cin>>s1>>s2;
			if(!f.count(s2)) f[s2]=cnt++;
			add_edge(f[s2],t,1);
		}
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
		{
			cin>>s1>>s2;
			if(!f.count(s1)) f[s1]=cnt++;
			if(!f.count(s2)) f[s2]=cnt++;
			add_edge(f[s2],f[s1],INF);
		}
		printf("%d\n",m-Dinic());
		flag=1;
	}
	return 0;
}
