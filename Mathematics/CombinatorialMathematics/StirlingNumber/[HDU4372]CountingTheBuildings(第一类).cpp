#include<bits/stdc++.h>
#define Mod 1000000007
using namespace std;

const int N=2000;
int C[N+10][N+10];
int S[N+10][N+10];

void Init()
{
	S[0][0]=1;
	for(int i=0;i<=N;i++)
	{
		C[i][0]=1;
		for(int j=1;j<=i;j++)
		{
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%Mod;
			S[i][j]=(1ll*(i-1)*S[i-1][j]+S[i-1][j-1])%Mod;
		}
	}
}

int main()
{
	int T,n,f,b;
	Init();
	for(cin>>T;T;T--)
	{
		scanf("%d%d%d",&n,&f,&b);
		int ans=1ll*C[f+b-2][f-1]*S[n-1][f+b-2]%Mod;
		printf("%d\n",ans);
	}
	return 0;
}
