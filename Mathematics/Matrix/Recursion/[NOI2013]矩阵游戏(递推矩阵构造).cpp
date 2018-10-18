#include<iostream>
#include<cstdio>
#include<cstring>
#define Mod 1000000007
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
			for(int k=1;k<=a.n;k++) ans.a[i][j]=(ans.a[i][j]+a.a[i][k]*b.a[k][j]%Mod)%Mod;
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

LL read(string s,LL p)
{
	int pos=0;
	char c=s[pos++];
	LL ans=0;
	while(c<'0'&&c>'9') c=s[pos++];
	while(c>='0'&&c<='9') ans=(ans*10+c-'0')%p,c=s[pos++];
	return ans;
}

int main()
{
	LL n,m,a,b,c,d;
	string s1,s2;
	cin>>s1>>s2>>a>>b>>c>>d;
	if(a==1) n=read(s1,Mod);else n=read(s1,Mod-1);
	if(c==1) m=read(s2,Mod);else m=read(s2,Mod-1);
	Matrix A;
	A.m=A.n=2;
	A.a[1][1]=a;A.a[1][2]=b;
	A.a[2][1]=0;A.a[2][2]=1;
	A=QuickPow(A,m-1);
	Matrix B;
	B.m=B.n=2;
	B.a[1][1]=c;B.a[1][2]=d;
	B.a[2][1]=0;B.a[2][2]=1;
	B=B*A;
	B=QuickPow(B,n-1);
	A=A*B;
	Matrix ans;
	ans.m=2;ans.n=1;
	ans.a[1][1]=ans.a[2][1]=1;
	ans=A*ans;
	cout<<ans.a[1][1]<<endl;
	return 0;
}
