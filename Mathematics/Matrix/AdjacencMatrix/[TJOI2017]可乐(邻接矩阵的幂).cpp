#include<iostream>
#include<cstdio>
#include<cstring>
#define Mod 2017
using namespace std;

struct Matrix
{
	int m,n;
	int a[35][35];
};

Matrix operator * (Matrix a,Matrix b)
{
	Matrix ans;
	ans.m=a.m;
	ans.n=b.n;
	for(int i=1;i<=a.m;i++)
		for(int j=1;j<=b.n;j++)
		{
			ans.a[i][j]=0;
			for(int k=1;k<=b.m;k++) ans.a[i][j]=(ans.a[i][j]+a.a[i][k]*b.a[k][j]%Mod)%Mod;
		}
	return ans;
}

Matrix QuickPow(Matrix a,int b)
{
	Matrix ans=a;
	b--;
	while(b)
	{
		if(b&1) ans=ans*a;
		a=a*a;
		b>>=1;
	}
	return ans;
}

int main()
{
	int n,m,a,b,t;
	cin>>n>>m;
	Matrix A;
	A.m=A.n=n+1;
	memset(A.a,0,sizeof(A.a));
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		A.a[a][b]=A.a[b][a]=1;
	}
	for(int i=1;i<=n;i++) A.a[i][i]=A.a[i][n+1]=1;
	A.a[n+1][n+1]=1;
	cin>>t;
	A=QuickPow(A,t);
	int ans=0;
	for(int i=1;i<=n+1;i++)
		ans=(ans+A.a[1][i])%Mod;
	cout<<ans<<endl;
	return 0;
}
