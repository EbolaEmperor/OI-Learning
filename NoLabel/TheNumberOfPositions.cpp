#include<iostream>
#include<cstdio>
using namespace std;

int main()
{
	int n,a,b;
	int ans=0;
	cin>>n>>a>>b;
	for(int i=1;i<=n;i++)
		if((i-1)>=a&&(n-i)<=b) ans++;
	cout<<ans<<endl;
	return 0;
}
