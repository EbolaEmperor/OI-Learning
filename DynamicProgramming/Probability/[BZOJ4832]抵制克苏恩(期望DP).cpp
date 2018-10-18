#include<bits/stdc++.h>
using namespace std;

double f[55][8][8][8][8],g[55][8][8][8][8];

int main()
{
	int T,K,A,B,C;
	for(scanf("%d",&T);T;T--)
	{
		scanf("%d%d%d%d",&K,&A,&B,&C);
		memset(f,0,sizeof(f));
		memset(g,0,sizeof(g));
		f[0][A+B+C][A][B][C]=1.0;
		for(int i=0;i<K;i++)
			for(int j=0;j<=7;j++)
				for(int a=0;a<=j;a++)
					for(int b=0;b<=j-a;b++)
					{
						int c=j-a-b;double p=1.0/(1.0+j);
						f[i+1][j][a][b][c]+=f[i][j][a][b][c]*p;
						g[i+1][j][a][b][c]+=(g[i][j][a][b][c]+f[i][j][a][b][c])*p;
						if(a) f[i+1][j-1][a-1][b][c]+=f[i][j][a][b][c]*p*a,g[i+1][j-1][a-1][b][c]+=g[i][j][a][b][c]*p*a;
						if(b)
						{
							if(j<7) f[i+1][j+1][a+1][b-1][c+1]+=f[i][j][a][b][c]*p*b,g[i+1][j+1][a+1][b-1][c+1]+=g[i][j][a][b][c]*p*b;
							else f[i+1][j][a+1][b-1][c]+=f[i][j][a][b][c]*p*b,g[i+1][j][a+1][b-1][c]+=g[i][j][a][b][c]*p*b;
						}
						if(c)
						{
							if(j<7) f[i+1][j+1][a][b+1][c]+=f[i][j][a][b][c]*p*c,g[i+1][j+1][a][b+1][c]+=g[i][j][a][b][c]*p*c;
							else f[i+1][j][a][b+1][c-1]+=f[i][j][a][b][c]*p*c,g[i+1][j][a][b+1][c-1]+=g[i][j][a][b][c]*p*c;
						}
					}
		double ans=0.0;
		for(int i=0;i<=7;i++)
			for(int a=0;a<=i;a++)
				for(int b=0;b<=i-a;b++)
				{
					int c=i-a-b;
					ans+=g[K][i][a][b][c];
				}
		printf("%.2lf\n",ans);
	}
	return 0;
}
