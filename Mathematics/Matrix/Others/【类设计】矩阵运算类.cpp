#include<bits/stdc++.h>
using namespace std;

typedef long long LL;

const double eps=1e-9;
int dcmp(double x)
{
	if(fabs(x)<=eps) return 0;
	else if(x>0) return 1;
	else return -1;
}

struct Matrix
{
	int m,n;
	LL a[100][100];
	Matrix(int _m=0,int _n=0):m(_m),n(_n){}
	friend ostream& operator << (ostream &out,const Matrix &mat)
	{
		for(int i=1;i<=mat.m;i++)
		{
			for(int j=1;j<=mat.n;j++)
				out<<mat.a[i][j]<<" ";
			out<<endl;
		}
		return out;
	}
};

Matrix operator % (Matrix a,LL p)
{
	for(int i=1;i<=a.m;i++)
		for(int j=1;j<=a.n;j++)
			a.a[i][j]%=p;
	return a;
}

Matrix operator * (Matrix a,LL b)
{
	for(int i=1;i<=a.m;i++)
		for(int j=1;j<=a.n;j++)
			a.a[i][j]*=b;
	return a;
}
Matrix operator * (LL b,Matrix a) {return a*b;}

Matrix operator * (Matrix a,Matrix b)
{
	if(a.n!=b.m)
	{
		puts("[Error] Multiply: The column of A isn't equal to the line number of B");
		exit(0);
	}
	Matrix ans;
	ans.m=a.m;
	ans.n=b.n;
	for(int i=1;i<=a.m;i++)
		for(int j=1;j<=b.n;j++)
		{
			ans.a[i][j]=0;
			for(int k=1;k<=a.n;k++) ans.a[i][j]+=a.a[i][k]*b.a[k][j];
		}
	return ans;
}

Matrix operator ^ (Matrix a,LL b)
{
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

LL Det(Matrix a)
{
	if(a.m!=a.n)
	{
		puts("[Error] Determinant: Line number isn't equal to column number.");
		exit(0);
	}
	int n=a.n;
	double g[100][100];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			g[i][j]=(double)a.a[i][j];
	for(int i=1;i<=n;i++)
	{
		int pos=i;
		while(dcmp(g[pos][i])==0&&pos<n) pos++;
		if(dcmp(g[pos][i])==0) return 0;
		if(pos!=i)
			for(int j=1;j<=n;j++) swap(g[i][j],g[pos][j]);
		for(int j=i+1;j<=n;j++)
		{
			if(dcmp(g[j][i])==0) continue;
			double t=g[j][i]/g[i][i];
			for(int k=1;k<=n;k++)
				g[j][k]-=t*g[i][k];
		}
	}
	double ans=1;
	for(int i=1;i<=n;i++) ans*=g[i][i];
	return (LL)round(ans);
}

struct ModMatrix
{
	int m,n;
	LL p;
	LL a[100][100];
	ModMatrix(int _m=0,int _n=0,LL _p=0):m(_m),n(_n),p(_p){}
};

ModMatrix operator % (ModMatrix a,LL p)
{
	for(int i=1;i<=a.m;i++)
		for(int j=1;j<=a.n;j++)
			a.a[i][j]%=p;
	return a;
}

ModMatrix operator * (ModMatrix a,LL b)
{
	for(int i=1;i<=a.m;i++)
		for(int j=1;j<=a.n;j++)
			a.a[i][j]=a.a[i][j]*b%a.p;
	return a;
}
ModMatrix operator * (LL b,ModMatrix a) {return a*b;}

ModMatrix operator * (ModMatrix a,ModMatrix b)
{
	if(a.n!=b.m)
	{
		puts("[Error] Multiply: The column of A isn't equal to the line number of B");
		exit(0);
	}
	ModMatrix ans;
	ans.m=a.m;
	ans.n=b.n;
	ans.p=a.p;
	for(int i=1;i<=a.m;i++)
		for(int j=1;j<=b.n;j++)
		{
			ans.a[i][j]=0;
			for(int k=1;k<=a.n;k++) ans.a[i][j]=(ans.a[i][j]+a.a[i][k]*b.a[k][j]%a.p)%a.p;
		}
	return ans;
}

ModMatrix operator ^ (ModMatrix a,LL b)
{
	if(b==0) return ModMatrix(0,0,a.p);
	ModMatrix ans=a;
	b--;
	while(b)
	{
		if(b&1) ans=ans*a;
		a=a*a;
		b>>=1;
	}
	return ans;
}

LL inv(LL a,LL p)
{
	a%=p;
	LL b=p-2,ans=1;
	while(b)
	{
		if(b&1) ans=ans*a%p;
		a=a*a%p;
		b>>=1;
	}
	return ans;
}

LL QuickMul(LL a,LL b,LL p)
{
	LL fg=1,ans=0;
	if(a<0) fg=-fg,a=-a;
	if(b<0) fg=-fg,b=-b;
	while(b)
	{
		if(b&1) ans=(ans+a)%p;
		a=(a+a)%p;
		b>>=1;
	}
	return ans*fg;
}

LL Det(ModMatrix a)
{
	if(a.m!=a.n)
	{
		puts("[Error] Determinant: Line number isn't equal to column number.");
		exit(0);
	}
	int n=a.n;
	LL ans=1;
	for(int i=1;i<=n;i++)
	{
		int pos=i;
		while(a.a[pos]==0&&pos<n) pos++;
		if(a.a[pos][i]==0) return 0;
		if(pos!=i)
		{
			ans=-ans;
			for(int j=1;j<=n;j++) swap(a.a[i][j],a.a[pos][j]);
		}
		LL t=inv(a.a[i][i],a.p);
		for(int j=i+1;j<=n;j++)
		{
			if(a.a[j][i]==0) continue;
			LL mul=a.a[j][i]*t%a.p;
			for(int k=1;k<=n;k++)
				a.a[j][k]=(a.a[j][k]-QuickMul(a.a[i][k],mul,a.p))%a.p;
		}
	}
	for(int i=1;i<=n;i++) ans=QuickMul(ans,a.a[i][i],a.p);
	return (ans%a.p+a.p)%a.p;
}

int main()
{
}
