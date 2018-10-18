#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

int f[5010];
int cnt[5010];
int a[5010];

int main()
{
	int n,ans1=0,ans2=0;
	cin>>n;
	for(int i=1;i<=n;i++) scanf("%d",a+i);
	for(int i=1;i<=n;i++)
	{
		f[i]=1;
		for(int j=1;j<i;j++)
			if(a[i]<a[j]) f[i]=max(f[i],f[j]+1);
		ans1=max(ans1,f[i]);
	}
	for(int i=1;i<=n;i++)
	{
		if(f[i]==1) cnt[i]=1;
		for(int j=1;j<i;j++)
			if(f[i]==f[j]+1&&a[i]<a[j]) cnt[i]+=cnt[j];
			else if(f[i]==f[j]&&a[i]==a[j]) cnt[i]=0;
		if(f[i]==ans1) ans2+=cnt[i];
	}
	cout<<ans1<<" "<<ans2<<endl;
	return 0;
}
