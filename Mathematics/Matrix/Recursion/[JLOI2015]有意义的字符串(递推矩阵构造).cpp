#include<iostream>
#include<cstdio>
using namespace std;

typedef unsigned long long LL;
const LL Mod=7528443412579576937ll;

struct Matrix
{
	int m,n;
	LL a[5][5];
	Matrix(int _m=0,int _n=0):m(_m),n(_n){}
};

LL QuickMul(LL a,LL b)
{
	LL ans=0;
	while(b)
	{
		if(b&1) ans=(ans+a)%Mod;
		a=(a+a)%Mod;
		b>>=1;
	}
	return ans;
}

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
			for(int k=1;k<=a.n;k++) ans.a[i][j]=(ans.a[i][j]+QuickMul(a.a[i][k],b.a[k][j]))%Mod;
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
	long long b,d;
	LL n;
	cin>>b>>d>>n;
	if(n==0) {cout<<1<<endl;return 0;}
	Matrix A;
	A.m=A.n=2;
	long long E=((d-b*b)%Mod+Mod)%Mod;
	b=(b%Mod+Mod)%Mod;
	A.a[1][1]=(LL)b;A.a[1][2]=((LL)E)/4;
	A.a[2][1]=1;A.a[2][2]=0;
	Matrix ans;
	ans.m=2;ans.n=1;
	ans.a[1][1]=(LL)b;ans.a[2][1]=2;
	if(n>1)
	{
		A=QuickPow(A,n-1);
		ans=A*ans;
	}
	LL x=ans.a[1][1];
	if(n%2==0) x--;
	cout<<x<<endl;
	return 0;
}
