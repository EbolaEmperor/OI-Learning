#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

int f[100005][4][2];
int a[100005][4];

int main()
{
	int n;
	cin>>n;
	for(int i=1;i<=n;i++) scanf("%d%d%d",&a[i][1],&a[i][2],&a[i][3]);
	memset(f,0,sizeof(f));
	for(int i=1;i<=3;i++) a[n+1][i]=a[1][i];
	for(int i=2;i<=n+1;i++)
	{
		f[i][1][0]=max(f[i-1][2][1],f[i-1][3][1])+a[i][1];
		f[i][3][1]=max(f[i-1][2][0],f[i-1][1][0])+a[i][3];
		f[i][2][0]=f[i-1][3][1]+a[i][2];
		f[i][2][1]=f[i-1][1][0]+a[i][2];
	}
	int ans=max(max(f[n+1][1][0],f[n+1][3][1]),max(f[n+1][2][0],f[n+1][2][1]));
	cout<<ans<<endl;
	return 0;
}
