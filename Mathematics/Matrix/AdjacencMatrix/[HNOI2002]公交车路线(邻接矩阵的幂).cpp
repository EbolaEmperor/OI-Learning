#include<bits/stdc++.h>
#define Mod 1000
using namespace std;

struct Matrix
{
	int m,n;
	int a[15][15];
	void init(int x,int y){m=x;n=y;memset(a,0,sizeof(a));}
};

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
	Matrix G;
	G.init(8,8);
	for(int i=0;i<7;i++)
		G.a[i][i+1]=G.a[i+1][i]=1;
	G.a[0][7]=G.a[7][0]=1;
	G.a[4][3]=G.a[4][5]=0;
	int n;
	cin>>n;
	G=QuickPow(G,n);
	cout<<G.a[0][4]<<endl;
	return 0;
}
