#include<bits/stdc++.h>
using namespace std;

int a[500010],n;

int main()
{
	cin>>n;
	for(int i=1;i<=n;i++) scanf("%d",a+i);
	sort(a+1,a+n+1);
	int ans=n;
	for(int i=n/2;i>=1;i--)
		if(a[i]*2<=a[ans]) ans--;
	cout<<ans<<endl;
	return 0;
}
