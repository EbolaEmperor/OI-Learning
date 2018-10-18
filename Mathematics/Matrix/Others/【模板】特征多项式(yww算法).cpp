#include<bits/stdc++.h>
#define pii pair<int,int>
#define ha 998244353
#define fi first
#define se second
using namespace std;

inline int read()
{
	int x=0,fg=1;char c=getchar();
	while(!isdigit(c)&&c!='-') c=getchar();
	if(c=='-') fg=-1,c=getchar();
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	return x;
}

int Pow(int a,int b)
{
	int ans=1;
	for(;b;b>>=1,a=1ll*a*a%ha)
		if(b&1) ans=1ll*ans*a%ha;
	return ans;
}

struct Poly
{
	int n,a[510];
	Poly(){memset(a,0,sizeof(a));n=0;}
	int& operator [] (const int &x){return a[x];}
} f[510];
int A[510][510],n;
pii c[510][510];

void gauss()
{
	for(int i=1;i<=n;i++)
	{
		int pos=i+1;
		while(pos<=n&&A[i][pos]==0) pos++;
		if(pos>n) continue;
		for(int j=i;j<=n;j++) swap(A[i+1][j],A[pos][j]);
		for(int j=1;j<=n;j++) swap(A[j][i+1],A[j][pos]);
		int inv=Pow(A[i+1][i],ha-2);
		for(int j=i+2;j<=n;j++)
		{
			if(A[j][i]==0) continue;
			int t=1ll*A[j][i]*inv%ha;
			for(int k=i;k<=n;k++) A[j][k]=(A[j][k]-1ll*A[i+1][k]*t%ha+ha)%ha;
			for(int k=1;k<=n;k++) A[k][i+1]=(A[k][i+1]+1ll*A[k][j]*t%ha)%ha;
		}
	}
}

void mul(Poly &A,Poly &B,pii v)
{
	A.n=max(A.n,B.n+bool(v.fi));
	for(int i=0;i<=A.n;i++)
	{
		A[i]=(A[i]+1ll*B[i]*v.se)%ha;
		if(i) A[i]=(A[i]+1ll*B[i-1]*v.fi)%ha;
	}
}

pii operator * (pii a,int x){return pii(1ll*a.fi*x%ha,1ll*a.se*x%ha);}
pii operator * (pii a,pii b){return pii((1ll*a.fi*b.se+1ll*a.se*b.fi)%ha,1ll*a.se*b.se%ha);}

void gao()
{
	f[n+1][0]=1;
	for(int i=n;i>=1;i--)
	{
		pii v(0,1);
		for(int j=i+1;j<=n+1;j++)
		{
			mul(f[i],f[j],v*c[i][j-1]*((j-i)&1?1:-1));
			v=v*c[j][j-1];
		}
	}
}

int main()
{
	n=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			A[i][j]=read();
	gauss();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
		{
			c[i][j].se=(ha-A[i][j])%ha;
			if(i==j) c[i][j].fi=1;
		}
	gao();
	for(int i=0;i<=n;i++) printf("%d ",(f[1][i]+ha)%ha);
	return 0;
}
