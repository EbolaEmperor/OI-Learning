#include<bits/stdc++.h>
using namespace std;

int main()
{
	int n,x;
	cin>>n;
	long long ans=0;
	priority_queue<int> q;
	for(int i=1;i<=n;i++)
	{
		scanf("%d",&x);
		q.push(x);
		int o=q.top();
		if(x<o)
		{
			ans+=o-x;
			q.pop();
			q.push(x);
		}
	}
	cout<<ans<<endl;
	return 0;
}
