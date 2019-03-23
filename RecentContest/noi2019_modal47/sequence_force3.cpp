// O(n^2)
#include<bits/stdc++.h>
using namespace std;

const int ha=998244353;
const int N=2010;
int n,p[N],prod[N][N];
int f[N][N],g[N][N],P[N][N];
// P[i][j]: ai=j的概率
// f[i][j]: 当ai=j时，前缀和的期望
// g[i][j]: 当ai=j时，前缀和平方的期望

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
}

int main()
{
    scanf("%d",&n);
    int i100=Pow(100,ha-2);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",p+i);
        p[i]=1ll*p[i]*i100%ha;
        prod[i][1]=p[i];
        for(int j=1;j<=i;j++)
            prod[i][j+1]=1ll*prod[i][j]*p[i-j]%ha;
    }
    P[0][0]=1;
    for(int i=1;i<=n;i++)
    {
        for(int j=0;j<=i-1;j++)
        {
            P[i][0]=(P[i][0]+1ll*P[i-1][j]*(1-p[i]+ha))%ha;
            f[i][0]=(f[i][0]+1ll*f[i-1][j]*(1-p[i]+ha))%ha;
            g[i][0]=(g[i][0]+1ll*g[i-1][j]*(1-p[i]+ha))%ha;
        }
        for(int j=1;j<=i;j++)
        {
            int pb=prod[i][j],s=(j+1)*j/2,s2=1ll*s*s%ha;
            P[i][j]=(P[i][j]+1ll*P[i-j][0]*pb)%ha;
            f[i][j]=(f[i][j]+1ll*f[i-j][0]*pb+1ll*s*P[i-j][0]%ha*pb)%ha;
            g[i][j]=(g[i][j]+1ll*g[i-j][0]*pb+2ll*f[i-j][0]*s%ha*pb+1ll*s2*P[i-j][0]%ha*pb)%ha;
        }
    }
    int ans=0;
    for(int i=0;i<=n;i++)
        ans=(ans+g[n][i])%ha;
    printf("%d\n",ans);
    return 0;
}