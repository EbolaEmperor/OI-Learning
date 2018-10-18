#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef long double LD;
const int N=8000000;
int phi[N+10];
int prime[N],tot=0;
bool mark[N+10];
LL f[N+10];
LL inv2,inv6;
map<LL,LL> sf;
LL Mod;

LL inv(LL a)
{
	LL b=Mod-2,ans=1;
	while(b)
	{
		if(b&1) ans=ans*a%Mod;
		a=a*a%Mod;
		b>>=1;
	}
	return ans;
}

void Init()
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
	for(int i=1;i<=N;i++) f[i]=(f[i-1]+1ll*i*i%Mod*phi[i]%Mod)%Mod;
}

LL Mul(LL x,LL y)  
{  
	LL tmp=(x*y-(LL)((LD)x/Mod*y+1.0e-8)*Mod);  
	return tmp<0?(tmp+Mod):tmp;  
}

LL Sum(LL n){return Mul(Mul(n,n+1ll),inv2);}
LL Sum2(LL n){return Mul(Mul(Mul(n,n+1ll),2ll*n+1),inv6);}  

LL Sf(LL n)
{
	if(n<=N) return f[n];
	if(sf.count(n)) return sf[n];
	LL res=Sum(n),div,tmp;
	res=Mul(res,res);
	for(LL i=2;i<=n;i=div+1)
	{
		div=n/(n/i);
		tmp=Sum2(div)-Sum2(i-1);
		res-=Mul(tmp,Sf(n/i));
		if(res<0) res+=Mod;
	}
	return sf[n]=res;
}

int main()
{
	LL n,div,ans=0,sum,tmp;
	cin>>Mod>>n;Init();
	inv2=inv(2);inv6=inv(6);
	for(LL i=1;i<=n;i=div+1)
	{
		div=n/(n/i);
		sum=Sum(n/i);
		sum=Mul(sum,sum);
		tmp=Sf(div)-Sf(i-1);
		if(tmp<0) tmp+=Mod;
		if(tmp>=Mod) tmp-=Mod;
		ans=(ans+Mul(sum,tmp))%Mod;
	}
	cout<<ans<<endl;
	return 0;
}
