#include<bits/stdc++.h>
using namespace std;

int fa[10010];

int find(int x){return (fa[x]==0)?x:(fa[x]=find(fa[x]));}

void merge(int a,int b)
{
	int x=find(a);
	int y=find(b);
	if(x!=y) fa[y]=x;
}

void query(int a,int b)
{
	int x=find(a);
	int y=find(b);
	if(x!=y) puts("N");
	else puts("Y");
}

int main()
{
	int n,m,opt,a,b;
	cin>>n>>m;
	memset(fa,0,sizeof(fa));
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&opt,&a,&b);
		if(opt==1) merge(a,b);
		if(opt==2) query(a,b);
	}
	return 0;
}
