#include<bits/stdc++.h>
using namespace std;

const int ha=1e9+7;
const int N=10000010,M=3010;
int n,m,b[M],fac[N],ifac[N],f[N],p[M];
bool can[M];

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
}
int C(int n,int m){return (n>=m)?1ll*fac[n]*ifac[m]%ha*ifac[n-m]%ha:0;}

int main()
{
    scanf("%d%d",&n,&m);init();
    for(int i=1;i<=m;i++) scanf("%d",b+i);
    int ans=0;
    f[0]=f[1]=1;
    for(int i=2;i<=n;i++)
        f[i]=(1ll*(i-1)*f[i-2]+f[i-1])%ha;
    for(int i=0;i<=m;i++)
    {
        can[b[i]]=1;
        for(int j=1,k=0;j<=i;j++)
        {
            k++;
            while(!can[k]) k++;
            p[k]=b[j];
        }
        bool flag=1;
        for(int j=1;j<=m;j++)
            if(can[j]&&p[p[j]]!=j) flag=0;
        if(flag) ans=(ans+1ll*C(n-m,m-i)*f[n-m-(m-i)])%ha;
    }
    cout<<ans<<endl;
    return 0;
}