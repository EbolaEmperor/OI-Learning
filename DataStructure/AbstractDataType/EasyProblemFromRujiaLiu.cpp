#include<iostream>
#include<cstdio>
#include<map>
#include<vector>
using namespace std;

map<int,vector<int> > a;

int main()
{
	int n,m,x,y;
	while(~scanf("%d%d",&n,&m))
	{
		a.clear();
		for(int i=1;i<=n;i++)
		{
			scanf("%d",&x);
			if(!a.count(x)) a[x]=vector<int>();
			a[x].push_back(i);
		}
		for(int i=1;i<=m;i++)
		{
			scanf("%d%d",&x,&y);
			if(!a.count(y)||a[y].size()<x) puts("0");
			else printf("%d\n",a[y][x-1]);
		}
	}
	return 0;
}
