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
        int x=0,fg=1;char c=Get();
        while(!isdigit(c)&&c!='-') c=Get();
        if(c=='-') fg=-1,c=Get();
        while(isdigit(c)) x=x*10+c-'0',c=Get();
        return x*fg;
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
        putc('\n');
    }
}

using namespace IO;
typedef long long LL;
const int N=100010;
int mn[N<<2],mx[N<<2],tag[N<<2];
LL sum[N<<2];int a[N],n;

void Maintain(int o)
{
    mn[o]=min(mn[o<<1],mn[o<<1|1]);
    mx[o]=max(mx[o<<1],mx[o<<1|1]);
    sum[o]=sum[o<<1]+sum[o<<1|1];
}

void Pushdown(int o,int l,int r)
{
    if(!tag[o]) return;
    mn[o<<1]+=tag[o];
    mn[o<<1|1]+=tag[o];
    mx[o<<1]+=tag[o];
    mx[o<<1|1]+=tag[o];
    int mid=(l+r)/2;
    sum[o<<1]+=1ll*tag[o]*(mid-l+1);
    sum[o<<1|1]+=1ll*tag[o]*(r-mid);
    tag[o<<1]+=tag[o];
    tag[o<<1|1]+=tag[o];
    tag[o]=0;
}

void Build(int o,int l,int r)
{
    if(l==r)
    {
        sum[o]=mn[o]=mx[o]=a[l];
        return;
    }
    int mid=(l+r)/2;
    Build(o<<1,l,mid);
    Build(o<<1|1,mid+1,r);
    Maintain(o);
}

void Add(int o,int l,int r,int nl,int nr,int x)
{
    if(l>=nl&&r<=nr)
    {
        sum[o]+=1ll*x*(r-l+1);
        tag[o]+=x;mn[o]+=x;mx[o]+=x;
        return;
    }
    Pushdown(o,l,r);
    int mid=(l+r)/2;
    if(nl<=mid) Add(o<<1,l,mid,nl,nr,x);
    if(nr>mid) Add(o<<1|1,mid+1,r,nl,nr,x);
    Maintain(o);
}

inline int D(int x,int y){return floor((double)x/y);}
void Div(int o,int l,int r,int nl,int nr,int x)
{
    if(l>=nl&&r<=nr&&mn[o]-D(mn[o],x)==mx[o]-D(mx[o],x))
    {
        assert(mx[o] - mn[o] <= 1);
        int dev=mn[o]-D(mn[o],x);
        sum[o]-=1ll*dev*(r-l+1);
        tag[o]-=dev;mn[o]-=dev;mx[o]-=dev;
        return;
    }
    Pushdown(o,l,r);
    int mid=(l+r)/2;
    if(nl<=mid) Div(o<<1,l,mid,nl,nr,x);
    if(nr>mid) Div(o<<1|1,mid+1,r,nl,nr,x);
    Maintain(o);
}

int Min(int o,int l,int r,int nl,int nr)
{
    if(l>=nl&&r<=nr) return mn[o];
    Pushdown(o,l,r);
    int mid=(l+r)/2,res=INT_MAX;
    if(nl<=mid) res=min(res,Min(o<<1,l,mid,nl,nr));
    if(nr>mid) res=min(res,Min(o<<1|1,mid+1,r,nl,nr));
    return res;
}

LL Sum(int o,int l,int r,int nl,int nr)
{
    if(l>=nl&&r<=nr) return sum[o];
    Pushdown(o,l,r);
    int mid=(l+r)/2;LL res=0;
    if(nl<=mid) res+=Sum(o<<1,l,mid,nl,nr);
    if(nr>mid) res+=Sum(o<<1|1,mid+1,r,nl,nr);
    return res;
}

int main()
{
    n=read();int Q=read();
    for(int i=1;i<=n;i++) a[i]=read();
    Build(1,1,n);
    while(Q--)
    {
        int opt=read(),l=read()+1,r=read()+1;
        int c=(opt<=2)?read():0;
        if(opt==1) Add(1,1,n,l,r,c);
        if(opt==2) Div(1,1,n,l,r,c);
        if(opt==3) print(Min(1,1,n,l,r));
        if(opt==4) print(Sum(1,1,n,l,r));
    }
    flush();
    return 0;
}