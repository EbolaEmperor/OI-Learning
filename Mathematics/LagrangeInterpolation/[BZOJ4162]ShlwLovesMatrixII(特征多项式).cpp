#include<bits/stdc++.h>
#define ha 1000000007
using namespace std;

int Pow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=1ll*a*a%ha)
		if(b&1) ans=1ll*ans*a%ha;
	return ans;
}

struct Matrix
{
	int n,a[55][55];
	Matrix(){memset(a,0,sizeof(a));}
	int* operator [] (const int &x){return a[x];}
	
	friend Matrix operator * (Matrix &A,Matrix &B)
	{
		Matrix C;C.n=A.n;
		for(int i=1;i<=A.n;i++)
			for(int j=1;j<=A.n;j++)
				for(int k=1;k<=A.n;k++)
					C[i][j]=(C[i][j]+1ll*A[i][k]*B[k][j])%ha;
		return C;
	}
};

struct Poly
{
	int n,a[155];
	Poly(){memset(a,0,sizeof(a));n=0;}
	int& operator [] (const int &x){return a[x];}
	
	friend Poly operator * (Poly A,Poly B)
	{
		Poly C;C.n=A.n+B.n;
		for(int i=0;i<=A.n;i++)
			for(int j=0;j<=B.n;j++)
				C[i+j]=(C[i+j]+1ll*A[i]*B[j])%ha;
		return C;
	}
	
	friend Poly operator * (Poly A,int x)
	{
		Poly C=A;
		for(int i=0;i<=C.n;i++)
			C[i]=1ll*C[i]*x%ha;
		return C;
	}
	
	friend Poly operator + (Poly A,Poly B)
	{
		Poly C;C.n=max(A.n,B.n);
		for(int i=0;i<=C.n;i++)
			C[i]=(A[i]+B[i])%ha;
		return C;
	}
	
	friend Poly operator % (Poly A,Poly B)
	{
		for(int i=A.n-B.n;i>=0;i--)
		{
			int k=1ll*A[i+B.n]*Pow(B[B.n],ha-2)%ha;
			for(int j=0;j<=B.n;j++)
				A[i+j]=(A[i+j]-1ll*B[j]*k%ha+ha)%ha;
		}
		A.n=B.n-1;
		return A;
	}
};

int Det(Matrix &A)
{
	int ans=1;
	for(int i=1;i<=A.n;i++)
	{
		int pos=i;
		while(pos<=A.n&&A[pos][i]==0) pos++;
		if(!A[pos][i]) return 0;
		if(pos!=i)
		{
			ans=1ll*ans*(ha-1)%ha;
			for(int j=1;j<=A.n;j++)
				swap(A[pos][j],A[i][j]);
		}
		ans=1ll*ans*A[i][i]%ha;
		int inv=Pow(A[i][i],ha-2);
		for(int j=1;j<=A.n;j++)
		{
			if(i==j||A[j][i]==0) continue;
			int t=1ll*A[j][i]*inv%ha;
			for(int k=1;k<=A.n;k++)
				A[j][k]=(A[j][k]-1ll*A[i][k]*t%ha+ha)%ha;
		}
	}
	return ans;
}

char s[10010];
int n,k;
Matrix A,B,ans;
int ay[55];

Poly Lagrange(int n)
{
	Poly res;
	for(int i=0;i<=n;i++)
	{
		Poly s1;
		s1[0]=1;
		for(int j=0;j<=n;j++)
		{
			if(i==j) continue;
			Poly tmp;tmp.n=1;
			tmp[0]=(ha-j)%ha;tmp[1]=1;
			s1=s1*tmp*Pow((i-j+ha)%ha,ha-2);
		}
		res=res+s1*ay[i];
	}
	return res;
}

int main()
{
	scanf("%s%d",s,&k);A.n=k;
	for(int i=1;i<=k;i++)
		for(int j=1;j<=k;j++)
			scanf("%d",&A[i][j]);
	for(int x=0;x<=k;x++)
	{
		B=A;
		for(int i=1;i<=k;i++)
			B[i][i]=(B[i][i]-x+ha)%ha;
		ay[x]=Det(B);
	}
	Poly cp=Lagrange(k),falun,dafa;
	falun.n=1;falun[1]=1;dafa[0]=1;
	for(int i=strlen(s)-1;i>=0;i--,falun=falun*falun%cp)
		if(s[i]=='1') dafa=dafa*falun%cp;
	for(int i=1;i<=k;i++) B[i][i]=1;
	for(int t=0;t<k;t++,B=A*B)
		for(int i=1;i<=k;i++)
			for(int j=1;j<=k;j++)
				ans[i][j]=(ans[i][j]+1ll*B[i][j]*dafa[t])%ha;
	for(int i=1;i<=k;i++)
	{
		for(int j=1;j<=k;j++)
			printf("%d ",ans[i][j]);
		puts("");
	}
	return 0;
}
