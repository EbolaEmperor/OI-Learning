#include<bits/stdc++.h>
using namespace std;

const int N=110;
const double eps=1e-6;
struct Edge{int to,next;double capa,flow;} e[N*N];
int h[N],tot=0,n,m,s,t;
double a[N],b[N],sum=0;
bool atk[N][N];
bool vis[N];
int deep[N];
int cur[N];

void AddEdge(int u,int v,double w)
{
	e[++tot].to=v;
	e[tot].flow=0;
	e[tot].capa=w;
	e[tot].next=h[u];
	h[u]=tot;
}

void add_edge(int u,int v,double w)
{
	AddEdge(u,v,w);
	AddEdge(v,u,0);
}

bool BFS()
{
	memset(vis,0,sizeof(vis));
	queue<int> q;q.push(s);
	vis[s]=1;deep[s]=0;
	while(!q.empty())
	{
		int u=q.front();q.pop();
		for(int tmp=h[u];~tmp;tmp=e[tmp].next)
			if(fabs(e[tmp].capa-e[tmp].flow)>eps&&!vis[e[tmp].to])
			{
				vis[e[tmp].to]=1;
				deep[e[tmp].to]=deep[u]+1;
				q.push(e[tmp].to);
			}
	}
	return vis[t];
}

double DFS(int u,double a)
{
	if(u==t||fabs(a)<eps) return a;
	double flow=0,f;
	for(int &tmp=cur[u];~tmp;tmp=e[tmp].next)
		if(deep[e[tmp].to]==deep[u]+1)
		{
			f=DFS(e[tmp].to,min(a,e[tmp].capa-e[tmp].flow));
			if(fabs(f)>0)
			{
				flow+=f;a-=f;
				e[tmp].flow+=f;
				e[tmp^1].flow-=f;
				if(fabs(a)<eps) break;
			}
		}
	return flow;
}

double Dinic()
{
	double flow=0;
	while(BFS())
	{
		for(int i=s;i<=t;i++) cur[i]=h[i];
		flow+=DFS(s,1e9);
	}
	return flow;
}

bool check(double x)
{
	tot=-1;
	memset(h,-1,sizeof(h));
	for(int i=1;i<=m;i++)
		add_edge(s,i,x*b[i]);
	for(int i=1;i<=n;i++)
		add_edge(m+i,t,a[i]);
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			if(atk[i][j]) add_edge(i,m+j,1e9);
	return fabs(Dinic()-sum)<eps;
}

int main()
{
	scanf("%d%d",&n,&m);
	s=0;t=m+n+1;
	for(int i=1;i<=n;i++) scanf("%lf",a+i),sum+=a[i];
	for(int i=1;i<=m;i++) scanf("%lf",b+i);
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&atk[i][j]);
	double l=0,r=1e6,mid;
	while(r-l>eps)
	{
		mid=(l+r)/2;
		if(check(mid)) r=mid;
		else l=mid;
	}
	printf("%lf\n",l);
	return 0;
}
