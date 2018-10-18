#include<iostream>
#include<cstdio>
#include<cstring>
#define Mod 10000
using namespace std;

struct Matrix
{
	int m,n;
	int a[55][55];
} G,A[15],B;
bool unable[15][55];

Matrix operator * (Matrix a,Matrix b)
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
	int n,m,s,t,k,a,b,T;
	scanf("%d%d%d%d%d",&n,&m,&s,&t,&k);
	memset(G.a,0,sizeof(G.a));
	G.m=G.n=n;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		G.a[a][b]=G.a[b][a]=1;
	}
	scanf("%d",&m);
	memset(unable,0,sizeof(unable));
	for(int i=1;i<=m;i++)
	{
		scanf("%d",&T);
		for(int j=0;j<T;j++)
		{
			scanf("%d",&a);
			for(int jj=j;jj<12;jj+=T)
				unable[jj][a]=1;
		}
	}
	B.m=B.n=n;
	memset(B.a,0,sizeof(B.a));
	for(int i=0;i<n;i++) B.a[i][i]=1;
	for(int tt=0;tt<12;tt++)
	{
		memset(A[tt].a,0,sizeof(A[tt].a));
		A[tt].m=A[tt].n=n;
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				A[tt].a[i][j]=(G.a[i][j]&&(!unable[tt][j]));
	}
	if(k>=12)
	{
		for(int i=1;i<12;i++) B=B*A[i];
		B=B*A[0];
		B=QuickPow(B,k/12);
		k%=12;
	}
	for(int i=1;i<=k;i++) B=B*A[i];
	cout<<B.a[s][t]<<endl;
	return 0;
}
