#include<bits/stdc++.h>
#define ha 924844033
using namespace std;

const int N=4010;
bool vis[N][2];
int f[N][N][2],ed[N],g[N];
int fac[N];

int main()
{
	int tot=0,n,k;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		for(int j=0;j<2;j++)
		{
			int cnt=0;
			if(vis[i][j]) continue;
			for(int x=i,y=0;x<=n;x+=k,y^=1)
				vis[x][y]=1,cnt++;
			ed[tot+=cnt]=1;
		}
	f[1][0][0]=1;
	for(int i=1;i<=n*2;i++)
		for(int j=0;j<n;j++)
		{
			f[i+1][j][0]=(f[i][j][0]+f[i][j][1])%ha;
			if(!ed[i]) f[i+1][j+1][1]=f[i][j][0];
		}
	for(int i=0;i<=n;i++) g[i]=(f[n*2][i][0]+f[n*2][i][1])%ha;
	fac[0]=1;for(int i=1;i<=n;i++) fac[i]=1ll*fac[i-1]*i%ha;
	int ans=0,fg=1;
	for(int i=0;i<=n;i++,fg=-fg)
		ans=(ans+1ll*fg*g[i]*fac[n-i])%ha;
	printf("%d\n",(ans+ha)%ha);
	return 0;
}
