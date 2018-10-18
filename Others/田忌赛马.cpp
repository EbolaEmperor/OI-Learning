#include<iostream>
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;

int a[2500],b[2500];

int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) scanf("%d",a+i);
	for(int i=1;i<=n;i++) scanf("%d",b+i);
	sort(a+1,a+1+n);
	sort(b+1,b+1+n);
	deque<int> qa,qb;
	for(int i=1;i<=n;i++) qa.push_back(a[i]),qb.push_back(b[i]);
	int ans=0;
	while(n--)
	{
		if(qa.back()>qb.back()) qa.pop_back(),qb.pop_back(),ans+=200;
		else if(qa.front()>qb.front()) qa.pop_front(),qb.pop_front(),ans+=200;
		else if(qa.front()<qb.back())qa.pop_front(),qb.pop_back(),ans-=200;
	}
	cout<<ans<<endl;
	return 0;
}
