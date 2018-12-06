#include<iostream>
#include<cstdio>
#include<cstring>
#define cls(x) memset(x,0,sizeof(x))
using namespace std;

struct Edge{int to,next;} e[2000000];
int h[5000],sum;
bool mark[5000];
int s[5000],cnt;

void add_edge(int u,int v)
{
	sum++;
	e[sum].to=v;
	e[sum].next=h[u^1];
	h[u^1]=sum;
}

bool DFS(int u)
{
	if(mark[u^1]) return 0;
	if(mark[u]) return 1;
	mark[u]=1;s[cnt++]=u;
	for(int tmp=h[u];tmp;tmp=e[tmp].next)
		if(!DFS(e[tmp].to)) return 0;
	return 1;
}

int main()
{
	int n,m,x,y;
	char c;
	while(~scanf("%d%d",&n,&m)&&n&&m)
	{
		sum=0;
		cls(h);cls(mark);cls(s);
		for(int i=1;i<=m;i++)
		{
			scanf("%d%c",&x,&c);
			x=2*x+(c=='h');
			scanf("%d%c",&y,&c);
			y=2*y+(c=='h');
			add_edge(x,y);
			add_edge(y,x);
		}
		mark[0]=1;
		for(int i=2;i<n*2;i+=2)
			if(!mark[i] && !mark[i+1])
			{
				cnt=0;
				if(!DFS(i))
				{
					while(cnt>0) mark[s[--cnt]]=0;
					if(!DFS(i+1)){printf("bad luck");goto fuck;}
				}
			}
		for(int i=1;i<n;i++) printf("%d%c ",i,mark[2*i]?'w':'h');
		fuck: putchar('\n');
	}
	return 0;
}
