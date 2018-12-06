#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define INF 0x7fffffff
using namespace std;

struct Edge{int from,to,capa,next,flow;} e[2000000];
int h[5005],cur[5005],d[5005];
bool vis[5005];
int s,t,n,m;
int sum=-1;
char s1[200][10],s2[200][10];

void add_edge(int u,int v,int c)
{
	sum++;
	e[sum].from=u;
	e[sum].to=v;
	e[sum].capa=c;
	e[sum].flow=0;
	e[sum].next=h[u];
	h[u]=sum;
}

bool win(int x,int y)
{
	if(s1[x][0]=='J'&&(s2[y][0]=='H'||s2[y][0]=='W')) return true;
	else if(s1[x][0]=='W'&&(s2[y][0]=='Y'||s2[y][0]=='E')) return true;
	else if(s1[x][0]=='Y'&&(s2[y][0]=='J'||s2[y][0]=='H')) return true;
	else if(s1[x][0]=='H'&&(s2[y][0]=='W'||s2[y][0]=='E')) return true;
	else if(s1[x][0]=='E'&&(s2[y][0]=='J'||s2[y][0]=='Y')) return true;
	else return false;
}

bool BFS()
{
	memset(vis,0,sizeof(vis));
	queue<int> q;
	q.push(s);
	vis[s]=1;
	d[s]=0;
	while(!q.empty())
	{
		int o=q.front();
		for(int tmp=h[o];tmp!=-1;tmp=e[tmp].next)
		{
			if(vis[e[tmp].to]==0&&e[tmp].capa>e[tmp].flow)
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
	if(u==t||a==0) return a;
	int flow=0,f;
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
	int x,cnt1=0,cnt2=0;
	cin>>n>>m;
	s=0;
	t=2*n+1;
	for(int i=s;i<=t;i++) h[i]=-1;
	for(int i=1;i<=n;i++)
	{
		cin>>s1[i];
		if(s1[i][0]=='Y') cnt1++;
	}
	for(int i=1;i<=n;i++)
	{
		cin>>s2[i];
		if(s2[i][0]=='Y') cnt2++;
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(win(i,j)) add_edge(i,n+j,1),add_edge(n+j,i,0);
	for(int i=1;i<=n;i++)
	{
		cin>>x;
		if(s1[i][0]=='J') x+=cnt1;
		add_edge(s,i,x),add_edge(i,s,0);
	}
	for(int i=1;i<=n;i++)
	{
		cin>>x;
		if(s2[i][0]=='J') x+=cnt2;
		add_edge(i+n,t,x),add_edge(t,i+n,0);
	}
	printf("%d\n",min(Dinic(),m));
	return 0;
}
