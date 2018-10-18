#include<bits/stdc++.h>
using namespace std;

const int N=1010;
int prm[N],tot=0;
bool mark[N];
int st[N],mx[N];
int f[2][2060];

inline void upmax(int &x,const int &y){if(y>x) x=y;}
inline void upmin(int &x,const int &y){if(y<x) x=y;}

void Init()
{
	for(int i=2;i<=1000;i++)
	{
		if(!mark[i])
		{
			prm[++tot]=i;
			mark[i]=1;mx[i]=i;
			if(i<=31) st[i]=1<<(tot-1);
		}
		for(int j=1;j<=tot&&i*prm[j]<=1000;j++)
		{
			mark[i*prm[j]]=1;
			mx[i*prm[j]]=mx[i];
			st[i*prm[j]]=st[i];
			upmax(mx[i*prm[j]],prm[j]);
			if(prm[j]<=31) st[i*prm[j]]|=1<<(j-1);
			if(i%prm[j]==0) break;
		}
	}
}

int main()
{
	Init();
	int T,n,K;
	scanf("%d",&T);
	for(int cas=1;cas<=T;cas++)
	{
		scanf("%d%d",&n,&K);
		memset(f,0x3f,sizeof(f));
		f[0][0]=0;
		int p=1;
		while(prm[p]<=n) p++;p--;
		int ans=(p>11)?p-11:0;
		upmin(p,11);
		int k=1;
		for(int i=1;i<=n;i++)
		{
			for(int s=0;s<(1<<p);s++)
			{
				f[k][s]=f[k^1][s];
				if((st[i]&s)==st[i]&&i!=K)
					upmin(f[k][s],f[k^1][s^st[i]]+1-(mx[i]>31));
			}
			memset(f[k^1],0x3f,sizeof(f[k^1]));
			f[k^1][0]=0;k^=1;
		}
		printf("Case #%d: %d\n",cas,f[k^1][(1<<p)-1]+ans+(K!=1));
	}
	return 0;
}
