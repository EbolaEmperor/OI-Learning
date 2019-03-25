#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=5005;
int pos[N],g[N],a[N];
LL f[N][N],ans;
int n,A,B;

void upmin(LL &x,const LL &y){if(y<x) x=y;}

int main()
{
	scanf("%d%d%d",&n,&A,&B);
	for(int i=1;i<=n;i++) scanf("%d",a+i);
	for(int i=1;i<=n;i++)
	{
		pos[a[i]]=i;
		for(int j=i-1;j;j--)
			if(a[j]>a[i]) g[i]++;
	}
	memset(f,0x3f,sizeof(f));f[0][0]=0;
	for(int i=0,tmp;i<n;i++)
	{
		tmp=pos[i+1];
		for(int j=0;j<=n;j++)
			if(j>g[tmp]) upmin(f[i+1][j-1],f[i][j]+A);
			else upmin(f[i+1][j],f[i][j]+B),upmin(f[i+1][g[tmp]],f[i][j]);
	}
	ans=INT64_MAX;
	for(int i=0;i<=n;i++)
		upmin(ans,f[n][i]);
	printf("%lld\n",ans);
 	return 0;
}