#include<bits/stdc++.h>
using namespace std;

bool vis[205][205];

int main()
{
	srand(time(0));
	freopen("spring1.in","w",stdout);
	int n=100,m=2000,k=20;
	printf("%d %d %d\n",n*2,m,k);
	for(int i=1;i<=m;i++)
	{
		int u=rand()%n+1,v=rand()%n+1+n;
		while(vis[u][v]) u=rand()%n+1,v=rand()%n+1+n;
		printf("%d %d\n",u,v);
		vis[u][v]=1;
	}
	return 0;
}
