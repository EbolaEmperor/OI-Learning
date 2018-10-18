#include<bits/stdc++.h>
#define ha 1000000007
using namespace std;

const int N=300;
int fac[N+10],ifac[N+10];
int f[N+10][N+10];
int facn[N+10],facm[N+10];
int pw[N+10];

int Pow(int a,int b)
{
    int ans=1;
    if(b<0) return 0;
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
    f[0][0]=1;
    for(int i=1;i<=N;i++)
        for(int j=i;j<=min(N,i<<1);j++)
            f[i][j]=(2ll*f[i-1][j-1]+(j>=2?f[i-1][j-2]:0))%ha;
}

inline int Cn(int x){return 1ll*facn[x]*ifac[x]%ha;}
inline int Cm(int x){return 1ll*facm[x]*ifac[x]%ha;}

int main()
{
    Init();
    int T,n,m,k;
    for(scanf("%d",&T);T;T--)
    {
        scanf("%d%d%d",&n,&m,&k);
        facn[0]=1;facn[1]=n-m;
        for(int i=2;i<=k;i++)
            facn[i]=1ll*facn[i-1]*(n-m-i+1)%ha;
        facm[0]=1;facm[1]=m;
        for(int i=2;i<=k;i++)
            facm[i]=1ll*facm[i-1]*(m-i+1)%ha;
        for(int i=0;i<=k;i++) pw[i]=Pow(2,m-i);
        int ans=0;
        for(int i=0;i<=k;i++)
        {
            int res=0;
            for(int j=(k-i)/2;j<=k-i;j++)
                res=(res+1ll*Cm(j)*pw[j]%ha*f[j][k-i])%ha;
            ans=(ans+1ll*res*Cn(i))%ha;
        }
        printf("%d\n",ans);
    }
    return 0;
}