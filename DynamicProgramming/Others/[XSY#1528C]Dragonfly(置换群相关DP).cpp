#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int ha=998244353;
const int N=1010;
int fac[N],ifac[N],inv[N];
int pw[N],ipw[N],gd[N],ft[N],m;
int f[N],g[N],h[N],d[N];

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=(LL)a*a%ha)
        if(b&1) ans=(LL)ans*a%ha;
    return ans;
}

void Init(int n)
{
    fac[0]=1;
    for(int i=1;i<=n;i++)
        fac[i]=(LL)fac[i-1]*i%ha;
    ifac[n]=Pow(fac[n],ha-2);
    for(int i=n-1;i>=0;i--)
        ifac[i]=(LL)ifac[i+1]*(i+1)%ha;
    for(int i=1;i<=n;i++)
        inv[i]=(LL)fac[i-1]*ifac[i]%ha;
}

inline int C(int n,int m){return (LL)fac[n]*ifac[m]%ha*ifac[n-m]%ha;}

int gao(int n,LL A)
{
    memset(g,0,sizeof(g));g[0]=1;m=0;
    for(int i=1;i<=n;i++) if(A%i==0) ft[++m]=i;
    for(int i=1;i<=n;i++)
    {
        int x=n/i;
        memset(f,0,sizeof(f));f[0]=pw[0]=1;
        for(int j=1;j<=x;j++) pw[j]=(LL)pw[j-1]*i%ha;
        for(int k=1;k<=m&&ft[k]<=x;k++)
        {
            gd[k]=(__gcd((LL)i,A/ft[k])==1);
            if(gd[k]) h[k]=(LL)fac[ft[k]-1]*pw[ft[k]-1]%ha;
        }
        for(int j=1;j<=x;j++)
            for(int k=1;k<=m&&ft[k]<=j;k++)
                if(gd[k]) f[j]=(f[j]+(LL)f[j-ft[k]]*C(j-1,ft[k]-1)%ha*h[k])%ha;
        memset(d,0,sizeof(d));
        d[0]=1;d[1]=i&1;
        for(int j=2;j<=x;j++)
            d[j]=((i&1)*d[j-1]+(LL)d[j-2]*(j-1)%ha*i)%ha;
        ipw[0]=1;
        for(int j=1;j<=x;j++) ipw[j]=(LL)ipw[j-1]*inv[i]%ha;
        for(int j=0;j<=x;j++) ipw[j]=(LL)ipw[j]*fac[j*i]%ha*ifac[j]%ha;
        for(int j=0;j<=x;j++) f[j]=(LL)f[j]*d[j]%ha*ipw[j]%ha;
        for(int j=n;j>=0;j--)
            for(int k=1;k<=j/i;k++)
                g[j]=(g[j]+(LL)C(j,i*k)*g[j-k*i]%ha*f[k])%ha;
    }
    return g[n];
}

int main()
{
    Init(1000);
    int T;scanf("%d",&T);
    while(T--)
    {
        int n;LL a,b,c;
        cin>>n>>a>>b>>c;
        if(!(a|b|c))
        {
            f[0]=f[1]=1;
            for(int i=2;i<=n;i++)
                f[i]=(f[i-1]+(LL)f[i-2]*(i-1))%ha;
            cout<<(LL)Pow(n,n)*f[n]%ha<<endl;
        }
        else cout<<gao(n,abs(a+c-b))<<endl;
    }
    return 0;
}