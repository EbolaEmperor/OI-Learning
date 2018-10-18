#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int N=6000000;
int prime[N],tot=0;
LL phi[N+10],u[N+10];
bool mark[N+10];
map<int,LL> su,sphi;

void Init()
{
	memset(mark,0,sizeof(mark));
	phi[1]=u[1]=1;
	for(int i=2;i<=N;i++)
	{
		if(!mark[i]) prime[++tot]=i,phi[i]=i-1,u[i]=-1;
		for(int j=1;j<=tot&&i*prime[j]<=N;j++)
		{
			mark[i*prime[j]]=1;
			if(i%prime[j]) phi[i*prime[j]]=(prime[j]-1)*phi[i],u[i*prime[j]]=-u[i];
			else{phi[i*prime[j]]=prime[j]*phi[i],u[i*prime[j]]=0;break;}
		}
	}
	for(int i=1;i<=N;i++) phi[i]+=phi[i-1],u[i]+=u[i-1];
}

void Sphi_Su(LL n,LL &ans1,LL &ans2)
{
	if(n<=N){ans1=phi[n];ans2=u[n];return;}
	if(sphi.count(n)){ans1=sphi[n];ans2=su[n];return;};
	ans1=n*(n+1)/2;ans2=1;LL div;
	for(LL i=2;i<=n;i=div+1)
	{
		div=n/(n/i);
		LL tmp1,tmp2;
		Sphi_Su(n/i,tmp1,tmp2);
		ans1-=(div-i+1)*tmp1;
		ans2-=(div-i+1)*tmp2;
	}
	sphi[n]=ans1;su[n]=ans2;
}

int main()
{
	Init();
	int T;LL n,ans1,ans2;
	for(cin>>T;T;T--)
	{
		cin>>n;
		Sphi_Su(n,ans1,ans2);
		cout<<ans1<<" "<<ans2<<endl;
	}
	return 0;
}
