#include<bits/stdc++.h>
using namespace std;

const int ha=998244353;
const int N=2010;
int n,a[4],ans=0;
int C[N][N],fac[N],ifac[N];

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
}

void init()
{
    for(int i=0;i<=n;i++)
        for(int j=C[i][0]=1;j<=i;j++)
            C[i][j]=(C[i-1][j-1]+C[i-1][j])%ha;
    fac[0]=1;
    for(int i=1;i<=n;i++)
        fac[i]=1ll*fac[i-1]*i%ha;
    ifac[n]=Pow(fac[n],ha-2);
    for(int i=n-1;i>=0;i--)
        ifac[i]=1ll*ifac[i+1]*(i+1)%ha;
}

int gao(int x)
{
    int m=n-4*x;
    static int f[4][N],b[4];
    for(int i=0;i<4;i++)
    {
        b[i]=a[i]-x;
        memset(f[i],0,sizeof(f[i]));
        for(int j=0;j<=min(b[i],m);j++)
            f[i][j]=ifac[j];
    }
    for(int k=0;k<3;k++)
    {
        static int g[N];
        memset(g,0,sizeof(g));
        for(int i=0;i<=m;i++)
            for(int j=0;j<=m;j++)
                g[i+j]=(g[i+j]+1ll*f[k][i]*f[k+1][j])%ha;
        memcpy(f[k+1],g,sizeof(g));
    }
    return 1ll*fac[m]*f[3][m]%ha;
}

int main()
{
    cin>>n>>a[0]>>a[1]>>a[2]>>a[3];
    sort(a,a+4);init();
    for(int i=0;i<=min(a[0],n/4);i++)
    {
        int tmp=1ll*C[n-3*i][i]*gao(i)%ha;
        if(i&1) tmp=ha-tmp;
        ans=(ans+tmp)%ha;
    }
    cout<<ans<<endl;
    return 0;
}