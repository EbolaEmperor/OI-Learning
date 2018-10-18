#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

int main()
{
	int n,m,x,ans=0,cnt;
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		cnt=0;
		for(int j=1;j<=m;j++)
		{
			scanf("%d",&x);
			if(x==1) cnt++;
		}
		ans=max(ans,cnt);
	}
	cout<<ans<<endl;
	return 0;
}
