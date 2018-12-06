#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;

int n,m,s,t;
int h[200],a[200],p[200];
struct Edge{int from,to,capa,flow,next;} e[100000];
bool vis[200];
int sum=-1;

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

int Maxflow()
{
	int flow=0;
	while(1)
	{
		memset(a,0,sizeof(a));
		a[s]=0x7fffffff;
		queue<int> q;
		q.push(s);
		while(!q.empty())
		{
			int o=q.front();
			for(int tmp=h[o];tmp!=-1;tmp=e[tmp].next)
			{
				if(e[tmp].capa>e[tmp].flow&&a[e[tmp].to]==0)
				{
					a[e[tmp].to]=min(a[o],e[tmp].capa-e[tmp].flow);
					p[e[tmp].to]=tmp;
					q.push(e[tmp].to);
				}
			}
			q.pop();
			if(a[t]!=0) break;
		}
		if(a[t]==0) break;
		for(int i=t;i!=s;i=e[p[i]].from)
		{
			e[p[i]].flow+=a[t];
			e[p[i]^1].flow-=a[t];
		}
		flow+=a[t];
	}
	return flow;
}

int main()
{
	int u,v;
	cin>>m>>n;
	memset(vis,0,sizeof(vis));
	s=0;
	t=n+1;
	for(int i=0;i<=n+10;i++) h[i]=-1;
	for(int i=1;i<=m;i++)
	{
		add_edge(s,i,1);
		add_edge(i,s,0);
	}
	for(int i=m+1;i<=n;i++)
	{
		add_edge(i,t,1);
		add_edge(t,i,0);
	}
	scanf("%d%d",&u,&v);
	while(!(u==-1&&v==-1))
	{
		add_edge(u,v,1);
		add_edge(v,u,0);
		scanf("%d%d",&u,&v);
	}
	printf("%d\n",Maxflow());
	for(int i=0;i<=sum;i+=2)
	{
		if(e[i].from==s||e[i].to==s||e[i].from==t||e[i].to==t) continue;
		if(e[i].flow>0) printf("%d %d\n",e[i].from,e[i].to);
	}
	return 0;
}
