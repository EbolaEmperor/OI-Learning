#include<iostream>
#include<cstdio>
using namespace std;

int a[100010];

int main()
{
	int n;
	cin>>n;
	int ans=0,cnt=0;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",a+i);
		if(a[i]>=a[i-1]) cnt++;
		else ans=max(ans,cnt),cnt=1;
	}
	cout<<max(ans,cnt)<<endl;
	return 0;
}
