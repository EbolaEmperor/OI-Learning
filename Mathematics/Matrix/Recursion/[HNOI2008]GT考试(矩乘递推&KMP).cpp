#include<bits/stdc++.h>
using namespace std;

int ha;
struct Matrix
{
	int a[25][25],m,n;
	Matrix(){memset(a,0,sizeof(a));}
	int* operator [] (const int &x){return a[x];}
	
	friend Matrix operator * (Matrix &A,Matrix &B)
	{
		Matrix C;C.m=A.m;C.n=B.n;
		for(int i=0;i<A.m;i++)
			for(int j=0;j<B.n;j++)
				for(int k=0;k<A.n;k++)
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
} A;

int main()
{
	int n,m;
	static char s[25];
	static int nxt[25];
	scanf("%d%d%d%s",&n,&m,&ha,s+1);
	int len=strlen(s+1),j=0;
	for(int i=2;i<=len;i++)
	{
		while(j&&s[i]!=s[j+1]) j=nxt[j];
		if(s[i]==s[j+1]) j++;
		nxt[i]=j;
	}
	A.m=A.n=m;
	for(int i=0;i<len;i++)
		for(int k=0;k<=9;k++)
		{
			j=i;
			while(j&&s[j+1]!=k+'0') j=nxt[j];
			if(s[j+1]==k+'0') j++;
			if(j<m) A[i][j]++;
		}
	A=A^n;int ans=0;
	for(int i=0;i<m;i++) ans+=A[0][i];
	printf("%d\n",ans%ha);
	return 0;
}
