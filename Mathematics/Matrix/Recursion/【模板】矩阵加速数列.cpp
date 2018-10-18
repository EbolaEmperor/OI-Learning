#include<iostream>
#include<cstdio>
#define MOD 1000000007
using namespace std;

typedef long long LL;

struct Matrix
{
	int m,n;
	LL a[5][5];
	Matrix(int _m=0,int _n=0):m(_m),n(_n){}
};

Matrix operator * (Matrix a,Matrix b)
{
	if(a.n!=b.m) return Matrix(0,0);
	Matrix ans;
	ans.m=a.m;
	ans.n=b.n;
	for(int i=1;i<=a.m;i++)
		for(int j=1;j<=b.n;j++)
		{
			ans.a[i][j]=0;
			for(int k=1;k<=a.n;k++) ans.a[i][j]=(ans.a[i][j]+a.a[i][k]*b.a[k][j]%MOD)%MOD;
		}
	return ans;
}

Matrix QuickPow(Matrix a,LL b)
{
	if(b==0) return Matrix(0,0);
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
	int T;
	for(cin>>T;T;T--)
	{
		LL n;
		cin>>n;
		if(n<=3) {cout<<1<<endl;continue;}
		Matrix A;
		A.m=A.n=3;
		A.a[1][1]=1;A.a[1][2]=0;A.a[1][3]=1;
		A.a[2][1]=1;A.a[2][2]=0;A.a[2][3]=0;
		A.a[3][1]=0;A.a[3][2]=1;A.a[3][3]=0;
		A=QuickPow(A,n-3);
		Matrix ans;
		ans.m=3;
		ans.n=1;
		ans.a[1][1]=ans.a[2][1]=ans.a[3][1]=1;
		ans=A*ans;
		cout<<ans.a[1][1]<<endl;
	}
	return 0;
}
