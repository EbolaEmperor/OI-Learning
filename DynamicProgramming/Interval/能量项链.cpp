#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

int f[210][210];
int a[210];

int main()
{
	int n,ans=0;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],a[n+i]=a[i];
	memset(f,0,sizeof(f));
	for(int r=2;r<=2*n;r++)
		for(int l=r-1;l>=1&&l>=r-n+1;l--)
			for(int k=l;k<r;k++)
			{
				f[l][r]=max(f[l][r],f[l][k]+f[k+1][r]+a[l]*a[k+1]*a[r+1]);
				ans=max(ans,f[l][r]);
			}
	cout<<ans<<endl;
	return 0;
}
