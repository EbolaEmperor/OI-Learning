#include<bits/stdc++.h>
using namespace std;

typedef long long LL;

struct ModMatrix
{
	int m,n;
	LL p;
	LL a[255][255];
	ModMatrix(int _m=0,int _n=0,LL _p=0):m(_m),n(_n),p(_p){}
} G;

LL inv(LL a,LL p)
{
	LL b=p-2,ans=1;
	while(b)
	{
		if(b&1) ans=ans*a%p;
		a=a*a%p;
		b>>=1;
	}
	return ans;
}

LL Det(ModMatrix &a)
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
		while(a.a[pos][i]==0&&pos<n) pos++;
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
				a.a[j][k]=(a.a[j][k]-a.a[i][k]*mul)%a.p;
		}
	}
	for(int i=1;i<=n;i++) ans=ans*a.a[i][i]%a.p;
	return (ans%a.p+a.p)%a.p;
}

int main()
{
	int n,m,a,b;
	cin>>n>>m;
	G.m=G.n=n;
	G.p=10007;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&a,&b);
		if(a!=b)
		{
			G.a[a][a]++;
			G.a[b][a]--;
		}
	}
	G.m--;G.n--;
	for(int i=1;i<=G.m;i++)
		for(int j=1;j<=G.n;j++)
			G.a[i][j]=G.a[i+1][j+1];
	cout<<Det(G)<<endl;
	return 0;
}
