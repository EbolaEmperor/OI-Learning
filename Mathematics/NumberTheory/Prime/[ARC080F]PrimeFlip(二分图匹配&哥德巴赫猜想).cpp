#include<bits/stdc++.h>
#define INF 0x7fffffff
using namespace std;

struct Edge{int to,capa,flow,next;} e[10500];
int h[210],sum=-1,s,t;
bool vis[210];
int d[210],cur[210];

void AddEdge(int u,int v,int w)
{
	e[++sum].to=v;
	e[sum].flow=0;
	e[sum].capa=w;
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
	q.push(s);
	d[s]=0;vis[s]=1;
	while(!q.empty())
	{
		int u=q.front();
		for(int tmp=h[u];~tmp;tmp=e[tmp].next)
			if(e[tmp].capa>e[tmp].flow&&!vis[e[tmp].to])
			{
				vis[e[tmp].to]=1;
				d[e[tmp].to]=d[u]+1;
				q.push(e[tmp].to);
			}
		q.pop();
	}
	return vis[t];
}

int DFS(int u,int a)
{
	if(u==t||a==0) return a;
	int f,flow=0;
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

int Maxflow()
{
	int flow=0;
	while(BFS())
	{
		for(int i=s;i<=t;i++) cur[i]=h[i];
		flow+=DFS(s,INF);
	}
	return flow;
}

const int N=10000000;
int lft[110],rht[110],num=0;
bool up[N+10];

int Pow(int a,int b,int p)
{
	int ans=1;
	for(;b;b>>=1,a=1ll*a*a%p)
		if(b&1) ans=1ll*ans*a%p;
	return ans;
}

bool isprime(int n)
{
	if(n==2) return true;
	if(n<2||!(n&1)) return false;
	int t=0;
	int a,x,y,u=n-1;
	while(!(u&1)) t++,u>>=1;
	for(int i=0;i<10;i++)
	{
		a=rand()%(n-1)+1;
		x=Pow(a,u,n);
		for(int j=0;j<t;j++,x=y)
		{
			y=1ll*x*x%n;
			if(y==1&&x!=1&&x!=n-1) return false;
		}
		if (x!=1) return false;
	}
	return true;
}

int main()
{
	int n,x;
	scanf("%d",&n);
	memset(h,-1,sizeof(h));
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		up[x]=1;
	}
	int l=0,r=0;
	for(int i=1;i<=N+1;i++)
		if(up[i]!=up[i-1])
		{
			if(i&1) lft[++l]=i;
			else rht[++r]=i;
		}
	s=0;t=l+r+1;
	for(int i=1;i<=l;i++) add_edge(s,i,1);
	for(int i=1;i<=r;i++) add_edge(l+i,t,1);
	for(int i=1;i<=l;i++)
		for(int j=1;j<=r;j++)
			if(isprime(abs(lft[i]-rht[j])))
				add_edge(i,j+l,1);
	int falun=Maxflow(),dafa=falun;
	if(l>falun) dafa+=(l-falun)/2*2;
	if(r>falun) dafa+=(r-falun)/2*2;
	if((l-falun)&1) dafa+=3;
	printf("%d\n",dafa);
	return 0;
}
