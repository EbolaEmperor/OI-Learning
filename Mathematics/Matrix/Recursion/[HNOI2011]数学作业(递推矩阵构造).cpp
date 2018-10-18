#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

typedef long long LL;
LL Mod;

struct Matrix
{
	int m,n;
	LL a[10][10];
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

int lg(LL x)
{
	int ans=0;
	while(x/10!=0) ans++,x/=10;
	return ans;
}

LL Pow10(int x)
{
	LL ans=1;
	while(x) ans*=10,x--;
	return ans;
}

int main()
{
	LL n;
	cin>>n>>Mod;
	if(n==1) {cout<<1<<endl;return 0;}
	int cnt=lg(n);
	Matrix ans;
	ans.m=3;ans.n=1;
	ans.a[1][1]=ans.a[2][1]=ans.a[3][1]=1;
	for(int i=1;i<=cnt;i++)
	{
		Matrix A;
		A.m=A.n=3;
		memset(A.a,0,sizeof(A.a));
		A.a[1][1]=Pow10(i);A.a[1][2]=A.a[1][3]=1;
		A.a[2][2]=A.a[2][3]=A.a[3][3]=1;
		LL b=(i==1)?8:(Pow10(i)-Pow10(i-1));
		A=QuickPow(A,b);
		ans=A*ans;
	}
	LL res=(cnt==0)?(n-1):(n-Pow10(cnt)+1);
	if(res>=1)
	{
		Matrix A;
		A.m=A.n=3;
		memset(A.a,0,sizeof(A.a));
		A.a[1][1]=Pow10(cnt+1);A.a[1][2]=A.a[1][3]=1;
		A.a[2][2]=A.a[2][3]=A.a[3][3]=1;
		A=QuickPow(A,res);
		ans=A*ans;
	}
	cout<<ans.a[1][1]<<endl;
	return 0;
}
