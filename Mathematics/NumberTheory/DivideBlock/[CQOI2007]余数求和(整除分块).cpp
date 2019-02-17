#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

int main()
{
	long long n,k;
	cin>>n>>k;
	long long ans=n*k,r=0;
	for(long long l=1;l<=n;l=r+1)
	{
		if(k/l==0) r=n;
		else r=min(k/(k/l),n);
		ans-=(k/l)*(r+1-l)*(l+r)/2;
	}
	cout<<ans<<endl;
	return 0;
}
