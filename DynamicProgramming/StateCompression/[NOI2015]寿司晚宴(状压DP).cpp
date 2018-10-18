#include<bits/stdc++.h>
#define pii pair<int,int>
#define rest first
#define state second
using namespace std;

const int N=510;
int f[N][N],g[2][N][N],n,p;
int prm[8]={2,3,5,7,11,13,17,19};
pii num[N];

inline void add(int &x,const int &y){x=(x+y>=p)?(x+y-p):(x+y);}

inline void gao(int x)
{
	int id=x-2;
	for(int i=0;i<8;i++)
		while(x%prm[i]==0)
			x/=prm[i],num[id].state|=(1<<i);
	num[id].rest=x;
}

int main()
{
	scanf("%d%d",&n,&p);
	add(f[0][0],1);
	int mx=(1<<8)-1;
	for(int i=2;i<=n;i++) gao(i);
	sort(num,num+n-1);
	for(int i=0;i<n-1;i++)
	{
		if(i==0||num[i].rest==1||num[i].rest!=num[i-1].first)
			memcpy(g[0],f,sizeof(f)),memcpy(g[1],f,sizeof(f));
		for(int j=mx;j>=0;j--)
			for(int k=mx;k>=0;k--)
				add(g[1][j][k|num[i].state],g[1][j][k]),
				add(g[0][j|num[i].state][k],g[0][j][k]);
		if(i==n-2||num[i].rest==1||num[i].rest!=num[i+1].first)
			for(int j=0;j<=mx;j++)
				for(int k=0;k<=mx;k++)
				{
					f[j][k]=g[0][j][k]+g[1][j][k]-f[j][k];
					if(f[j][k]>=p) f[j][k]-=p;
					else if(f[j][k]<0) f[j][k]+=p;
				}
	}
	int ans=0;
	for(int i=0;i<=mx;i++)
		for(int j=0;j<=mx;j++)
			if(!(i&j)) add(ans,f[i][j]);
	printf("%d\n",ans);
	return 0;
}
