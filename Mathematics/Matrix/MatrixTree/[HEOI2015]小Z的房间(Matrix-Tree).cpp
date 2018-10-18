#include<bits/stdc++.h>
#define ha 1000000000
using namespace std;

int Gauss(int (*A)[100],int n)
{
	int res=1;
	for(int i=1;i<n;i++)
		for(int j=i+1;j<n;j++)
			while(A[j][i])
			{
				int t=A[i][i]/A[j][i];res=-res;
				for(int k=1;k<n;k++)
				{
					int tmp=(A[i][k]-1ll*A[j][k]*t%ha+ha)%ha;
					A[i][k]=A[j][k];A[j][k]=tmp;
				}
			}
	for(int i=1;i<n;i++) res=1ll*res*A[i][i]%ha;
	return (res+ha)%ha;
}

int mp[11][11],G[100][100];
void add_edge(int u,int v){G[u][v]--;G[v][v]++;}

int main()
{
	int n,m,tot=0;
	static char s[15];
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
	{
		scanf("%s",s+1);
		for(int j=1;j<=m;j++)
			if(s[j]=='.') mp[i][j]=++tot;
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
		{
			if(!mp[i][j]) continue;
			if(mp[i][j+1]) add_edge(mp[i][j],mp[i][j+1]);
			if(mp[i][j-1]) add_edge(mp[i][j],mp[i][j-1]);
			if(mp[i+1][j]) add_edge(mp[i][j],mp[i+1][j]);
			if(mp[i-1][j]) add_edge(mp[i][j],mp[i-1][j]);
		}
	printf("%d\n",Gauss(G,tot));
	return 0;
}
