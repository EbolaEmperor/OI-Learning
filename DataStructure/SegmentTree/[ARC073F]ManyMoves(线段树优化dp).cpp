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
const int N=200010;
int n,q,a,b,X[N];
int delta[N];
LL sumd[N],f[N];

struct SegmentTree
{
    LL mnv[N<<2];int leaf;
    void build()
    {
        for(leaf=1;leaf<=(n+2);leaf<<=1);
        for(int i=1;i<=leaf+n;i++) mnv[i]=INT64_MAX/3;
    }
    void modify(int k,LL x)
    {
        mnv[leaf+k]=min(mnv[leaf+k],x);
        for(int i=(leaf+k)>>1;i;i>>=1)
            mnv[i]=min(mnv[i<<1],mnv[i<<1|1]);
    }
    LL qmin(int l,int r)
    {
        LL res=INT64_MAX/3;
        for(l=leaf+l-1,r=leaf+r+1;l^r^1;l>>=1,r>>=1)
        {
            if(~l&1) res=min(res,mnv[l^1]);
            if(r&1) res=min(res,mnv[r^1]);
        }
        return res;
    }
}t1,t2;

LL solve(int a,int b)
{
    X[0]=a;
    for(int i=1;i<=q;i++)
    {
        delta[i]=abs(X[i]-X[i-1]);
        sumd[i]=sumd[i-1]+delta[i];
    }
    f[1]=abs(b-X[1]);
    t1.build();t2.build();
    t1.modify(X[0],f[1]-sumd[1]-X[0]);
    t2.modify(X[0],f[1]-sumd[1]+X[0]);
    for(int i=2;i<=q;i++)
    {
        f[i]=t1.qmin(1,X[i])+X[i]+sumd[i-1];
        f[i]=min(f[i],t2.qmin(X[i],n)-X[i]+sumd[i-1]);
        t1.modify(X[i-1],f[i]-sumd[i]-X[i-1]);
        t2.modify(X[i-1],f[i]-sumd[i]+X[i-1]);
    }
    LL ans=INT64_MAX/3;
    for(int i=0;i<=q;i++) ans=min(ans,f[i]+sumd[q]-sumd[i]);
    return ans;
}

int main()
{
    n=read();q=read();a=read();b=read();
    for(int i=1;i<=q;i++) X[i]=read();
    LL ans=min(solve(a,b),solve(b,a));
    printf("%lld\n",ans);
    return 0;
}