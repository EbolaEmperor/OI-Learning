#include<bits/stdc++.h>
#define Mod 4147
using namespace std;

struct Matrix
{
	int m,n;
	int a[110][110];
	void init(int x,int y){m=x;n=y;memset(a,0,sizeof(a));}
} A,B;

Matrix operator * (const Matrix &a,const Matrix &b)
{
	Matrix ans;
	ans.m=a.m;
	ans.n=b.n;
	for(int i=0;i<a.m;i++)
		for(int j=0;j<b.n;j++)
		{
			ans.a[i][j]=0;
			for(int k=0;k<b.m;k++) ans.a[i][j]=(ans.a[i][j]+a.a[i][k]*b.a[k][j]%Mod)%Mod;
		}
	return ans;
}

Matrix QuickPow(Matrix &a,int b)
{
	Matrix ans;
	ans.init(a.m,a.n);
	for(int i=0;i<ans.m;i++) ans.a[i][i]=1;
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
	B.init(n,1);
	for(int i=0;i<n;i++)
		scanf("%d",&B.a[i][0]);
	A.init(n,n);
	for(int i=0;i<n;i++)
		scanf("%d",&A.a[0][i]);
	for(int i=1;i<n;i++) A.a[i][i-1]=1;
	A=QuickPow(A,m-n);
	B=A*B;
	cout<<B.a[0][0]<<endl;
	return 0;
}
