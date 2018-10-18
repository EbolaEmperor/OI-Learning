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

int Gauss(int A[20][20],int n)
{
	int ans=1;
	for(int i=1;i<n;i++)
	{
		int pos=i;
		while(pos<n&&!A[pos][i]) pos++;
		if(!A[pos][i]) return 0;
		if(pos!=i)
		{
			ans=-ans;
			for(int j=1;j<n;j++)
				swap(A[pos][j],A[i][j]);
		}
		ans=1ll*ans*A[i][i]%ha;
		int inv=Pow(A[i][i],ha-2);
		for(int j=i+1;j<n;j++)
		{
			int t=1ll*A[j][i]*inv%ha;
			for(int k=1;k<n;k++)
				A[j][k]=(A[j][k]-1ll*A[i][k]*t%ha+ha)%ha;
		}
	}
	return (ans+ha)%ha;
}

struct Edge{int u,v;} G[20][410];
int A[20][20],M[20];

int main()
{
	int n,u,v;
	scanf("%d",&n);
	for(int i=1;i<n;i++)
	{
		scanf("%d",M+i);
		for(int j=1;j<=M[i];j++)
		{
			scanf("%d%d",&u,&v);
			G[i][j]=Edge{u,v};
		}
	}
	int ans=0;
	for(int i=0;i<(1<<n-1);i++)
	{
		memset(A,0,sizeof(A));
		int colornum=0;
		for(int j=1;j<n;j++)
			if(i&(1<<j-1))
			{
				for(int k=1;k<=M[j];k++)
				{
					int u=G[j][k].u,v=G[j][k].v;
					A[u][v]--;A[v][u]--;
					A[u][u]++;A[v][v]++;
				}
				colornum++;
			}
		if((n-1-colornum)&1) ans=(ans-Gauss(A,n)+ha)%ha;
		else ans=(ans+Gauss(A,n))%ha;
	}
	printf("%d\n",(ans+ha)%ha);
	return 0;
}
