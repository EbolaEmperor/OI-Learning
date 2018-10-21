#include<bits/stdc++.h>
using namespace std;

const int ha=998244353;
const int N=1000000;
int fac[N+5],ifac[N+5];

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
}

void Init()
{
    fac[0]=1;
    for(int i=1;i<=N;i++)
        fac[i]=1ll*fac[i-1]*i%ha;
    ifac[N]=Pow(fac[N],ha-2);
    for(int i=N-1;i>=0;i--)
        ifac[i]=1ll*ifac[i+1]*(i+1)%ha;
}

inline int C(const int &n,const int &m){return 1ll*fac[n]*ifac[m]%ha*ifac[n-m]%ha;}
inline int invC(const int &n,const int &m){return 1ll*ifac[n]*fac[m]%ha*fac[n-m]%ha;}

int main()
{
    int n,m;Init();
    cin>>n>>m;
    int t=min(n,m),ans=0;
    for(int i=1;i<=t;i++)
        ans=(ans+1ll*C(2*i,i)*C(n+m-2*i,n-i))%ha;
    ans=1ll*ans*invC(n+m,n)%ha*ifac[2]%ha;
    printf("%d\n",(ans+max(n,m))%ha);
    return 0;
}