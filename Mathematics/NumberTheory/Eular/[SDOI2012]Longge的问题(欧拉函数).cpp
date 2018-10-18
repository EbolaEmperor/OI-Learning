#include<iostream>
#include<cstdio>
#include<cmath>
using namespace std;

typedef long long LL;

LL d[100000];
int tot=0;

LL phi(LL n)
{
	LL ans=n,a=n;
	for(LL i=2;i*i<=a;i++)
		if(a%i==0)
		{
			ans=ans/i*(i-1);
			while(a%i==0) a/=i;
		}
	if(a>1) ans=ans/a*(a-1);
	return ans;
}

int main()
{
	LL n;
	cin>>n;
	LL m=(LL)floor(sqrt(n));
	for(LL i=1;i<=m;i++)
	{
		if(n%i!=0) continue;
		if(i*i!=n) d[++tot]=i,d[++tot]=n/i;
		else d[++tot]=i;
	}
	LL ans=0;
	for(int i=1;i<=tot;i++) ans+=d[i]*phi(n/d[i]);
	cout<<ans<<endl;
	return 0;
}
