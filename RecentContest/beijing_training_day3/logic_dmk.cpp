#include<bits/stdc++.h>
using namespace std;

bool vis[10005];
int ch[10005][2];

int main()
{
	freopen("rand.txt","r",stdin);
	int sand;scanf("%d",&sand);
	srand(sand);
	fclose(stdin);
	int n=3,m=9;
	printf("%d %d\n",n,m);
	for(int i=1;i<=m;i++)
	{
		int x1=rand()%n+1,y1=rand()&1;
		int x2=rand()%n+1,y2=rand()&1;
		while(x1==x2) x1=rand()%n+1,x2=rand()%n+1;
		if(y1) x1=-x1;if(y2) x2=-x2;
		printf("%d %d\n",x1,x2);
	}
	for(int i=m+1;i<2*m;i++)
	{
		int a=rand()%(i-1)+1;
		while(vis[a]) a=rand()%(i-1)+1;
		printf("%d ",a);vis[a]=1;
		ch[i][0]=a;
		a=rand()%(i-1)+1;
		while(vis[a]) a=rand()%(i-1)+1;
		printf("%d\n",a);vis[a]=1;
		ch[i][1]=a;
	}
	freopen("graph.txt","w",stdout);
	for(int i=m+1;i<2*m;i++)
		printf("%d %d\n%d %d\n",i,ch[i][0],i,ch[i][1]);
	fclose(stdout);
	freopen("rand.txt","w",stdout);
	printf("%d\n",rand());
	return 0;
}
