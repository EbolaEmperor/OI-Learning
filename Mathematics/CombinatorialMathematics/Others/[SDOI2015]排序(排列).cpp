#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
int n,a[5010],len;
LL ans=0;

LL fac(int n)
{
	LL res=1;
	for(LL i=2;i<=n;i++)
		res*=i;
	return res;
}

bool check(int l,int sz){return a[l+(sz/2)-1]+1==a[l+(sz/2)];}
void swap(int p1,int p2,int sz){for(int i=0;i<sz;i++) swap(a[p1+i],a[p2+i]);}

void dfs(int opt,int num)
{
	if(opt>n){ans+=fac(num);return;}
	int sz=(1<<opt),cnt=0;
	int p[5];
	for(int i=1;i<=len;i+=sz)
	{
		if(!check(i,sz)) p[++cnt]=i;
		if(cnt>2) return;
	}
	if(cnt==0) dfs(opt+1,num);
	if(cnt==1)
	{
		swap(p[1],p[1]+sz/2,sz/2);
		if(check(p[1],sz)) dfs(opt+1,num+1);
		swap(p[1],p[1]+sz/2,sz/2);
	}
	if(cnt==2)
	{
		swap(p[1],p[2],sz/2);
		if(check(p[1],sz)&&check(p[2],sz)) dfs(opt+1,num+1);
		swap(p[1],p[2],sz/2);
		swap(p[1],p[2]+sz/2,sz/2);
		if(check(p[1],sz)&&check(p[2],sz)) dfs(opt+1,num+1);
		swap(p[1],p[2]+sz/2,sz/2);
		swap(p[1]+sz/2,p[2],sz/2);
		if(check(p[1],sz)&&check(p[2],sz)) dfs(opt+1,num+1);
		swap(p[1]+sz/2,p[2],sz/2);
		swap(p[1]+sz/2,p[2]+sz/2,sz/2);
		if(check(p[1],sz)&&check(p[2],sz)) dfs(opt+1,num+1);
		swap(p[1]+sz/2,p[2]+sz/2,sz/2);
	}
}

int main()
{
	cin>>n;
	len=(1<<n);
	for(int i=1;i<=len;i++) scanf("%d",a+i);
	dfs(1,0);
	cout<<ans<<endl;
	return 0;
}
