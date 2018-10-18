#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

typedef long long LL;
LL Mod;

struct Matrix
{
	int m,n;
	LL a[20][20];
	Matrix(int _m=0,int _n=0):m(_m),n(_n){}
};

LL QuickMul(LL a,LL b)
{
	LL ans=0;
	while(b)
	{
		if(b&1) ans=(ans+a)%Mod;
		a=(a+a)%Mod;
		b>>=1;
	}
	return ans;
}

Matrix operator * (Matrix a,Matrix b)
{
	if(a.n!=b.m) return Matrix(0,0);
	Matrix ans;
	ans.m=a.m;
	ans.n=b.n;
	for(int i=1;i<=a.m;i++)
		for(int j=1;j<=b.n;j++)
		{
			ans.a[i][j]=0;
			for(int k=1;k<=a.n;k++) ans.a[i][j]=(ans.a[i][j]+QuickMul(a.a[i][k],b.a[k][j]))%Mod;
		}
	return ans;
}

Matrix QuickPow(Matrix a,LL b)
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

int main()
{
	LL n;
	LL p,q,r,t,u,v,w,x,y,z;
	cin>>n>>Mod>>p>>q>>r>>t>>u>>v>>w>>x>>y>>z;
	Matrix A;
	A.m=A.n=11;
	memset(A.a,0,sizeof(A.a));
	A.a[1][1]=p;A.a[1][2]=1;A.a[1][3]=1;A.a[1][4]=q;A.a[1][7]=r;A.a[1][8]=t-2*r;A.a[1][11]=r-t+1;
	A.a[2][1]=1;A.a[2][2]=u;A.a[2][3]=1;A.a[2][5]=v;A.a[2][9]=1;
	A.a[3][1]=1;A.a[3][2]=1;A.a[3][3]=x;A.a[3][6]=y;A.a[3][8]=1;A.a[3][10]=1;A.a[3][11]=1;
	A.a[4][1]=1;A.a[5][2]=1;A.a[6][3]=1;
	A.a[7][7]=1;A.a[7][8]=2;A.a[7][11]=1;
	A.a[8][8]=1;A.a[8][11]=1;
	A.a[9][9]=w;A.a[10][10]=z;A.a[11][11]=1;
	for(int i=1;i<=11;i++)
		for(int j=1;j<=11;j++) A.a[i][j]=(A.a[i][j]%Mod+Mod)%Mod;
	A=QuickPow(A,n-2);
	Matrix ans;
	ans.m=11;
	ans.n=1;
	ans.a[1][1]=3;ans.a[2][1]=3;ans.a[3][1]=3;
	ans.a[4][1]=1;ans.a[5][1]=1;ans.a[6][1]=1;
	ans.a[7][1]=4;
	ans.a[8][1]=2;
	ans.a[9][1]=w%Mod;
	ans.a[10][1]=z%Mod;
	ans.a[11][1]=1;
	ans=A*ans;
	cout<<"nodgd "<<ans.a[1][1]<<endl;
	cout<<"Ciocio "<<ans.a[2][1]<<endl;
	cout<<"Nicole "<<ans.a[3][1]<<endl;
	return 0;
}
