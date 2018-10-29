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

typedef long long LL;
const int ha=998244353;
const int N=100010;
LL cnt[N],n,A,ans=0;

int main()
{
    n=read();A=read();
    for(int i=1;i<=n;i++) cnt[read()]++;
    for(LL i=1;i*i<=A;i++)
        for(LL j=1;j<=i;j++)
        {
            LL x=i*i-j*j,z=i*i+j*j,y=2ll*i*j;
            if(z>A) break;
            if(__gcd(__gcd(x,y),z)>1) continue;
            for(int a=x,b=y,c=z;c<=A;a+=x,b+=y,c+=z)
                ans=(ans+cnt[a]*cnt[b]*cnt[c])%ha;
        }
    printf("%lld\n",ans);
    return 0;
}