#include<bits/stdc++.h>
using namespace std;

inline void upmax(short &x,const short &y){if(y>x) x=y;}

const int N=105;
short f[N][N][N][N];
short sum1[N][N],sum2[N][N];
int n,m,tx,ty;

void gao()
{
	int limu=tx-1,limd=n-tx,liml=ty-1,limr=m-ty;
	for(int u=0;u<=limu;u++)
		for(int d=0;d<=limd;d++)
			for(int l=0;l<=liml;l++)
				for(int r=0;r<=limr;r++)
				{
					int L=max(ty-l,r+1),R=min(ty+r,m-l);
					if(L<=R)
					{
						upmax(f[u+1][d][l][r],f[u][d][l][r]+(tx-u-1>=d+1?sum1[tx-u-1][R]-sum1[tx-u-1][L-1]:0));
						upmax(f[u][d+1][l][r],f[u][d][l][r]+(tx+d+1<=n-u?sum1[tx+d+1][R]-sum1[tx+d+1][L-1]:0));
					}
					L=max(tx-u,d+1),R=min(tx+d,n-u);
					if(L<=R)
					{
						upmax(f[u][d][l+1][r],f[u][d][l][r]+(ty-l-1>=r+1?sum2[R][ty-l-1]-sum2[L-1][ty-l-1]:0));
						upmax(f[u][d][l][r+1],f[u][d][l][r]+(ty+r+1<=m-l?sum2[R][ty+r+1]-sum2[L-1][ty+r+1]:0));
					}
				}
	printf("%d\n",f[limu][limd][liml][limr]);
}

int main()
{
	static char s[105];
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s+1);
		for(int j=1;j<=m;j++)
		{
			if(s[j]=='E') tx=i,ty=j;
			sum1[i][j]=sum1[i][j-1]+(s[j]=='o');
			sum2[i][j]=sum2[i-1][j]+(s[j]=='o');
		}
	}
	gao();
	return 0;
}
