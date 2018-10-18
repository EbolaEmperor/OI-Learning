#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

struct node{int v,ord;} a[1000005],b[1000005];
int p[1000005],c[1000005];
int n;

bool cmp(node x,node y)
{
	if(x.v==y.v) return x.ord<y.ord;
	else return x.v<y.v;
}

int lowbit(int x){return x&-x;}

void add(int x,int d)
{
	while(x<=n)
	{
		c[x]+=d;
		x+=lowbit(x);
	}
}

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

int main()
{
	cin>>n;
	char tmp=getchar();
	while(tmp<'A'||tmp>'Z') tmp=getchar();
	for(int i=1;i<=n;i++) a[i].v=tmp-'A',a[i].ord=i,tmp=getchar();
	while(tmp<'A'||tmp>'Z') tmp=getchar();
	for(int i=1;i<=n;i++) b[i].v=tmp-'A',b[i].ord=i,tmp=getchar();
	sort(a+1,a+1+n,cmp);
	sort(b+1,b+1+n,cmp);
	for(int i=1;i<=n;i++) p[a[i].ord]=b[i].ord;
	long long ans=0;
	for(int i=n;i>=1;i--)
	{
		add(p[i],1);
		ans+=(long long)sum(p[i]-1);
	}
	cout<<ans<<endl;
	return 0;
}
