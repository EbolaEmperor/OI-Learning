#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

int a[200],d[200],f[200];

int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	memset(d,0,sizeof(d));
	memset(f,0,sizeof(f));
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<i;j++)
			if(a[j]<a[i]) f[i]=max(f[i],f[j]);
		f[i]++;
	}
	for(int i=n;i>=1;i--)
	{
		for(int j=n;j>i;j--)
			if(a[j]<a[i]) d[i]=max(d[i],d[j]);
		d[i]++;
	}
	int ans=0;
	for(int i=1;i<=n;i++) ans=max(ans,f[i]+d[i]);
	ans--;
	cout<<(n-ans)<<endl;
	return 0;
}
