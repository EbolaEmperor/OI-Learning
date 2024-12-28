#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;

int f[4000];
int mainw[4000],mainc[4000];
int followw[4000][2],followc[4000][2];
int follown[4000];
bool ismain[4000];

int main()
{
	int x,y,z;
	memset(ismain,0,sizeof(ismain));
	memset(f,0,sizeof(f));
	memset(follown,0,sizeof(follown));
	int n,m;
	cin>>n>>m;
	n/=10;
	for(int i=1;i<=m;i++)
	{
		scanf("%d%d%d",&x,&y,&z);
		if(z==0) mainw[i]=x/10,mainc[i]=x*y/10,ismain[i]=1;
		else followw[z][follown[z]]=x/10,followc[z][follown[z]++]=x*y/10;
	}
	for(int i=1;i<=m;i++)
		if(ismain[i])
			for(int T=n;T>=mainw[i];T--)
				{
					if(T>=mainw[i]) f[T]=max(f[T],f[T-mainw[i]]+mainc[i]);
					for(int j=0;j<follown[i];j++)
						if(T-mainw[i]-followw[i][j]>=0)
							f[T]=max(f[T],f[T-mainw[i]-followw[i][j]]+mainc[i]+followc[i][j]);
					if(follown[i]==2&&T-mainw[i]-followw[i][0]-followw[i][1]>=0)
						f[T]=max(f[T],f[T-mainw[i]-followw[i][0]-followw[i][1]]+mainc[i]+followc[i][0]+followc[i][1]);
				}
	int ans=0;
	for(int T=0;T<=n;T++)
		if(f[T]>ans) ans=f[T];
	cout<<(ans*10)<<endl;
	return 0;
}
