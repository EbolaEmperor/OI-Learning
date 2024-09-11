#include<bits/stdc++.h>
#define ha 1000000007
#define inv2 500000004
using namespace std;

const int S=(1<<20)+5;
char buf[S],*H,*T;
inline char Get()
{
    if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
    if(H==T) return -1;return *H++;
}
inline int read()
{
    int x=0;char c=Get();
    while(!isdigit(c)) c=Get();
    while(isdigit(c)) x=x*10+c-'0',c=Get();
    return x;
}

const int N=200010;
const int M=8000;
int fac[M+10],ifac[M+10];
int f[M/2+10][M/2+10],base=M/4+2;
int n,A[N],B[N];

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
    for(int i=1;i<=M;i++)
        fac[i]=1ll*fac[i-1]*i%ha;
    ifac[M]=Pow(fac[M],ha-2);
    for(int i=M-1;i>=0;i--)
        ifac[i]=1ll*ifac[i+1]*(i+1)%ha;
}

int C(int n,int m){return 1ll*fac[n]*ifac[m]%ha*ifac[n-m]%ha;}

int main()
{
    Init(); n=read();
    for(int i=1;i<=n;i++)
    {
        A[i]=read(),B[i]=read();
        f[base-A[i]][base-B[i]]++;
    }
    for(int i=1;i<=M/2+2;i++)
        for(int j=1;j<=M/2+2;j++)
            f[i][j]=(f[i][j]+(f[i-1][j]+f[i][j-1])%ha)%ha;
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        ans=(ans+f[A[i]+base][B[i]+base])%ha;
        ans=(ans-C(2*A[i]+2*B[i],2*A[i]))%ha;
    }
    ans=(ans+ha)%ha;
    ans=1ll*inv2*ans%ha;
    cout<<ans<<endl;
    return 0;
}