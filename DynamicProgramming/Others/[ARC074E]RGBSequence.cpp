#include<bits/stdc++.h>
#define ha 1000000007
using namespace std;

int n,m;
struct Inteval{int l,x,next;} e[310];
int h[310],sum=0;
int f[310][310][310];

inline void Add(int &x,const int &y){x=(x+y>=ha)?(x+y-ha):(x+y);}

void add_inteval(int l,int r,int x)
{
	e[++sum].l=l;
	e[sum].x=x;
	e[sum].next=h[r];
	h[r]=sum;
}

int main()
{
	int l,r,x;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&l,&r,&x);
		add_inteval(l,r,x);
	}
	f[1][0][0]=1;
	for(int t=h[1];t;t=e[t].next)
		for(int j=0;j<=1;j++)
			for(int k=0;k<=1;k++)
			{
				int cnt=1;
				cnt+=(j>=e[t].l);
				cnt+=(k>=e[t].l);
				if(cnt!=e[t].x) f[1][j][k]=0;
			}
	for(int i=1;i<n;i++)
	{
		for(int j=0;j<i;j++)
			for(int k=0;k<i;k++)
			{
				if(j||k)
				{
					Add(f[i+1][i][k],f[i][j][k]);
					Add(f[i+1][j][i],f[i][j][k]);
				}
				else Add(f[i+1][i][0],f[i][j][k]);
				Add(f[i+1][j][k],f[i][j][k]);
			}
		for(int t=h[i+1];t;t=e[t].next)
		{
			for(int j=0;j<=i;j++)
				for(int k=0;k<=i;k++)
				{
					int cnt=1;
					cnt+=(j>=e[t].l);
					cnt+=(k>=e[t].l);
					if(cnt!=e[t].x) f[i+1][j][k]=0;
				}
		}
	}
	int ans=3ll*f[n][0][0]%ha;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			if(i||j) Add(ans,6ll*f[n][i][j]%ha);
	printf("%d\n",ans);
	return 0;
}
