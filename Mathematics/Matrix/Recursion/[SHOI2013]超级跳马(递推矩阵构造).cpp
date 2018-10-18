#include<bits/stdc++.h>
#define Mod 30011
using namespace std;

struct Matrix
{
	int m,n;
	int a[110][110];
} a,b,c;

Matrix operator * (const Matrix &a,const Matrix &b)
{
	Matrix c;
	c.m=a.m;c.n=b.n;
	for(int i=1;i<=a.m;i++)
		for(int j=1;j<=b.n;j++)
		{
			c.a[i][j]=0;
			for(int k=1;k<=a.n;k++)
				c.a[i][j]=(c.a[i][j]+a.a[i][k]*b.a[k][j])%Mod;
		}
	return c;
}

Matrix operator ^ (Matrix a,int b)
{
	Matrix ans=a;b--;
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
	int n,m;
	cin>>n>>m;
	b.m=2*n;b.n=1;
	b.a[1][1]=b.a[n+1][1]=b.a[n+2][1]=1;
	a.m=a.n=2*n;
	for(int i=1;i<=n;i++) a.a[i][n+i]=1;
	for(int i=n+1;i<=2*n;i++) a.a[i][i-n]=1;
	a.a[n+1][n+1]=a.a[n+1][n+2]=1;
	for(int i=n+2;i<2*n;i++)
		a.a[i][i]=a.a[i][i-1]=a.a[i][i+1]=1;
	a.a[2*n][2*n]=a.a[2*n][2*n-1]=1;
	c=a^(m-3);
	b=c*b;
	int ans1=b.a[n][1];
	b=a*b;
	cout<<(b.a[2*n][1]-ans1+Mod)%Mod<<endl;
	return 0;
}
