#include<bits/stdc++.h>
#define Mod 1000000007
using namespace std;

typedef long long LL;
struct LIM{int x,y;} lim[100010];

bool operator < (const LIM &a,const LIM &b){return a.x<b.x||(a.x==b.x&&a.y<b.y);}
bool operator == (const LIM &a,const LIM &b){return a.x==b.x&&a.y==b.y;}

LL QuickMul(LL a,LL b)
{
	a%=Mod;b%=Mod;
	LL ans=0;
	while(b)
	{
		if(b&1) ans=(ans+a)%Mod;
		a=(a+a)%Mod;
		b>>=1;
	}
	return ans;
}

LL QuickPow(LL a,LL b)
{
	LL ans=1;
	while(b)
	{
		if(b&1) ans=QuickMul(ans,a);
		a=QuickMul(a,a);
		b>>=1;
	}
	return ans;
}

int main()
{
	LL n;int m,k;
	scanf("%lld%d%d",&n,&m,&k);
	LL sum=n*(n+1)/2;
	for(int i=1;i<=k;i++) scanf("%d%d",&lim[i].x,&lim[i].y);
	sort(lim+1,lim+1+k);
	k=unique(lim+1,lim+1+k)-(lim+1);
	lim[k+1].x=lim[k+1].y=0;
	LL cnt=m,res=sum,ans=1;
	for(int i=1;i<=k;i++)
	{
		res-=lim[i].y;
		if(lim[i].x!=lim[i+1].x)
		{
			cnt--;
			ans=QuickMul(ans,res);
			res=sum;
		}
	}
	ans=QuickMul(ans,QuickPow(sum,cnt));
	cout<<ans<<endl;
	return 0;
}
