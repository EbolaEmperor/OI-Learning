#include<bits/stdc++.h>
using namespace std;

int m,n,ha,f[1010][510],a[1010],b[1010];

int Pow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=1ll*a*a%ha)
		if(b&1) ans=1ll*ans*a%ha;
	return ans;
}

int lagrange(int *arrx,int *arry,int n,int x)
{
	int res=0;
	for(int i=0;i<n;i++)
	{
		int s1=1,s2=1;
		for(int j=0;j<n;j++)
		{
			if(i==j) continue;
			s1=1ll*s1*(x-arrx[j])%ha;
			s2=1ll*s2*(arrx[i]-arrx[j])%ha;
		}
		res=(res+1ll*s1*Pow(s2,ha-2)%ha*arry[i])%ha;
	}
	return res;
}

int main()
{
	scanf("%d%d%d",&m,&n,&ha);
	f[0][0]=1;
	for(int i=1;i<=2*n;i++)
	{
		f[i][0]=f[i-1][0];
		for(int j=1;j<=n;j++)
			f[i][j]=(f[i-1][j]+1ll*f[i-1][j-1]*i*j)%ha;
	}
	if(m<=2*n){printf("%d\n",f[m][n]);return 0;}
	for(int i=0;i<=2*n;i++) a[i]=i;
	for(int i=0;i<=2*n;i++) b[i]=f[i][n];
	printf("%d\n",lagrange(a,b,2*n+1,m));
	return 0;
}
