#include<bits/stdc++.h>
using namespace std;

int QuickPow(int a,int b,const int &p)
{
	int ans=1;
	while(b)
	{
		if(b&1) ans=1ll*ans*a%p;
		a=1ll*a*a%p;
		b>>=1;
	}
	return ans;
}

int GetPhi(int n)
{
	int res=n;
	for(int i=2;i*i<=n;i++)
	{
		if(n%i==0) res-=res/i;
		while(n%i==0) n/=i;
	}
	if(n>1) res-=res/n;
	return res;
}

int F(int p)
{
	if(p==1) return 0;
	int phi=GetPhi(p);
	return QuickPow(2,F(phi)+phi,p);
}

int main()
{
	int T,p;
	for(cin>>T;T;T--)
	{
		scanf("%d",&p);
		printf("%d\n",F(p));
	}
	return 0;
}
