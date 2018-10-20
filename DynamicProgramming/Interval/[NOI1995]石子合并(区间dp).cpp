#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

int f[210][210];
int d[210][210];
int a[210];
int sum[210];

int main()
{
	int n,ans1=0xfffffff,ans2=0;
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i],a[n+i]=a[i];
	memset(sum,0,sizeof(sum));
	sum[1]=a[1];
	for(int i=2;i<=2*n;i++) sum[i]=sum[i-1]+a[i];
	for(int r=2;r<=2*n;r++)
		for(int l=r-1;l>=1&&l>=r-n+1;l--)
		{
			d[l][r]=0x3f3f3f3f;
			for(int k=l;k<r;k++)
			{
				d[l][r]=min(d[l][r],d[l][k]+d[k+1][r]+sum[r]-sum[l-1]);
				if(l+n-1==r) ans1=min(ans1,d[l][r]);
				f[l][r]=max(f[l][r],f[l][k]+f[k+1][r]+sum[r]-sum[l-1]);
				ans2=max(ans2,f[l][r]);
			}
		}
	cout<<ans1<<endl<<ans2<<endl;
	return 0;
}
