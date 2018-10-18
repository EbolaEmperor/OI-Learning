#include<bits/stdc++.h>
using namespace std;

int a[100010],b[100010],c[100010];
int g[100010];

int LIS(int *a,int n)
{
	int ans=0;
	for(int i=1;i<=n;i++) g[i]=0x7fffffff;
	for(int i=1;i<=n;i++)
	{
		int p=lower_bound(g+1,g+1+n,a[i])-(g+1);
		ans=max(ans,p+1);
		g[p+1]=min(g[p+1],a[i]);
	}
	return ans;
}

int main()
{
	int n,x;
	cin>>n;
	for(int i=1;i<=n;i++) scanf("%d",a+i);
	for(int i=1;i<=n;i++) scanf("%d",&x),b[x]=i;
	for(int i=1;i<=n;i++) c[i]=b[a[i]];
	cout<<LIS(c,n)<<endl;
	return 0;
}
