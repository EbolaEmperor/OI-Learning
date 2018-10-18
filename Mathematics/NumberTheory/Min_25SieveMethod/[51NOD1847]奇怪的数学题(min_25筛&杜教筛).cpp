#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef unsigned int uint;
const int N=1000000;
bool mark[N+10];
int prime[N/10],tot=0;
uint phi[N+10];
uint n,k,qn;
uint stl[60][60],s[60];
uint f1[N+10],f2[N+10];
uint g1[N+10],g2[N+10];
uint ans1[N+10],ans2[N+10];
map<uint,uint> sp;

void Init1()
{
	phi[1]=1;
	for(int i=2;i<=N;i++)
	{
		if(!mark[i]) prime[++tot]=i,phi[i]=i-1;
		for(int j=1;j<=tot&&i*prime[j]<=N;j++)
		{
			mark[i*prime[j]]=1;
			if(i%prime[j]) phi[i*prime[j]]=phi[i]*(prime[j]-1);
			else{phi[i*prime[j]]=phi[i]*prime[j];break;}
		}
	}
	for(int i=1;i<=N;i++) phi[i]+=phi[i-1];
}

void Init2()
{
	stl[0][0]=1;
	for(int i=1;i<=k;i++)
		for(int j=1;j<=i;j++)
			stl[i][j]=stl[i-1][j-1]-(i-1)*stl[i-1][j];
}

uint GetS(LL x)
{
	s[0]=x;
	for(int i=1;i<=k;i++)
	{
		s[i]=1;
		LL t=(x+1)/(i+1)*(i+1);
		s[i]*=(x+1)/(i+1);
		for(LL j=x+1;j>=x-i+1;j--)
			if(j!=t) s[i]*=j;
		for(int j=0;j<i;j++)
			s[i]-=stl[i][j]*s[j];
	}
	return s[k];
}

uint Sphi(uint n)
{
	if(n<=N) return phi[n];
	if(sp.count(n)) return sp[n];
	uint div,res=1ll*n*(n+1)/2;
	for(int i=2;i<=n;i=div+1)
	{
		div=n/(n/i);
		res-=Sphi(n/i)*(div-i+1);
	}
	sp[n]=res;
	return res;
}

uint Pow(uint a,uint b)
{
	uint ans=1;
	for(;b;b>>=1,a*=a)
		if(b&1) ans*=a;
	return ans;
}

void Init3()
{
	for(int i=1;i<=qn;i++) f1[i]=GetS(i)-1,g1[i]=i-1;
	for(int i=1;n/i>qn;i++) f2[i]=GetS(n/i)-1,g2[i]=n/i-1;
	for(int i=1;i<=tot;i++)
	{
		int j,t=Pow(prime[i],k),p=prime[i];
		for(j=1;n/p/j>qn&&n/j>=1ll*p*p;j++)
		{
			ans2[j]+=f2[p*j]-f1[p-1];
			f2[j]-=t*(f2[p*j]-f1[p-1]);
			g2[j]-=g2[p*j]-g1[p-1];
		}
		for(;n/j>qn&&n/j>=1ll*p*p;j++)
		{
			ans2[j]+=f1[n/p/j]-f1[p-1];
			f2[j]-=t*(f1[n/p/j]-f1[p-1]);
			g2[j]-=g1[n/p/j]-g1[p-1];
		}
		for(int j=qn;j>=2&&j>=1ll*p*p;j--)
		{
			ans1[j]+=f1[j/p]-f1[p-1];
			f1[j]-=t*(f1[j/p]-f1[p-1]);
			g1[j]-=g1[j/p]-g1[p-1];
		}
	}
	for(int i=1;i<=qn;i++) ans1[i]+=g1[i];
	for(int i=1;n/i>qn;i++) ans2[i]+=g2[i];
}

uint GetF(LL x){return x<=qn?ans1[x]:ans2[n/x];}

uint Getsqrt(uint n)
{
	uint tmp=sqrt(n);
	for(uint i=max((int)tmp-3,0);i<=tmp+3;i++)
		if(i*i>n) return i-1;
}

int main()
{
	scanf("%u%u",&n,&k);
	qn=Getsqrt(n);
	Init1();Init2();Init3();
	uint ans=0,div;
	for(uint i=1;i<=n;i=div+1)
	{
		div=n/(n/i);
		ans+=(GetF(div)-GetF(i-1))*(2*Sphi(n/i)-1);
	}
	printf("%u\n",ans);
	return 0;
}
