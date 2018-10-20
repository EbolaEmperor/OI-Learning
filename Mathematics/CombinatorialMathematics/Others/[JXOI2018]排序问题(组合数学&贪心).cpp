#include<bits/stdc++.h>
using namespace std;

namespace IO
{
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
    char obuf[S],*oS=obuf,*oT=oS+S-1,c,qu[55];int qr;
    inline void flush(){fwrite(obuf,1,oS-obuf,stdout);oS=obuf;}
    inline void putc(char x){*oS++ =x;if(oS==oT) flush();}
    template <class I>inline void print(I x)
    {
        if(!x) putc('0');
        if(x<0) putc('-'),x=-x;
        while(x) qu[++qr]=x%10+'0',x/=10;
        while(qr) putc(qu[qr--]);
    }
}

using namespace IO;
const int N=200010;
const int M=10200010;
const int ha=998244353;
int n,m,l,r,cnt[N],sum[N];
int a[N],Hash[N],hs;
int fac[M],ifac[M];

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
}

void Init(int n)
{
    fac[0]=1;
    for(int i=1;i<=n;i++)
        fac[i]=1ll*fac[i-1]*i%ha;
    ifac[n]=Pow(fac[n],ha-2);
    for(int i=n-1;i>=0;i--)
        ifac[i]=1ll*ifac[i+1]*(i+1)%ha;
}

int main()
{
    Init(10200000);
    for(int T_T=read();T_T;T_T--)
    {
        n=read();m=read();l=read();r=read();
        memset(cnt,0,sizeof(int)*(n+5));
        memset(sum,0,sizeof(int)*(n+5));
        int all=fac[n+m],rest=r-l+1,ans=1;
        for(int i=1;i<=n;i++) Hash[i]=a[i]=read();
        sort(Hash+1,Hash+1+n);
        hs=unique(Hash+1,Hash+1+n)-(Hash+1);
        for(int i=1;i<=hs;i++) rest-=(Hash[i]>=l&&Hash[i]<=r);
        for(int i=1;i<=n;i++)
        {
            a[i]=lower_bound(Hash+1,Hash+1+hs,a[i])-Hash;
            if(Hash[a[i]]>=l&&Hash[a[i]]<=r) cnt[a[i]]++;
            sum[a[i]]++;ans=1ll*ans*sum[a[i]]%ha;
        }
        sort(cnt+1,cnt+1+hs);int zero=0;
        for(int i=1;i<=hs;i++) if(cnt[i]==0) zero=i;
        for(int i=1;i<=hs-zero;i++) cnt[i]=cnt[i+zero]%ha;
        n=hs-zero;
        for(int i=0;i<n;i++)
        {
            if(cnt[i+1]==cnt[i]) continue;
            if(1ll*(cnt[i+1]-cnt[i])*(i+rest)<=m)
            {
                m-=(cnt[i+1]-cnt[i])*(i+rest);
                int x=1ll*fac[cnt[i+1]]*ifac[cnt[i]]%ha;
                ans=1ll*ans*Pow(x,i+rest)%ha;
            }
            else
            {
                int x=m/(i+rest);
                int t=1ll*fac[cnt[i]+x]*ifac[cnt[i]]%ha;
                ans=1ll*ans*Pow(t,i+rest)%ha;
                ans=1ll*ans*Pow(cnt[i]+x+1,m%(i+rest))%ha;
                m=0;break;
            }
        }
        if(m>0)
        {
            int x=m/(r-l+1);
            int t=1ll*fac[cnt[n]+x]*ifac[cnt[n]]%ha;
            ans=1ll*ans*Pow(t,r-l+1)%ha;
            ans=1ll*ans*Pow(cnt[n]+x+1,m%(r-l+1))%ha;
        }
        ans=1ll*all*Pow(ans,ha-2)%ha;
        print(ans);putc('\n');
    }
    flush();
    return 0;
}