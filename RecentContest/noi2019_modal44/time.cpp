#include<bits/stdc++.h>
using namespace std;

const int ha=998244353;
const int N=110;
int E[N][N],fac[N],S[N][N],inv[N],n,m;

int main()
{
    scanf("%d%d",&n,&m);
    fac[0]=1;
    for(int i=1;i<=m;i++)
        fac[i]=1ll*fac[i-1]*i%ha;
    S[0][0]=1;
    for(int i=1;i<=m;i++)
        for(int j=1;j<=i;j++)
            S[i][j]=(S[i-1][j-1]+1ll*j*S[i-1][j])%ha;
    inv[1]=1;
    for(int i=2;i<=n;i++)
        inv[i]=1ll*(ha-ha/i)*inv[ha%i]%ha;
    E[n][0]=E[n][1]=1;
    for(int i=n-1;i>=0;i--)
    {
        E[i][0]=1;
        for(int j=1;j<=m+1;j++)
        {
            int s1=1ll*i*inv[n]%ha*E[i][j-1]%ha;
            int s2=1ll*(n-i)*inv[n]%ha*(E[i+1][j]+E[i+1][j-1])%ha;
            E[i][j]=1ll*n*inv[n-i]%ha*(s1+s2)%ha;
        }
    }
    int ans=0;
    for(int k=1;k<=m;k++)
        ans=(ans+1ll*S[m][k]*fac[k]%ha*E[0][k+1])%ha;
    if(!m) ans=(ans+E[0][1]-1)%ha;
    printf("%d\n",ans);
    return 0;
}