#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
using namespace std;

struct Edge
{
	int from,to,capa,flow,next;
} e[300000];
int  h[10005];
int a[10005];
int p[10005];
int sum=0;
int n,m,s,t;

void add_edge(int a,int b,int c,int d)
{
	sum++;
	e[sum].from=a;
	e[sum].to=b;
	e[sum].capa=c;
	e[sum].flow=d;
	e[sum].next=h[a];
	h[a]=sum;
}

int maxflow()
{
	int flow=0;
	while(1)
	{
		memset(a,0,sizeof(a));
		queue<int> q;
		q.push(s);
		a[s]=0x7fffffff;
		while(!q.empty())
		{
			int o=q.front();
			for(int tmp=h[o];tmp!=0;tmp=e[tmp].next)
			{
				if(a[e[tmp].to]==0&&e[tmp].capa>e[tmp].flow)
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
			e[p[i]+1].flow-=a[t];
		}
		flow+=a[t];
	}
	return flow;
}

int main()
{
	int x,y,z;
	memset(h,0,sizeof(h));
	memset(p,0,sizeof(p));
	scanf("%d%d%d%d",&n,&m,&s,&t);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		add_edge(x,y,z,0);
		add_edge(y,x,0,0);     //构造残量网络
	}
	printf("%d\n",maxflow());
	return 0;
}
