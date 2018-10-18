#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

struct node{int v,ord;} a[40005];
int c[40005];
int n;

bool cmp(node x,node y){return x.v>y.v;}

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
	cin>>n;
	for(int i=1;i<=n;i++) scanf("%d",&a[i].v),a[i].ord=i;
	sort(a+1,a+1+n,cmp);
	int ans=0;
	for(int i=1;i<=n;i++)
	{
		add(a[i].ord,1);
		ans+=sum(a[i].ord-1);
	}
	cout<<ans<<endl;
	return 0;
}
