#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int S=(1<<20)+5;
char buf[S],*H,*T;
inline char Get()
{
    if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
    if(H==T) return -1;return *H++;
}
template<typename I>inline void read(I &x)
{
    x=0;char c=Get();
    while(!isdigit(c)) c=Get();
    while(isdigit(c)) x=x*10+c-'0',c=Get();
}

const int N=10000000;
bool mark[N+10];
int prm[N/10],mu[N+10];
int tot=0;

void Init()
{
    for(int i=2;i<=N;i++)
    {
        if(!mark[i]) prm[++tot]=i,mu[i]=-1;
        for(int j=1;j<=tot&&i*prm[j]<=N;j++)
        {
            mark[i*prm[j]]=1;
            if(i%prm[j]) mu[i*prm[j]]=-mu[i];
            else{mu[i*prm[j]]=0;break;}
        }
    }
}

bool check(LL n)
{
    if(n>=2&&n<=4||n==6||n==14) return 1;
    if(n<=14||n&1) return 0;
    n>>=1;
    if(n<=N) return !mark[n]&&mu[n-1];
    for(int i=1;i<=tot&&1ll*prm[i]*prm[i]<=n;i++)
        if(n%prm[i]==0||(n-1)%(1ll*prm[i]*prm[i])==0) return 0;
    return 1;
}

int main()
{
    int T,k;LL n;Init();
    for(read(T);T;T--)
    {
        read(k);read(n);
        if(k==1) puts(n&1?"YES":"NO");
        if(k==2) puts(n<=2?"YES":"NO");
        if(k==3) puts(check(n)?"YES":"NO");
    }
    return 0;
}