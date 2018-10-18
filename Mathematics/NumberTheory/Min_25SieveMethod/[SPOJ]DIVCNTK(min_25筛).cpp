#include<bits/stdc++.h>
using namespace std;

typedef unsigned long long ULL;
typedef long long LL;
const int N=1000000;
bool mark[N+10];
int prime[N],tot=0;
LL s1[N+10],s2[N+10];
ULL g1[N+10],g2[N+10];
ULL qn,n,k;

LL GetS(LL x){return x<=qn?s1[x]:s2[n/x];}
ULL GetG(LL x){return x<=qn?g1[x]:g2[n/x];}

void InitP()
{
	for(int i=2;i<=N;i++)
	{
		if(!mark[i]) prime[++tot]=i;
		for(int j=1;j<=tot&&i*prime[j]<=N;j++)
		{
			mark[i*prime[j]]=1;
			if(i%prime[j]==0) break;
		}
	}
}

void InitG()
{
	//cout<<"here"<<endl;
	for(int i=1;i<=qn;i++) s1[i]=i-1,s2[i]=n/i-1;
	for(int j=1;j<=tot&&prime[j]<=qn;j++)
	{
		//cout<<j<<endl;
		LL p=prime[j];
		for(LL i=1;i<=qn&&n/i>=p*p;i++) s2[i]-=GetS(n/(i*p))-GetS(p-1);
		for(LL i=qn;i>=1&&i>=p*p;i--) s1[i]-=GetS(i/p)-GetS(p-1);
	}
	for(int i=2;i<=qn;i++) g1[i]=(ULL)s1[i]*(k+1);
	for(int i=1;i<=n/(qn+1);i++) g2[i]=(ULL)s2[i]*(k+1);
}

ULL getsqrt(ULL x)
{
	ULL tmp=sqrt(x);
	for(ULL i=max((LL)tmp-3,0ll);i<=tmp+3;i++)
		if(i*i>x) return i-1;
}

ULL GetAns(LL i,int jj)
{
	//cout<<i<<endl;
	LL p=prime[jj];
	if(i<=1||i<p) return 0;
	ULL ans=GetG(i)-GetG(p-1);
	if(i<p*p) return ans;
	LL tmp;
	for(int j=jj;j<=tot&&1ll*prime[j]*prime[j]<=i;j++)
	{
		tmp=i/prime[j];
		for(int q=1;tmp>=prime[j];tmp/=prime[j],q++)
			ans+=1ull*GetAns(tmp,j+1)*(q*k+1)+((q+1)*k+1);
	}
	return ans;
}

int main()
{
	InitP();
	scanf("%llu%llu",&n,&k);
	qn=getsqrt(n);
	InitG();
	printf("%llu\n",GetAns(n,1)+1);
	return 0;
}
