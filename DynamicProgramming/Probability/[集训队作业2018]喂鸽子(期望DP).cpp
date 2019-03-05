#include<bits/stdc++.h>
using namespace std;

const int ha=998244353;
const int N=50010;
int fac[N],ifac[N],inv[N];
int P[N][55],E[N][55];
int n,k;

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
}

void init(int n=50000)
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
int C(int n,int m){return 1ll*fac[n]*ifac[m]%ha*ifac[n-m]%ha;}

int main()
{
    init();
    cin>>n>>k;
    P[0][0]=1;
    for(int i=0;i<=n*k;i++)
        for(int j=0;j<=n;j++)
        {
            int psb=1ll*P[i][j]*inv[n-j]%ha;
            int e=(1ll*E[i][j]*inv[n-j]+1ll*n*inv[n-j]%ha*psb)%ha;
            P[i+1][j]=(P[i+1][j]+psb)%ha;
            E[i+1][j]=(E[i+1][j]+e)%ha;
            if(i+1>=(j+1)*k)
            {
                P[i+1][j+1]=(P[i+1][j+1]+1ll*psb*C(i-j*k,k-1))%ha;
                E[i+1][j+1]=(E[i+1][j+1]+1ll*e*C(i-j*k,k-1))%ha;
            }
        }
    int ans=1ll*E[n*k][n]*fac[n]%ha;
    printf("%d\n",ans);
    return 0;
}