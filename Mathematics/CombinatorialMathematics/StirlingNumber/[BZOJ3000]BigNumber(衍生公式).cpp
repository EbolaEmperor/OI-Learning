#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const double pi=acos(-1);
const double e=exp(1);
inline double log(double n,double k){return log(n)/log(k);}

int main()
{
	int n,k;
	while(~scanf("%d%d",&n,&k))
	{
		LL ans=(LL)(log(2*pi*n,k)*0.5+n*log(n,k)-n*log(e,k))+1;
		printf("%lld\n",ans);
	}
	return 0;
}
