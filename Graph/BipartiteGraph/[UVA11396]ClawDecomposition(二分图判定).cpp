#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

struct Edge{int to,next;} e[2000000];
int h[5000],color[5000];
int sum;

void add_edge(int u,int v)
{
	sum++;
	e[sum].to=v;
	e[sum].next=h[u];
	h[u]=sum;
}

bool DFS(int u)
{
	bool flag=true;
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
	{
		if(color[e[tmp].to]==0)
		{
			color[e[tmp].to]=3-color[u];
			flag=DFS(e[tmp].to);
		}
		else if(color[e[tmp].to]==color[u]) flag=false;
		if(!flag) break;
	}
	return flag;
}

int main()
{
	int n,m,x,y;
	while(~scanf("%d",&n)&&n)
	{
		m=0;sum=0;
		memset(h,0,sizeof(h));
		while(~scanf("%d%d",&x,&y)&&x&&y)
		{
			add_edge(x,y);
			add_edge(y,x);
			m++;
		}
		memset(color,0,sizeof(color));
		color[1]=1;
		if(n*3==m*2&&DFS(1)) puts("YES");
		else puts("NO");
	}
	return 0;
}
