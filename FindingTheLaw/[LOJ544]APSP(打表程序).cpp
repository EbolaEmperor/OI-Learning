#include<bits/stdc++.h>
using namespace std;

const int N=1010;
char s[N];
int sa[N],rank[N],c[N];
int x[N],y[N],tmp[N];
int n=1,k;
map<int,bool> mp;

void get_sa(int n,int m)
{
	memset(c,0,sizeof(c));
	for(int i=1;i<=n;i++) c[x[i]=s[i]]++;
	for(int i=1;i<m;i++) c[i+1]+=c[i];
	for(int i=n;i>=1;i--) sa[c[x[i]]--]=i;
	for(int k=1;k<=n;k<<=1)
	{
		int num=0;
		for(int i=n-k+1;i<=n;i++) y[++num]=i;
		for(int i=1;i<=n;i++) if(sa[i]>k) y[++num]=sa[i]-k;
		for(int i=1;i<=m;i++) c[i]=0;
		for(int i=1;i<=n;i++) tmp[i]=x[y[i]];
		for(int i=1;i<=n;i++) c[tmp[i]]++;
		for(int i=1;i<m;i++) c[i+1]+=c[i];
		for(int i=n;i>=1;i--) sa[c[tmp[i]]--]=y[i];
		num=1;swap(x,y);x[sa[1]]=1;
		for(int i=2;i<=n;i++)
			x[sa[i]]=(y[sa[i]]!=y[sa[i-1]]||y[sa[i]+k]!=y[sa[i-1]+k])?++num:num;
		if(num==n) break;
		m=num;
	}
	for(int i=1;i<=n;i++) rank[sa[i]]=i;
}

void dfs(int p)
{
	if(p>n)
	{
		get_sa(n,k);
		int now=0;
		for(int i=1;i<=n;i++)
			now=now*10+rank[i];
		mp[now]=1;
		return;
	}
	for(int i=1;i<=k;i++)
		s[p]=i,dfs(p+1);
}

void check()
{
	static int per[15];
	for(int i=1;i<=n;i++) per[i]=i;
	do{
		int now=0;
		for(int i=1;i<=n;i++)
			now=now*10+per[i];
		if(!mp.count(now))
		{
			printf("%d\n",n);
			for(int i=1;i<=n;i++)
				printf("%d ",per[i]);
			exit(0);
		}
	}while(next_permutation(per+1,per+1+n));
}

int main()
{
	cin>>k;
	for(;"wzt AK IOI";n++)
	{
		mp.clear();
		dfs(1);
		check();
	}
	return 0;
}
