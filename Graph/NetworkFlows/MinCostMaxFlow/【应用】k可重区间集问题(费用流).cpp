#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#define INF 0x3fffffff
using namespace std;

struct Edge{int from,to,capa,flow,cost,next;} e[2000000];
int h[5100],a[5100],p[5100],d[5100];
bool vis[5100];
int n, k, s, t;
int sum=-1;

void add_edge_(int u,int v,int c1,int c2)
{
	sum++;
	e[sum].from=u;
	e[sum].to=v;
	e[sum].capa=c1;
	e[sum].cost=c2;
	e[sum].flow=0;
	e[sum].next=h[u];
	h[u]=sum;
}

void add_edge(int u,int v,int c1,int c2)
{
	add_edge_(u, v, c1, c2);
	add_edge_(v, u, 0, -c2);
}

bool BellmanFord(int& flow,long long& cost)
{
	memset(vis,0,sizeof(vis));
	vis[s]=1;
	a[s]=INF;
	for(int i=s;i<=t;i++) d[i]=-INF;
	d[s]=0;
	queue<int> q;
	q.push(s);
	while(!q.empty())
	{
		int o=q.front();
		for(int tmp=h[o];tmp!=-1;tmp=e[tmp].next)
		{
			if(e[tmp].capa>e[tmp].flow&&d[o]+e[tmp].cost>d[e[tmp].to])
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
	if(d[t]==-INF) return false;
	flow+=a[t];
	cost+=(long long)a[t]*(long long)d[t];
	for(int i=t;i!=s;i=e[p[i]].from)
	{
		e[p[i]].flow+=a[t];
		e[p[i]^1].flow-=a[t];
	}
	return true;
}

long long MaxcostMaxflow()
{
	int flow=0;
	long long cost=0;
	while(BellmanFord(flow,cost));
	return cost;
}

int L[600], R[600];

int main()
{
    cin >> n >> k;
	memset(h, -1, sizeof(h));
    s = 0; 
    t = 2*n + 2;
    int ss = 2*n + 1;
    add_edge(s, ss, k, 0);
    for(int i = 1; i <= n; i++){
        cin >> L[i] >> R[i];
        add_edge(ss, i, 1, 0);
        add_edge(i+n, t, 1, 0);
        add_edge(i, i+n, 1, R[i]-L[i]);
    }
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= n; j++)
            if(L[j] >= R[i]) add_edge(i+n, j, 1, 0);
    printf("%lld\n",MaxcostMaxflow());
	return 0;
}
