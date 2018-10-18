#include<iostream>
#include<cstdio>
#include<cstring>
#define INF 0x3f3f3f3f
using namespace std;

int x[10010],y[10010];
int bottom[10010],top[10010];
int f[10010][1010];
int ord[10010];

int main()
{
	int n,m,k,pos;
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++) scanf("%d%d",x+i,y+i);
	for(int i=0;i<=n;i++) bottom[i]=0,top[i]=m+1;
	memset(ord,0,sizeof(ord));
	for(int i=1;i<=k;i++)
	{
		scanf("%d",&pos);
		scanf("%d%d",bottom+pos,top+pos);
		ord[pos]=i;
		//cout<<pos<<" "<<ord[pos]<<endl;
	}
	int cnt=0;
	for(int i=1;i<=n;i++)
		if(ord[i]!=0) ord[i]=++cnt;
	for(int i=1;i<=n;i++)
		for(int j=0;j<=m;j++)
			f[i][j]=INF;
	for(int j=0;j<=m;j++) f[0][j]=0;
	bottom[0]=-1;
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=m;j++)
		{
			if(j==m)
			{
				for(int k=max(bottom[i-1]+1,j-x[i]);k<top[i-1];k++) f[i][j]=min(f[i][j],f[i-1][k]+1);
				for(int k=max(bottom[i]+1,j-x[i]);k<top[i];k++) f[i][j]=min(f[i][j],f[i][k]+1);
			}
			if(j>x[i]) f[i][j]=min(f[i][j],f[i-1][j-x[i]]+1);
			if(j>x[i]) f[i][j]=min(f[i][j],f[i][j-x[i]]+1);
			//printf("dp(%d,%d)=%d\n",i,j,f[i][j]);
		}
		for(int j=bottom[i]+1;j<top[i];j++)
			if(j+y[i]>bottom[i-1]&&j+y[i]<top[i-1]) f[i][j]=min(f[i][j],f[i-1][j+y[i]]);
		for(int j=0;j<=bottom[i];j++) f[i][j]=INF;
		for(int j=top[i];j<=m;j++) f[i][j]=INF;
	}
	int ans=INF;
	for(int i=0;i<=m;i++) ans=min(ans,f[n][i]);
	if(ans!=INF)
	{
		printf("1\n%d\n",ans);
		return 0;
	}
	for(int i=n;i>=0;i--)
		if(top[i]<=m)
			for(int j=bottom[i]+1;j<top[i];j++)
				if(f[i][j]!=INF)
				{
					//cout<<i<<endl;
					printf("0\n%d\n",ord[i]);
					return 0;
				}
	printf("0\n0\n");
	return 0;
}
