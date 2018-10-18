#include<bits/stdc++.h>
using namespace std;

typedef unsigned long long ULL;
int n,m,t;ULL k;
struct Matrix
{
	int m,n;
	ULL a[130][130],flag;
	Matrix(){memset(a,0,sizeof(a));}
	ULL* operator [] (const int &x){return a[x];}
	
	friend Matrix operator * (Matrix &A,Matrix &B)
	{
		Matrix C;C.m=A.m;C.n=B.n;C.flag=1;
		for(int i=1;i<=C.m;i++)
			for(int j=1;j<=C.n;j++)
				for(int l=1;l<=A.n;l++)
				{
					C[i][j]+=A[i][l]*B[l][j];
					if(C[1][t]>=k) C.flag=0;
				}
		return C;
	}
} P[70],E,G,NOW,TMP;

int main()
{
	int u,v,w;
	scanf("%d%d%llu",&n,&m,&k);
	t=3*n+1;G.m=G.n=t;
	for(int i=1;i<=n;i++)
		G[i][n+i]=G[n+i][2*n+i]=1;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&u,&v,&w);
		G[n*(w-1)+u][v]++;
		G[n*(w-1)+u][t]++;
	}
	G[t][t]=1;
	int bit;P[0]=G;E.m=1;E.n=t;
	for(int i=1;i<=n;i++) E[1][i]=1;
	for(bit=0;bit<=63;bit++)
	{
		TMP=E*P[bit];
		if(TMP[1][t]>=k) break;
		P[bit+1]=P[bit]*P[bit];
	}
	if((--bit)==63&&TMP[1][t]<k){puts("-1");return 0;}
	NOW=E;ULL ans=0;
	for(;bit>=0;bit--)
	{
		TMP=NOW*P[bit];
		if(TMP.flag&&TMP[1][t]<k)
			NOW=TMP,ans|=1ull<<bit;
	}
	printf("%llu\n",ans+1);
	return 0;
}
