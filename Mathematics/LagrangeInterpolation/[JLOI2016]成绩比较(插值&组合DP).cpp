#include<bits/stdc++.h>
#define ha 1000000007
using namespace std;

int Pow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=1ll*a*a%ha)
		if(b&1) ans=1ll*ans*a%ha;
	return ans;
}

int C[110][110];
int U[110],R[110],P[110];
int arrx[110],arry[110];
int n,m,K;
int f[110][110];

void Init()
{
	for(int i=0;i<=n;i++) C[i][0]=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%ha;
}

int Lagrange(int *x,int *y,int n,int k)
{
	int ans=0;
	for(int i=0;i<n;i++)
	{
		if(k==x[i]) return y[i];
		int s1=1,s2=1;
		for(int j=0;j<n;j++)
		{
			if(i==j) continue;
			s1=1ll*s1*(k-x[j])%ha;
			s2=1ll*s2*(x[i]-x[j])%ha;
		}
		ans=(ans+1ll*s1*Pow(s2,ha-2)%ha*y[i])%ha;
	}
	return (ans+ha)%ha;
}

int main()
{
	scanf("%d%d%d",&n,&m,&K);
	for(int i=1;i<=m;i++) scanf("%d",U+i);
	for(int i=1;i<=m;i++) scanf("%d",R+i);
	for(int i=1;i<=n+1;i++) arrx[i]=i;
	for(int T=1;T<=m;T++)
	{
		for(int i=1;i<=n+1;i++)
			arry[i]=(arry[i-1]+1ll*Pow(i,n-R[T])*Pow(U[T]-i,R[T]-1)%ha+ha)%ha;
		P[T]=Lagrange(arrx+1,arry+1,n+1,U[T]);
	}
	f[0][n-1]=1;Init();
	for(int i=1;i<=m;i++)
		for(int j=1;j<n;j++)
			for(int k=j;k<n;k++)
				if(n-R[i]-j>=0)
					f[i][j]=(f[i][j]+1ll*f[i-1][k]*C[k][j]%ha*C[n-k-1][n-R[i]-j]%ha*P[i])%ha;
	printf("%d\n",(f[m][K]+ha)%ha);
	return 0;
}
