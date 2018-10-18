#include<iostream>
#include<cstdio>
using namespace std;

int n;
int a[500005],c[500005];

int lowbit(int x){return x&-x;}

int sum(int x)
{
	int ret=0;
	while(x>0)
	{
		ret+=c[x];
		x-=lowbit(x);
	}
	return ret;
}

void add(int x,int d)
{
	while(x<=n)
	{
		c[x]+=d;
		x+=lowbit(x);
	}
}

int main()
{
	int m,opt,x,y,k;
	cin>>n>>m;
	for(int i=1;i<=n;i++) scanf("%d",a+i);
	for(int i=1;i<=n;i++) add(i,a[i]-a[i-1]);
	for(int T=1;T<=m;T++)
	{
		scanf("%d",&opt);
		if(opt==1) scanf("%d%d%d",&x,&y,&k),add(x,k),add(y+1,-k);
		if(opt==2) scanf("%d",&x),printf("%d\n",sum(x));
	}
	return 0;
}
