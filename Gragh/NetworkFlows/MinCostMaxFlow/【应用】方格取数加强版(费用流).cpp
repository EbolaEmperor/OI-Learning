#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define INF 0x7fffffff
#define IN 0
#define OUT 1
using namespace std;

struct Edge{int from,to,capa,flow,cost,next;} e[2000000];
int h[5000];
bool vis[5000];
int a[5000];
int p[5000];
int d[5000];
int n,m,s,t;
int sum=-1;

void add_edge(int u,int v,int w,int c)
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

void AddEdge(int u,int v,int w,int c)
{
	add_edge(u,v,w,c);
	add_edge(v,u,0,-c);
}

bool BellmanFord(int &flow,long long &cost)
{
    for(int i=s;i<=t;i++) d[i]=INF;
    memset(vis,0,sizeof(vis));
    d[s]=0;vis[s]=1;p[s]=0;a[s]=INF;
    queue<int> q;
    q.push(s);
    while(!q.empty())
    {
        int o=q.front();
		//cout<<d[o]<<endl;
        for(int tmp=h[o];tmp!=-1;tmp=e[tmp].next)
        {
			//cout<<tmp<<endl;
            if(e[tmp].capa>e[tmp].flow&&d[o]+e[tmp].cost<d[e[tmp].to])
            {
                d[e[tmp].to]=d[o]+e[tmp].cost;
                p[e[tmp].to]=tmp;
                a[e[tmp].to]=min(a[o],e[tmp].capa-e[tmp].flow);
                if(!vis[e[tmp].to]) q.push(e[tmp].to),vis[e[tmp].to]=1;
            }
        }
        q.pop();
        vis[o]=0;
    }
    if(d[t]==INF) return false;
    flow+=a[t];
    cost+=(long long)a[t]*(long long)d[t];
    for(int u=t;u!=s;u=e[p[u]].from)
    {
		//cout<<u<<endl;
        e[p[u]].flow+=a[t];
        e[p[u]^1].flow-=a[t];
    }
    return true;
}

long long MincostMaxflow()
{
	int flow=0;
    long long cost=0;
    while(BellmanFord(flow,cost));
    return cost;
}

int getn(int x,int y,bool op)
{
	int ans=(x-1)*n+y;
	return ans+op*n*n;
}

int main()
{
	int k,x;
	cin>>n>>k;
	s=0;t=2*n*n+1;
	for(int i=s;i<=t;i++) h[i]=-1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			scanf("%d",&x);
			AddEdge(getn(i,j,IN),getn(i,j,OUT),1,-x);
			AddEdge(getn(i,j,IN),getn(i,j,OUT),INF,0);
			if(i<n) AddEdge(getn(i,j,OUT),getn(i+1,j,IN),INF,0);
			if(j<n) AddEdge(getn(i,j,OUT),getn(i,j+1,IN),INF,0);
		}
	AddEdge(s,getn(1,1,IN),k,0);
	AddEdge(getn(n,n,OUT),t,k,0);
	printf("%lld\n",-MincostMaxflow());
	return 0;
}
