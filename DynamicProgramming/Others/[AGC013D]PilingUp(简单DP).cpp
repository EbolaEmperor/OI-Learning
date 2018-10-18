#include<bits/stdc++.h>
#define ha 1000000007
using namespace std;

const int N=3010;
int f[N][N][2];

void Add(int &x,const int &y){x=(x+y>=ha)?(x+y-ha):(x+y);}

int main()
{
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) f[1][i][0]=1;
	f[1][0][1]=1;
	for(int i=1;i<=m;i++)
		for(int j=0;j<=n;j++)
		{
			if(j>=1)
			{
				Add(f[i+1][j-1][1],f[i][j][1]);
				if(j==1) Add(f[i+1][j-1][1],f[i][j][0]);
				else Add(f[i+1][j-1][0],f[i][j][0]);
			}
			if(j<n)
			{
				Add(f[i+1][j+1][1],f[i][j][1]);
				Add(f[i+1][j+1][0],f[i][j][0]);
			}
			if(j>=1)
			{
				Add(f[i+1][j][1],f[i][j][1]);
				if(j==1) Add(f[i+1][j][1],f[i][j][0]);
				else Add(f[i+1][j][0],f[i][j][0]);
			}
			if(j<n)
			{
				Add(f[i+1][j][1],f[i][j][1]);
				Add(f[i+1][j][0],f[i][j][0]);
			}
		}
	int ans=0;
	for(int i=0;i<=n;i++) Add(ans,f[m+1][i][1]);
	printf("%d\n",ans);
	return 0;
}
