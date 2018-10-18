#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;

const long long INF=(long long)1e15;
struct Edge{int from,to,next;long long capa,flow;} e[2000000],e_spfa[2000000];
int h[30010],hh[15000];
int n,m,s,t,sum=-1,sum_spfa=0;
bool vis[30010];
long long dist[30010],z;

void add_edge_spfa(int u,int v,long long w)
{
	sum_spfa++;
	e_spfa[sum_spfa].from=u;
	e_spfa[sum_spfa].to=v;
	e_spfa[sum_spfa].capa=w;
	e_spfa[sum_spfa].next=h[u];
	h[u]=sum_spfa;
}

void SPFA()
{
	memset(vis,0,sizeof(vis));
	queue<int> q;
	for(int i=0;i<=n;i++) q.push(i),vis[i]=1;
	while(!q.empty())
	{
		int o=q.front();
		//cout<<o<<endl;
		for(int tmp=h[o];tmp;tmp=e_spfa[tmp].next)
		{
			if(dist[o]+e_spfa[tmp].capa>dist[e_spfa[tmp].to])
			{
				dist[e_spfa[tmp].to]=dist[o]+e_spfa[tmp].capa;
				if(!vis[e_spfa[tmp].to]) vis[e_spfa[tmp].to]=1,q.push(e_spfa[tmp].to);
			}
		}
		q.pop();
		vis[o]=0;
	}
}

int main()
{
	int x,y,z;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		add_edge_spfa(i-1,i,0);
		add_edge_spfa(i,i-1,-1);
	}
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		add_edge_spfa(x-1,y,z);
	}
	SPFA();
	cout<<(dist[n])<<endl;
	return 0;
}
