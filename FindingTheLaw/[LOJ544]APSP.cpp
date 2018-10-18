#include<bits/stdc++.h>
using namespace std;

int a[100010];

int main()
{
	int n,k;cin>>k;n=k+1;
	printf("%d\n",n);
	if(n&1)
	{
		for(int i=1,m=n/2+1;i<=n;i+=2,m++) a[i]=m;
		for(int i=2,m=n/2;i<=n;i+=2,m--) a[i]=m;
	}
	else
	{
		for(int i=1,m=n/2;i<=n;i+=2,m--) a[i]=m;
		for(int i=2,m=n/2+1;i<=n;i+=2,m++) a[i]=m;
	}
	for(int i=1;i<=n;i++) printf("%d ",a[i]);
	return 0;
}
