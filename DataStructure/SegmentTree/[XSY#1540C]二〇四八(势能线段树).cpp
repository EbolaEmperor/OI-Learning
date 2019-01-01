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
        while(x) qu[++qr]=x%10+'0',x/=10;
        while(qr) putc(qu[qr--]);
    }
}

using namespace IO;
typedef long long LL;
typedef pair<int,int> pii;
struct QRY{int l,r,id;};
const int N=200010;
LL mn[N<<2],mx[N<<2],sum[N<<2],tag[N<<2];
vector<int> a[N];
vector<QRY> qry[N];
int n,m,q,cnt,now;
LL ans[N],val[N];
pii b[N];

inline void modify(int o,int l,int r,LL x)
{
    tag[o]=mn[o]=mx[o]=x;
    sum[o]=x*(r-l+1);
}

inline void maintain(int o)
{
    mn[o]=min(mn[o<<1],mn[o<<1|1]);
    mx[o]=max(mx[o<<1],mx[o<<1|1]);
    sum[o]=sum[o<<1]+sum[o<<1|1];
}

inline void pushdown(int o,int l,int r)
{
    if(tag[o]==-1) return;
    int mid=(l+r)/2;
    modify(o<<1,l,mid,tag[o]);
    modify(o<<1|1,mid+1,r,tag[o]);
    tag[o]=-1;
}

void build(int o,int l,int r)
{
    tag[o]=-1;
    if(l==r){mx[o]=mn[o]=n+2;return;}
    int mid=(l+r)/2;
    build(o<<1,l,mid);
    build(o<<1|1,mid+1,r);
    maintain(o);
}

void update(int o,int l,int r,int nl,int nr,LL x)
{
    if(mx[o]<=x) return;
    if(l>=nl&&r<=nr&&mn[o]>=x)
    {
        modify(o,l,r,x);
        return;
    }
    int mid=(l+r)/2;pushdown(o,l,r);
    if(nl<=mid) update(o<<1,l,mid,nl,nr,x);
    if(nr>mid) update(o<<1|1,mid+1,r,nl,nr,x);
    maintain(o);
}

LL query(int o,int l,int r,int nl,int nr,LL x)
{
    if(l>=nl&&r<=nr)
    {
        if(mn[o]>x+1) return 0;
        if(mx[o]<=x+1) return (x+2)*(r-l+1)-sum[o];
    }
    pushdown(o,l,r);
    int mid=(l+r)/2;LL res=0;
    if(nl<=mid) res+=query(o<<1,l,mid,nl,nr,x);
    if(nr>mid) res+=query(o<<1|1,mid+1,r,nl,nr,x);
    return res;
}

void jump(int o,int l,int r)
{
    if(mn[o]==mx[o])
    {
        b[++cnt]=pii(l,r);
        val[cnt]=mn[o];
        while(mn[o]<b[now].first) now++;
        modify(o,l,r,val[now]);
        return;
    }
    pushdown(o,l,r);
    int mid=(l+r)/2;
    jump(o<<1|1,mid+1,r);
    jump(o<<1,l,mid);
    maintain(o);
}

int main()
{
    n=read();m=read();q=read();
    for(int i=1;i<=n;i++) a[read()].push_back(i);
    for(int i=1,k,l,r;i<=q;i++)
    {
        l=read();r=read();k=read();
        qry[k].push_back({l,r,i});
    }
    build(1,1,n+2);
    for(int i=1;i<=m;i++)
    {
        cnt=0;now=1;jump(1,1,n+2);
        for(int p : a[i]) update(1,1,n+2,1,p,p+1);
        for(QRY p : qry[i]) ans[p.id]=query(1,1,n+2,p.l,p.r,p.r);
    }
    for(int i=1;i<=q;i++)
        print(ans[i]),putc('\n');
    return flush(),0;
}