#include<bits/stdc++.h>
using namespace std;

int ha;
struct Matrix
{
	int n,a[75][75];
	Matrix(){memset(a,0,sizeof(a));}
	int* operator [] (const int &x){return a[x];}
	void setrand(){for(int i=1;i<=n;i++) a[i][1]=rand()%ha;}
	
	friend Matrix operator * (Matrix &A,Matrix &B)
	{
		Matrix C;C.n=A.n;
		for(int i=1;i<=C.n;i++)
			for(int j=1;j<=C.n;j++)
				for(int k=1;k<=C.n;k++)
					C[i][j]=(C[i][j]+A[i][k]*B[k][j])%ha;
		return C;
	}
	
	friend Matrix operator ^ (Matrix A,int b)
	{
		Matrix ans=A;b--;
		for(;b;b>>=1,A=A*A)
			if(b&1) ans=ans*A;
		return ans;
	}

	friend bool operator == (Matrix &A,Matrix &B)
	{
		for(int i=1;i<=A.n;i++)
			for(int j=1;j<=A.n;j++)
				if(A[i][j]!=B[i][j]) return 0;
		return 1;
	}
} Hash[150];

int BSGS(Matrix &A,Matrix &B)
{
	int m=ceil(sqrt(ha));
	Matrix D;
	D.n=A.n;
	D.setrand();
	for(int i=0;i<m;i++)
	{
		Hash[i]=B*D;
		D=A*D;
	}
	Matrix base=A^m;
	for(int i=1;i<=m;i++)
	{
		for(int j=m;j>=0;j--)
			if(D==Hash[j]) return i*m-j;
		D=base*D;
	}
	return -1;
}

int main()
{
	int n;
	scanf("%d%d",&n,&ha);
	Matrix A,B;
	A.n=B.n=n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&A[i][j]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&B[i][j]);
	printf("%d\n",BSGS(A,B));
	return 0;
}
