#include<bits/stdc++.h>
using namespace std;

int read()
{
	int x=0;char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) x=x*10+c-'0',c=getchar();
	return x;
}

const int N=10000010;
int a[1010],n,m;
int ch[N][2],tot=0;
int root[300010];
int cnt[N];
int lgo[1010],rgo[1010];

void insert(int o,int pre,int x)
{
	for(int i=30;i>=0;i--)
	{
		cnt[o]=cnt[pre]+1;
		int j=(x>>i)&1;
		ch[o][j]=++tot;
		ch[o][j^1]=ch[pre][j^1];
		o=ch[o][j];
		pre=ch[pre][j];
	}
	cnt[o]=cnt[pre]+1;
}

int Query(int l,int r,int L,int R,int k)
{
	int ans=0;
	for(int i=l;i<=r;i++) lgo[i]=L,rgo[i]=R;
	for(int bit=30;bit>=0;bit--)
	{
		int num=0;
		for(int i=l;i<=r;i++)
		{
			int j=((a[i]>>bit)&1)^1;
			num+=cnt[ch[rgo[i]][j]]-cnt[ch[lgo[i]][j]];
		}
		if(num>=k)
		{
			ans|=1<<bit;
			for(int i=l;i<=r;i++)
			{
				int j=((a[i]>>bit)&1)^1;
				rgo[i]=ch[rgo[i]][j];
				lgo[i]=ch[lgo[i]][j];
			}
		}
		else
		{
			k-=num;
			for(int i=l;i<=r;i++)
			{
				int j=(a[i]>>bit)&1;
				rgo[i]=ch[rgo[i]][j];
				lgo[i]=ch[lgo[i]][j];
			}
		}
	}
	return ans;
}

int main()
{
	n=read();m=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=m;i++)
	{
		root[i]=++tot;
		insert(root[i],root[i-1],read());
	}
	int Q=read(),u,d,l,r,k;
	while(Q--)
	{
		u=read();d=read();l=read();r=read();k=read();
		printf("%d\n",Query(u,d,root[l-1],root[r],k));
	}
	return 0;
}
