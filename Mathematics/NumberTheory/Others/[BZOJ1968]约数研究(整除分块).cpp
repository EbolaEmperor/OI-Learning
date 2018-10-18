#include<bits/stdc++.h>
using namespace std;

int main()
{
	int n,div,ans=0;cin>>n;
	for(int i=1;i<=n;i=div+1)
	{
		div=n/(n/i);
		ans+=(div-i+1)*(n/i);
	}
	cout<<ans<<endl;
	return 0;
}
