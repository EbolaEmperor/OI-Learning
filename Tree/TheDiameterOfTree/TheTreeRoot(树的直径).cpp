#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

struct Edge{int to,next;} e[2000000];
int h[6000];
int dist1[6000],dist2[6000];
bool vis[6000];
int sum;

void add_edge(int u,int v)
{
	sum++;
	e[sum].to=v;
	e[sum].next=h[u];
	h[u]=sum;
}

void BFS(int s,int *dist)
{
	memset(vis,0,sizeof(vis));
	queue<int> q;
	q.push(s);
	vis[s]=1;dist[s]=0;
	while(!q.empty())
	{
		int o=q.front();
		for(int tmp=h[o];tmp!=0;tmp=e[tmp].next)
			if(!vis[e[tmp].to])
			{
				vis[e[tmp].to]=1;
				dist[e[tmp].to]=dist[o]+1;
				q.push(e[tmp].to);
			}
		q.pop();
	}
}

int main()
{
	int n,k,x;
	while(~scanf("%d",&n))
	{
		sum=0;memset(h,0,sizeof(h));
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&k);
			for(int j=1;j<=k;j++)
			{
				scanf("%d",&x);
				add_edge(i,x);
			}
		}
		BFS(1,dist1);
		int maxn=0,d1,d2;
		for(int i=1;i<=n;i++)
			if(dist1[i]>maxn) maxn=dist1[i],d1=i;
		BFS(d1,dist1);
		maxn=0;
		for(int i=1;i<=n;i++)
			if(dist1[i]>maxn) maxn=dist1[i],d2=i;
		BFS(d2,dist2);
		vector<int> best;
		vector<int> worst;
		int bestn=0x7fffffff,worstn=0;
		for(int i=1;i<=n;i++)
		{
			int m=max(dist1[i],dist2[i]);
			if(m<=bestn)
			{
				if(m<bestn) bestn=m,best.clear();
				best.push_back(i);
			}
			if(m>=worstn)
			{
				if(m>worstn) worstn=m,worst.clear();
				worst.push_back(i);
			}
		}
		sort(best.begin(),best.end());
		sort(worst.begin(),worst.end());
		printf("Best Roots  :");
		for(int i=0;i<best.size();i++) printf(" %d",best[i]);
		printf("\nWorst Roots :");
		for(int i=0;i<worst.size();i++) printf(" %d",worst[i]);
		printf("\n");
	}
	return 0;
}
