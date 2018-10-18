#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
LL f[15],s[15];

vector<LL> dp(LL x)
{
	vector<LL> ans(10,0);
	LL w=x;int tot=0;
	static int num[15];
	while(w) num[++tot]=w%10,w/=10;
	for(int i=tot;i>0;i--)
	{
		for(int j=0;j<10;j++) ans[j]+=f[i-1]*num[i];
		for(int j=0;j<num[i];j++) ans[j]+=s[i-1];
		LL t=0;for(int j=i-1;j>0;j--) t=t*10+num[j];
		ans[num[i]]+=t+1;ans[0]-=s[i-1];
	}
	return ans;
}

int main()
{
	LL a,b;cin>>a>>b;s[0]=1;
	for(int i=1;i<=12;i++)
		f[i]=f[i-1]*10+s[i-1],s[i]=s[i-1]*10;
	vector<LL> ans1=dp(a-1),ans2=dp(b);
	for(int i=0;i<10;i++) printf("%lld ",ans2[i]-ans1[i]);
	return 0;
}
