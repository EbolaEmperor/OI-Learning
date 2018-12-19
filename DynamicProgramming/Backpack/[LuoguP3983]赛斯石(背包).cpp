#include<iostream>
#include<cstdio>
#include<climits>
using namespace std;

long long a[11];
long long b[11]={0,1,3,5,7,9,10,11,14,15,17};
long long f[100050];

int main()
{
	long long need;
	cin>>need;
	if(need==0) {cout<<0<<endl;return 0;}
	for(long long i=1;i<=10;i++) scanf("%lld",a+i);
	for(long long i=1;i<=10;i++) f[i]=a[i]-b[i];
	for(long long i=1;i<=need;i++)
		for(long long j=1;j<=10;j++)
			if(i-j>=1) f[i]=max(f[i],f[i-j]+f[j]);
	if(need<=10) cout<<f[need]+1<<endl;
	else cout<<f[need]<<endl;
	return 0;
}
