#include<bits/stdc++.h>
using namespace std;

struct Matrix
{
	double a[2][2];int m,n;
	Matrix(int x=0,int y=0):m(x),n(y){memset(a,0,sizeof(a));}
	double* operator [] (const int &x){return a[x];}
	
	friend Matrix operator * (Matrix &A,Matrix &B)
	{
		Matrix C;C.m=A.m;C.n=B.n;
		for(int i=0;i<C.m;i++)
			for(int j=0;j<C.n;j++)
				for(int k=0;k<A.n;k++)
					C[i][j]+=A[i][k]*B[k][j];
		return C;
	}
	
	friend Matrix operator ^ (Matrix A,int b)
	{
		Matrix ans(A.m,A.n);
		for(int i=0;i<A.m;i++) ans[i][i]=1;
		for(;b;b>>=1,A=A*A)
			if(b&1) ans=ans*A;
		return ans;
	}
} A,B,C;

int main()
{
	static int pos[15];
	int n;double p;
	while(~scanf("%d%lf",&n,&p))
	{
		for(int i=1;i<=n;i++) scanf("%d",pos+i);
		sort(pos+1,pos+1+n);
		A=Matrix(2,2);
		A[0][0]=p;A[0][1]=1-p;A[1][0]=1;
		B=Matrix(2,1);
		B[0][0]=1;B[1][0]=0;
		int now=1;
		for(int i=1;i<=n;i++)
		{
			C=A^(pos[i]-now);
			B=C*B;
			B[0][0]=0;
			now=pos[i];
		}
		B=A*B;
		printf("%.7lf\n",B[0][0]);
	}
	return 0;
}
