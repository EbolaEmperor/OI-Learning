#include<bits/stdc++.h>
#define inc (int)1e5
using namespace std;

int a[100010],cnt[250000],_hash[100010];

int main()
{
	int n,b,pos;
	cin>>n>>b;
	memset(cnt,0,sizeof(cnt));
	for(int i=1;i<=n;i++)
	{
		scanf("%d",a+i);
		if(a[i]>b) _hash[i]=1;
		else if(a[i]<b) _hash[i]=-1;
		else _hash[i]=0,pos=i;
		//cout<<_hash[i]<<" ";
	}
	int ans=1,sum=0;
	for(int i=pos-1;i>=1;i--)
	{
		sum+=_hash[i];
		if(sum==0) ans++;
		cnt[inc+sum]++;
	}
	sum=0;
	for(int i=pos+1;i<=n;i++)
	{
		sum+=_hash[i];
		if(sum==0) ans++;
		ans+=cnt[inc-sum];
	}
	cout<<ans<<endl;
	return 0;
}
