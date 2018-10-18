#include<bits/stdc++.h>
#define Mod 45989
using namespace std;

struct Matrix
{
	int m,n;
	int a[150][150];
	void init(int x,int y){m=x;n=y;memset(a,0,sizeof(a));}
};
struct Edge{int from,to,next;} e[150];
int h[55],sum=-1;

void add_edge(int u,int v)
{
	sum++;
	e[sum].from=u;
	e[sum].to=v;
	e[sum].next=h[u];
	h[u]=sum;
}

Matrix operator * (const Matrix &a,const Matrix &b)
{
	Matrix ans;
	ans.m=a.m;
	ans.n=b.n;
	for(int i=0;i<a.m;i++)
		for(int j=0;j<b.n;j++)
		{
			ans.a[i][j]=0;
			for(int k=0;k<b.m;k++) ans.a[i][j]=(ans.a[i][j]+a.a[i][k]*b.a[k][j]%Mod)%Mod;
		}
	return ans;
}

Matrix QuickPow(Matrix &a,int b)
{
	Matrix ans;
	ans.init(a.m,a.n);
	for(int i=0;i<ans.m;i++) ans.a[i][i]=1;
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
	int n,m,t,a,b,u,v;
	cin>>n>>m>>t>>a>>b;
	for(int i=0;i<n;i++) h[i]=-1;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d",&u,&v);
		add_edge(u,v);
		add_edge(v,u);
	}
	Matrix E;
	E.init(2*m+1,2*m+1);
	for(int i=0;i<2*m;i++)
		for(int tmp=h[e[i].to];tmp!=-1;tmp=e[tmp].next)
			if(tmp!=(i^1)) E.a[i][tmp]=1;
	E=QuickPow(E,t-1);
	Matrix A;
	A.init(2*m+1,2*m+1);
	for(int tmp=h[a];tmp!=-1;tmp=e[tmp].next)
		A.a[2*m][tmp]=1;
	A=A*E;
	int ans=0;
	for(int tmp=h[b];tmp!=-1;tmp=e[tmp].next)
		ans=(ans+A.a[2*m][tmp^1])%Mod;
	cout<<ans<<endl;
	return 0;
}
