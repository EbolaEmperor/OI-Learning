#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;

template <typename fl,typename co> class MincostMaxflow
{
	private:

	struct Edge{int from,to,next;fl capa,flow;co cost;} e[100005];
	int s,t;
	int h[5005],p[5005];
	fl a[5005];
	co d[5005];
	bool vis[5005];
	int sum;

	void AddEdge(int u,int v,fl w,co f)
	{
		sum++;
		e[sum].from=u;
		e[sum].to=v;
		e[sum].capa=w;
		e[sum].cost=f;
		e[sum].flow=0;
		e[sum].next=h[u];
		h[u]=sum;
	}

	bool BellmanFord(fl& flow,co& cost)
	{
		for(int i=0;i<5005;i++) d[i]=0x7fffffff;
		memset(vis,0,sizeof(vis));
		d[s]=0;
		a[s]=0x7fffffff;
		vis[s]=1;
		queue<int> q;
		q.push(s);
		while(!q.empty())
		{
			int o=q.front();
			//cout<<o<<" "<<h[o]<<endl;
			for(int tmp=h[o];tmp!=-1;tmp=e[tmp].next)
			{
				if(e[tmp].capa>e[tmp].flow&&d[o]+e[tmp].cost<d[e[tmp].to])
				{
					d[e[tmp].to]=d[o]+e[tmp].cost;
					a[e[tmp].to]=min(a[o],e[tmp].capa-e[tmp].flow);
					p[e[tmp].to]=tmp;
					if(!vis[e[tmp].to])
					{
						vis[e[tmp].to]=1;
						q.push(e[tmp].to);
					}
				}
			}
			q.pop();
			vis[o]=0;
		}
		if(d[t]==0x7fffffff) return 0;
		flow+=a[t];
		cost+=d[t]*(co)a[t];
		for(int i=t;i!=s;i=e[p[i]].from)
		{
			e[p[i]].flow+=a[t];
			e[p[i]^1].flow-=a[t];
		}
		return 1;
	}
	
	public:

	void add_edge(int u,int v,fl w,co f)
	{
		AddEdge(u,v,w,f);
		AddEdge(v,u,0,-f);
	}
	void MCMF(fl& flow,co& cost)
	{
		flow=cost=0;
		while(BellmanFord(flow,cost));
	}
	void init(int x,int y)
	{
		s=x;t=y;
		sum=-1;
		for(int i=0;i<5005;i++) h[i]=-1;
	}

};

int main()
{
	int n,m,s,t;
	scanf("%d%d%d%d",&n,&m,&s,&t);
	MincostMaxflow<int,long long> g;
	g.init(s,t);
	int u,v,w;
	long long f;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d%lld",&u,&v,&w,&f);
		g.add_edge(u,v,w,f);
	}
	long long mincost=0;
	int maxflow=0;
	g.MCMF(maxflow,mincost);
	printf("%d %lld\n",maxflow,mincost);
	return 0;
}
