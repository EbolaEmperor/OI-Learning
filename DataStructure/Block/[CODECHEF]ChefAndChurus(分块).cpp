#include<bits/stdc++.h>
#define lowbit(x) (x&-x)
using namespace std;

typedef unsigned long long ULL;
const int M=350,N=100010;
int cnt[M][N],block,tot=0;
int n,a[N],L[N],R[N];
ULL bit[N];
ULL sum[M];

void Add(int p,int x){for(;p<=n;p+=lowbit(p)) bit[p]+=x;}
ULL Sum(int p){ULL res=0;for(;p;p-=lowbit(p)) res+=bit[p];return res;}

void Modify(int p,int x)
{
	Add(p,x-a[p]);
	for(int i=1;i<=tot;i++)
		sum[i]+=1ull*(x-a[p])*cnt[i][p];
	a[p]=x;
}

ULL Query(int l,int r)
{
	int lb=(l-1)/block+1,rb=(r-1)/block+1;
	ULL ans=0;
	if(lb==rb)
		for(int i=l;i<=r;i++)
			ans+=Sum(R[i])-Sum(L[i]-1);
	else
	{
		for(int i=lb+1;i<rb;i++) ans+=sum[i];
		for(int i=l;i<=lb*block;i++) ans+=Sum(R[i])-Sum(L[i]-1);
		for(int i=(rb-1)*block+1;i<=r;i++) ans+=Sum(R[i])-Sum(L[i]-1);
	}
	return ans;
}

int main()
{
	scanf("%d",&n);
	block=ceil(sqrt(n));
	for(int i=1;i<=n;i++)
	{
		scanf("%d",a+i);
		Add(i,a[i]);
	}
	for(int i=1;i<=n;i++)
		scanf("%d%d",L+i,R+i);
	for(int i=1;i<=n;i++)
	{
		if(i%block==1) tot++;
		cnt[tot][L[i]]++;
		cnt[tot][R[i]+1]--;
		sum[tot]+=Sum(R[i])-Sum(L[i]-1);
	}
	for(int i=1;i<=tot;i++)
		for(int j=1;j<=n;j++)
			cnt[i][j]+=cnt[i][j-1];
	int Q,opt,x,y;
	for(scanf("%d",&Q);Q;Q--)
	{
		scanf("%d%d%d",&opt,&x,&y);
		if(opt==1) Modify(x,y);
		else printf("%llu\n",Query(x,y));
	}
	return 0;
}
