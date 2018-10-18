#include<bits/stdc++.h>
#define Mod 1000000007
#define inv2 500000004
using namespace std;

const int N=200010;
int a[N],ans[N];
bool prm[3*N];

void FWT(int *a,int n,bool flag)
{
	for(int i=1;i<n;i<<=1)
		for(int j=0;j<n;j+=(i<<1))
			for(int k=0;k<i;k++)
			{
				int x=a[j+k],y=a[i+j+k];
				if(flag) a[j+k]=(x+y)%Mod,a[i+j+k]=(x-y+Mod)%Mod;
				else a[j+k]=1ll*(x+y)*inv2%Mod,a[i+j+k]=1ll*(x-y+Mod)*inv2%Mod;
			}
}

int main()
{
	for(int i=2;i<=500000;i++) prm[i]=1;
	for(int i=2;i<=500000;i++)
		for(int j=i+i;j<=500000;j+=i)
			prm[j]=0;
	int n,m;
	while(~scanf("%d%d",&n,&m))
	{
		memset(a,0,sizeof(a));
		int len;for(len=1;len<=m;len<<=1);
		for(int i=0;i<len;i++) a[i]=prm[i]&&i<=m;
		FWT(a,len,1);
		for(int i=0;i<len;i++) ans[i]=a[i];
		for(n--;n;n>>=1)
		{
			if(n&1) for(int i=0;i<len;i++) ans[i]=1ll*ans[i]*a[i]%Mod;
			for(int i=0;i<len;i++) a[i]=1ll*a[i]*a[i]%Mod;
		}
		FWT(ans,len,0);
		printf("%d\n",ans[0]);
	}
	return 0;
}
