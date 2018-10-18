#include<bits/stdc++.h>
using namespace std;

struct Edge{int to,capa,next;} e[2000000];
int h[10000],sum,n,m;
int dis[10000];
bool vis[10000];
int times[10000];
bool flag;

void add_edge(int u,int v,int w)
{
	sum++;
	e[sum].to=v;
	e[sum].capa=w;
	e[sum].next=h[u];
	h[u]=sum;
}

void spfa(int s)
{
	memset(vis,0,sizeof(vis));
	memset(times,0,sizeof(times));
	for(int i=1;i<=n;i++) dis[i]=0x7fffffff;
	vis[s]=1;dis[s]=0;times[s]=1;
	queue<int> q;
	q.push(s);
	while(!q.empty())
	{
		int o=q.front();
		for(int tmp=h[o];tmp;tmp=e[tmp].next)
			if(dis[o]+e[tmp].capa<dis[e[tmp].to])
			{
				times[e[tmp].to]++;
				if(times[e[tmp].to]>=n){flag=true;return;}
				dis[e[tmp].to]=dis[o]+e[tmp].capa;
				if(!vis[e[tmp].to]) vis[e[tmp].to]=1,q.push(e[tmp].to);
			}
		q.pop();
		vis[o]=0;
	}
}

int main()
{
	int T,a,b,c;
	for(cin>>T;T;T--)
	{
		scanf("%d%d",&n,&m);
		memset(h,0,sizeof(h));
		sum=0;
		for(int i=1;i<=m;i++)
		{
			scanf("%d%d%d",&a,&b,&c);
			add_edge(a,b,c);
			if(c>=0) add_edge(b,a,c);
		}
		flag=false;
		spfa(1);
		puts(flag?"YE5":"N0");
	}
	return 0;
}
