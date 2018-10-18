#include<bits/stdc++.h>
#define ha 1000000007
using namespace std;

typedef long long LL;
struct Matrix
{
	int a[3][3];
	Matrix(){memset(a,0,sizeof(a));}
	int* operator [] (const int &x){return a[x];}
	
	friend Matrix operator * (Matrix A,Matrix B)
	{
		Matrix C;
		for(int i=1;i<=2;i++)
			for(int j=1;j<=2;j++)
				for(int k=1;k<=2;k++)
					C[i][j]=(C[i][j]+1ll*A[i][k]*B[k][j])%ha;
		return C;
	}
	
	friend Matrix operator ^ (Matrix A,LL x)
	{
		Matrix ans;
		ans[1][1]=ans[2][2]=1;
		for(;x;x>>=1,A=A*A)
			if(x&1) ans=ans*A;
		return ans;
	}
};

LL fib[70];

LL gao(LL x)
{
	LL dafa=0;bool flag=0;
	for(int i=63;i>=0;i--)
		if(x&(1ll<<i-1))
		{
			dafa+=fib[i];
			if(flag) return dafa-1;
			flag=1;
		}
		else flag=0;
	return dafa;
}

int main()
{
	int res=0,T;LL n;
	fib[0]=fib[1]=1;
	for(int i=2;i<64;i++)
		fib[i]=fib[i-1]+fib[i-2];
	for(scanf("%d",&T);T;T--)
	{
		scanf("%lld",&n);
		printf("%lld\n",gao(n));
		Matrix A;
		A[1][1]=A[1][2]=A[2][1]=1;
		Matrix B;
		B[1][1]=B[2][1]=1;
		B=(A^n)*B;
		printf("%d\n",B[1][1]);
	}
	return 0;
}
