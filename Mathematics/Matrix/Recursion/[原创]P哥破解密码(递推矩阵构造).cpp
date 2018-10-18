#include<bits/stdc++.h>
#define ha 19260817
using namespace std;

struct Matrix
{
	int m,n;
	int a[5][5];
	Matrix(){memset(a,0,sizeof(a));}
	int* operator [] (const int &x){return a[x];}
	
	friend Matrix operator * (Matrix A,Matrix B)
	{
		Matrix C;
		C.m=A.m;C.n=B.n;
		for(int i=1;i<=C.m;i++)
			for(int j=1;j<=C.n;j++)
				for(int k=1;k<=A.n;k++)
					C[i][j]=(C[i][j]+1ll*A[i][k]*B[k][j])%ha;
		return C;
	}
	
	friend Matrix operator ^ (Matrix A,int b)
	{
		Matrix ans=A;b--;
		for(;b;b>>=1,A=A*A)
			if(b&1) ans=ans*A;
		return ans;
	}
};

int main()
{
	int m,n;
	for(scanf("%d",&m);m;m--)
	{
		scanf("%d",&n);
		Matrix A,B;
		A.m=A.n=3;
		A[1][1]=A[1][2]=A[1][3]=1;
		A[2][1]=A[3][2]=1;
		B.m=3;B.n=1;
		B[1][1]=1;
		B=(A^n)*B;
		printf("%d\n",(B[1][1]+B[2][1]+B[3][1])%ha);
	}
	return 0;
}
