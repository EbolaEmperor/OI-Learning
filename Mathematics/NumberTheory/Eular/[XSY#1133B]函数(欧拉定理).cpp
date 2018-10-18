#include<bits/stdc++.h>
using namespace std;

typedef long long LL;

int Pow(int a,LL b,int p)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%p)
        if(b&1) ans=1ll*ans*a%p;
    return ans;
}

int getphi(int x)
{
    int res=x;
    for(int i=2;i*i<=x;i++)
    {
        if(x%i==0) res-=res/i;
        while(x%i==0) x/=i;
    }
    if(x>1) res-=res/x;
    return res;
}

int facpow(LL x,int p)
{
    if(p==1) return 0;
    if(x==3) return 16%p;
    if(x==4) return 65536%p;
    int phi=getphi(p);
    return Pow(2,facpow(x-1,phi)+phi,p);
}

int gao(LL m,LL n,LL p)
{
    if(m==0) return (n+1)%p;
    if(m==1) return (n+2)%p;
    if(m==2) return (2ll*(n%p)+3)%p;
    if(m==3) return (Pow(2,n+3,p)-3)%p;
    if(m==4) return (facpow(n+3,p)-3)%p;
    if(m==5&&n==0) return (facpow(4,p)-3)%p;
    return (facpow(0,p)-3)%p;
}

int main()
{
    int T,p;LL n,m;
    for(scanf("%d",&T);T;T--)
    {
        scanf("%lld%lld%d",&m,&n,&p);
        printf("%d\n",(gao(m,n,p)%p+p)%p);
    }
    return 0;
}