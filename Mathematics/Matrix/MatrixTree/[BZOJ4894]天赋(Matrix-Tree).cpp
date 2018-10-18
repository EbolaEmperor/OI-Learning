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

int Det(int A[310][310],int n)
{
	int ans=1;
	for(int i=2;i<=n;i++)
	{
		int pos=i;
		while(pos<=n&&!A[pos][i]) pos++;
		if(!A[pos][i]) return 0;
		if(pos!=i)
		{
			ans=-ans;
			for(int j=2;j<=n;j++)
				swap(A[i][j],A[pos][j]);
		}
		ans=1ll*ans*A[i][i]%ha;
		int inv=Pow(A[i][i],ha-2);
		for(int j=i+1;j<=n;j++)
		{
			int t=1ll*A[j][i]*inv%ha;
			for(int k=2;k<=n;k++)
				A[j][k]=(A[j][k]-1ll*A[i][k]*t%ha+ha)%ha;
		}
	}
	return (ans+ha)%ha;
}

int G[310][310];

int main()
{
	int n;
	static char s[310];
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s+1);
		for(int j=1;j<=n;j++)
			if(s[j]=='1') G[i][j]--,G[j][j]++;
	}
	printf("%d\n",Det(G,n));
	return 0;
}
