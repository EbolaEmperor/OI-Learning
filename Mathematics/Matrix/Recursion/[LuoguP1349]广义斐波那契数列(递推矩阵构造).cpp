#include<iostream>
#include<cstdio>
using namespace std;

typedef long long LL;

struct Matrix
{
	LL a[100][100];
	int m,n;
	Matrix(int _m=0,int _n=0):m(_m),n(_n){}
};
LL m;

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
			for(int k=1;k<=a.n;k++) ans.a[i][j]=(ans.a[i][j]+a.a[i][k]*b.a[k][j]%m)%m;
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
	LL p,q,a1,a2,n;
	cin>>p>>q>>a1>>a2>>n>>m;
	a1%=m;a2%=m;p%=m;q%=m;
	if(n==1) {cout<<a1<<endl;return 0;}
	if(n==2) {cout<<a2<<endl;return 0;}
	Matrix A;
	A.m=A.n=2;
	A.a[1][1]=p;A.a[1][2]=q;
	A.a[2][1]=1;A.a[2][2]=0;
	A=QuickPow(A,n-2);
	Matrix ans;
	ans.m=2;ans.n=1;
	ans.a[1][1]=a2;
	ans.a[2][1]=a1;
	ans=A*ans;
	cout<<ans.a[1][1]<<endl;
	return 0;
}
