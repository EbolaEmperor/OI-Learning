#include<iostream>
#include<cstdio>
using namespace std;

int t1[100010],t2[100010];
int n,m;

int lowbit(int x){return x&-x;}
void add(int c[],int x,int k){for(int i=x;i<=n;i+=lowbit(i)) c[i]+=k;}
int sum(int c[],int x)
{
	int ret=0;
	for(int i=x;i>0;i-=lowbit(i)) ret+=c[i];
	return ret;
}
int main()
{
	int q,l,r;
	scanf("%d%d",&n,&m);
	for(int T=1;T<=m;T++)
	{
		scanf("%d%d%d",&q,&l,&r);
		if(q==1) add(t1,l,1),add(t2,r,1);
		if(q==2) printf("%d\n",sum(t1,r)-sum(t2,l-1));
	}
	return 0;
}
