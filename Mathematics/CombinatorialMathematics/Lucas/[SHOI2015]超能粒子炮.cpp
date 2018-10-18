#include<bits/stdc++.h>
#define ha 2333
using namespace std;

typedef long long LL;
int C[ha+10][ha+10],S[ha+10][ha+10];

int Lucas(LL n,LL m)
{
	if(n<m) return 0;
	if(n<ha&&m<ha) return C[n][m];
	return 1ll*Lucas(n/ha,m/ha)*C[n%ha][m%ha]%ha;
}

int gao(LL n,LL k)
{
	if(k<0) return 0;
	if(n<ha&&k<ha) return S[n][k];
	return (1ll*gao(n/ha,k/ha-1)*S[n%ha][ha-1]+1ll*Lucas(n/ha,k/ha)*S[n%ha][k%ha])%ha;
}

int main()
{
	for(int i=0;i<ha;i++) C[i][0]=S[0][i]=1;
	for(int i=1;i<ha;i++)
	{
		S[i][0]=1;
		for(int j=1;j<ha;j++)
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%ha,
			S[i][j]=(S[i][j-1]+C[i][j])%ha;
	}
	int T;LL n,k;
	for(scanf("%d",&T);T;T--)
	{
		scanf("%lld%lld",&n,&k);
		printf("%d\n",gao(n,k));
	}
	return 0;
}
