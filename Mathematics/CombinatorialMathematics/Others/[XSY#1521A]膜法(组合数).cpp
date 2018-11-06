#include<bits/stdc++.h>
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

const int ha=1e9+7;
const int N=100010;
int fac[N],ifac[N];

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
}

void prework(int n)
{
    fac[0]=1;
    for(int i=1;i<=n;i++)
        fac[i]=1ll*fac[i-1]*i%ha;
    ifac[n]=Pow(fac[n],ha-2);
    for(int i=n-1;i>=0;i--)
        ifac[i]=1ll*ifac[i+1]*(i+1)%ha;
}

inline int C(int n,int m){return 1ll*fac[n]*ifac[m]%ha*ifac[n-m]%ha;}

int main()
{
    int n,m,l,r,k,ans=1;
    n=read();m=read();
    prework(n+1);
    for(int i=1;i<=m;i++)
    {
        l=read();r=read();k=read();
        int res=(C(r+1,l-k+1)-C(l,l-k+1)+ha)%ha;
        ans=1ll*ans*res%ha;
    }
    printf("%d\n",ans);
    return 0;
}