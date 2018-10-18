#include<bits/stdc++.h>
using namespace std;

long long inv[3000010];

int main()
{
	long long n,p;
	cin>>n>>p;
	inv[1]=1;
	cout<<1<<endl;
	for(long long i=2;i<=n;i++)
	{
		inv[i]=(-(p/i)*inv[p%i]%p+p)%p;
		printf("%lld\n",inv[i]);
	}
	return 0;
}
