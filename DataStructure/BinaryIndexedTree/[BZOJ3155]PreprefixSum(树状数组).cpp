#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
LL a[100010],n,m;
struct BIT
{
	LL c[100010];
	LL lowbit(LL x){return x&(-x);}
	void modify(LL p,LL pre,LL x)
	{
		for(LL i=p;i<=n;i+=lowbit(i))
			c[i]=c[i]-pre+x;
	}
	LL query(LL p)
	{
		LL cnt=0;
		for(LL i=p;i>=1;i-=lowbit(i))
			cnt+=c[i];
		return cnt;
	}
} t1,t2;
char opt[10];

int main()
{
	LL p,x;
	cin>>n>>m;
	for(LL i=1;i<=n;i++)
	{
		scanf("%lld",a+i);
		t1.modify(i,0,a[i]);
		t2.modify(i,0,(i-1)*a[i]);
	}
	for(LL i=1;i<=m;i++)
	{
		scanf("%s%lld",&opt,&p);
		if(opt[0]=='M')
		{
			scanf("%lld",&x);
			t1.modify(p,a[p],x);
			t2.modify(p,(p-1)*a[p],(p-1)*x);
			a[p]=x;
		}
		else printf("%lld\n",p*t1.query(p)-t2.query(p));
	}
	return 0;
}
