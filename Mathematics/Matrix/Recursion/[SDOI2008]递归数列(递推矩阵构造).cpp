#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
LL Mod;

struct Matrix
{
	int m,n;
	LL a[100][100];
	Matrix(int _m=0,int _n=0):m(_m),n(_n){}
};

Matrix operator * (Matrix a,Matrix b)
{
	if(a.n!=b.m) return Matrix(0,0);
	Matrix ans;
	ans.m=a.m;
	ans.n=a.n;
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
	//cout<<b<<endl;
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

LL sum(Matrix A,Matrix B,LL n)
{
	if(n<B.m)
	{
		LL ans=0;
		for(int i=B.m+1-n;i<=B.m;i++) ans=(ans+B.a[i][1])%Mod;
		return ans;
	}
	A=QuickPow(A,n-B.m+1);
	B=A*B;
	return B.a[1][1];
}

void Init(Matrix &a)
{
	for(int i=1;i<=a.m;i++)
		for(int j=1;j<=a.n;j++)
			a.a[i][j]=(a.a[i][j]%Mod+Mod)%Mod;
}

int main()
{
	int k;
	cin>>k;
	Matrix ans;
	ans.m=k+1;
	ans.n=1;
	ans.a[1][1]=0;
	for(int i=k;i>=1;i--)
	{
		cin>>ans.a[i+1][1];
		ans.a[1][1]+=ans.a[i+1][1];
	}
	Matrix A;
	A.m=A.n=k+1;
	memset(A.a,0,sizeof(A.a));
	for(int i=1;i<=k;i++)
	{
		cin>>A.a[1][i+1];
		A.a[2][i+1]=A.a[1][i+1];
	}
	LL m,n;
	cin>>m>>n>>Mod;
	A.a[1][1]=1;
	for(int i=1;i<k;i++) A.a[i+2][i+1]=1;
	Init(A);Init(ans);
	LL sm=sum(A,ans,m-1);
	LL sn=sum(A,ans,n);
	LL s=((sn-sm)%Mod+Mod)%Mod;
	cout<<s<<endl;
	return 0;
}
