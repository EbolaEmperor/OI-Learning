#include<iostream>
#include<cstdio>
#include<cmath>
#include<algorithm>
#define MOD 998244353
using namespace std;

typedef long long LL;
LL a[10000010];

LL inv(LL a)
{
	LL b=MOD-2,ans=1;
	while(b)
	{
		if(b&1) ans=ans*a%MOD;
		a=a*a%MOD;
		b>>=1;
	}
	return ans;
}

LL C(LL a,LL b)
{
	LL ans1=1;
	for(LL i=a;i>b;i--)
		ans1=ans1*i%MOD;
	LL ans2=1;
	for(LL i=a-b;i>1;i--)
		ans2=ans2*i%MOD;
	return ans1*inv(ans2)%MOD;
}

int main()
{
	int n;
	cin>>n;
	for(int i=0;i<n;i++) scanf("%lld",a+i);
	sort(a,a+n);
	int m=unique(a,a+n)-a;
	cout<<C(2*m,m)*inv(m+1)%MOD<<endl;
	return 0;
}

