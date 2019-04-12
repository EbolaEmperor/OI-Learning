#include<bits/stdc++.h>
using namespace std;

const int ha=1e9+7,N=10000010;
int fac[N],ifac[N],inv[N];
int n,ans=0;

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
}

void init()
{
    fac[0]=1;
    for(int i=1;i<=n;i++)
        fac[i]=1ll*fac[i-1]*i%ha;
    ifac[n]=Pow(fac[n],ha-2);
    for(int i=n-1;i>=0;i--)
        ifac[i]=1ll*ifac[i+1]*(i+1)%ha;
    inv[1]=1;
    for(int i=2;i<=n;i++)
        inv[i]=1ll*(ha-ha/i)*inv[ha%i]%ha;
}

int C(int n,int m){return (n>=m&&m>=0)?1ll*fac[n]*ifac[m]%ha*ifac[n-m]%ha:0;}
int iC(int n,int m){return (n>=m&&m>=0)?1ll*ifac[n]*fac[m]%ha*fac[n-m]%ha:0;}

int main()
{
    cin>>n;init();
    for(int i=0;i<n;i++)
        ans=(ans+1ll*(1-1ll*C(i,n-i)*iC(n-1,i-1)%ha+ha)*n%ha*inv[n-i])%ha;
    cout<<ans<<endl;
    return 0;
}
