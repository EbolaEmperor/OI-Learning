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
    template<class I> inline void read(I &x)
    {
        x=0;char c=Get();
        while(!isdigit(c)) c=Get();
        while(isdigit(c)) x=x*10+c-'0',c=Get();
    }
    char obuf[S],*oS=obuf,*oT=oS+S-1,c,qu[55];int qr;
    inline void flush(){fwrite(obuf,1,oS-obuf,stdout);oS=obuf;}
    inline void putc(char x){*oS++ =x;if(oS==oT) flush();}
    template<class I> inline void print(I x)
    {
        if(!x) putc('0');
        while(x) qu[++qr]=x%10+'0',x/=10;
        while(qr) putc(qu[qr--]);
        putc('\n');
    }
}

using namespace IO;
typedef unsigned long long ULL;
const int N=100010,ha=19961993;
ULL fact[N<<2];
int prod[N<<2];
int n=100000,m,leaf,tot=0;
bool mark[310];
int prm[65],ctr[N];

int Pow(int a,int b)
{
    int ans=1;
    for(;b;b>>=1,a=1ll*a*a%ha)
        if(b&1) ans=1ll*ans*a%ha;
    return ans;
}

void Init()
{
    mark[0]=mark[1]=1;
    for(int i=2;i<=300;i++)
    {
        if(!mark[i]) prm[++tot]=i;else continue;
        for(int j=i+i;j<=300;j+=i) mark[j]=1;
    }
    for(int i=1;i<=60;i++)
    {
        ctr[i]=1-Pow(prm[i],ha-2);
        if(ctr[i]<0) ctr[i]+=ha;
    }
}

ULL factorize(ULL x)
{
    ULL res=0;
    for(int i=1;i<=60;i++)
        if(x%prm[i]==0) res|=1ull<<i-1;
    return res;
}

int getphi(int n,ULL fac)
{
    for(int i=1;fac&&i<=60;i++,fac>>=1) 
        if(fac&1ull) n=1ll*n*ctr[i]%ha;
    return n;
}

void Maintain(int o)
{
    fact[o]=fact[o<<1]|fact[o<<1|1];
    prod[o]=1ll*prod[o<<1]*prod[o<<1|1]%ha;
}

void Build()
{
    for(leaf=1;leaf<=n+2;leaf<<=1);
    for(int i=0;i<=(leaf<<1);i++) fact[i]=0,prod[i]=1;
    for(int i=leaf+1;i<=leaf+n;i++) fact[i]=2ull,prod[i]=3;
    for(int i=leaf-1;i;i--) Maintain(i);
}

int Query(int l,int r)
{
    int res1=1;ULL res2=0;
    for(l=leaf+l-1,r=leaf+r+1;l^r^1;l>>=1,r>>=1)
    {
        if(~l&1) res1=1ll*res1*prod[l^1]%ha,res2|=fact[l^1];
        if(r&1) res1=1ll*res1*prod[r^1]%ha,res2|=fact[r^1];
    }
    return getphi(res1,res2);
}

void Modify(int k,ULL x)
{
    prod[leaf+k]=x%ha;
    fact[leaf+k]=factorize(x);
    for(int i=(leaf+k)>>1;i;i>>=1) Maintain(i);
}

int main()
{
    int opt,x,y;ULL c;
    Init();Build();
    for(read(m);m;m--)
    {
        read(opt);
        if(opt==0) read(x),read(y),print(Query(x,y));
        if(opt==1) read(x),read(c),Modify(x,c);
    }
    flush();
    return 0;
}