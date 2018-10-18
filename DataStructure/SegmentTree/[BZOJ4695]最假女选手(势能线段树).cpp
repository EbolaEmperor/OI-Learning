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
const int N=500010;
int mn[N<<2],cmn[N<<2],mns[N<<2];
int mx[N<<2],cmx[N<<2],mxs[N<<2];
LL sum[N<<2];int tag[N<<2];
int a[N],n;

void maintain(int o)
{
    int lc=o<<1,rc=o<<1|1;
    sum[o]=sum[lc]+sum[rc];
    if(mn[lc]==mn[rc]) mn[o]=mn[lc],cmn[o]=cmn[lc]+cmn[rc],mns[o]=min(mns[lc],mns[rc]);
    if(mn[lc]<mn[rc]) mn[o]=mn[lc],cmn[o]=cmn[lc],mns[o]=min(mns[lc],mn[rc]);
    if(mn[lc]>mn[rc]) mn[o]=mn[rc],cmn[o]=cmn[rc],mns[o]=min(mns[rc],mn[lc]);
    if(mx[lc]==mx[rc]) mx[o]=mx[lc],cmx[o]=cmx[lc]+cmx[rc],mxs[o]=max(mxs[lc],mxs[rc]);
    if(mx[lc]>mx[rc]) mx[o]=mx[lc],cmx[o]=cmx[lc],mxs[o]=max(mxs[lc],mx[rc]);
    if(mx[lc]<mx[rc]) mx[o]=mx[rc],cmx[o]=cmx[rc],mxs[o]=max(mxs[rc],mx[lc]);
}

void pushdown(int o,int l,int r)
{
    int lc=o<<1,rc=o<<1|1,mid=(l+r)/2;
    if(tag[o])
    {
        sum[lc]+=1ll*tag[o]*(mid-l+1);
        sum[rc]+=1ll*tag[o]*(r-mid);
        mx[lc]+=tag[o];mn[lc]+=tag[o];
        if(mxs[lc]>-INT_MAX) mxs[lc]+=tag[o];
        if(mns[lc]<INT_MAX) mns[lc]+=tag[o];
        mx[rc]+=tag[o];mn[rc]+=tag[o];
        if(mxs[rc]>-INT_MAX) mxs[rc]+=tag[o];
        if(mns[rc]<INT_MAX) mns[rc]+=tag[o];
        tag[lc]+=tag[o];
        tag[rc]+=tag[o];
        tag[o]=0;
    }
    if(mn[lc]<mn[o])
    {
        if(mx[lc]==mn[lc]) mx[lc]=mn[o];
        if(mxs[lc]==mn[lc]) mxs[lc]=mn[o];
        sum[lc]+=1ll*(mn[o]-mn[lc])*cmn[lc];
        mn[lc]=mn[o];
    }
    if(mn[rc]<mn[o])
    {
        if(mx[rc]==mn[rc]) mx[rc]=mn[o];
        if(mxs[rc]==mn[rc]) mxs[rc]=mn[o];
        sum[rc]+=1ll*(mn[o]-mn[rc])*cmn[rc];
        mn[rc]=mn[o];
    }
    if(mx[lc]>mx[o])
    {
        if(mn[lc]==mx[lc]) mn[lc]=mx[o];
        if(mns[lc]==mx[lc]) mns[lc]=mx[o];
        sum[lc]+=1ll*(mx[o]-mx[lc])*cmx[lc];
        mx[lc]=mx[o];
    }
    if(mx[rc]>mx[o])
    {
        if(mn[rc]==mx[rc]) mn[rc]=mx[o];
        if(mns[rc]==mx[rc]) mns[rc]=mx[o];
        sum[rc]+=1ll*(mx[o]-mx[rc])*cmx[rc];
        mx[rc]=mx[o];
    }
}

void build(int o,int l,int r)
{
    if(l==r)
    {
        sum[o]=mn[o]=mx[o]=a[l];
        mns[o]=INT_MAX;mxs[o]=-INT_MAX;
        cmn[o]=cmx[o]=1;
        return;
    }
    int mid=(l+r)/2;
    build(o<<1,l,mid);
    build(o<<1|1,mid+1,r);
    maintain(o);
}

void add(int o,int l,int r,int nl,int nr,int x)
{
    if(l>=nl&&r<=nr)
    {
        mx[o]+=x;mn[o]+=x;
        if(mxs[o]>-INT_MAX) mxs[o]+=x;
        if(mns[o]<INT_MAX) mns[o]+=x;
        sum[o]+=1ll*x*(r-l+1);
        tag[o]+=x;
        return;
    }
    pushdown(o,l,r);
    int mid=(l+r)/2;
    if(nl<=mid) add(o<<1,l,mid,nl,nr,x);
    if(nr>mid) add(o<<1|1,mid+1,r,nl,nr,x);
    maintain(o);
}

void upmax(int o,int l,int r,int nl,int nr,int x)
{
    if(mn[o]>=x) return;
    if(l>=nl&&r<=nr&&mns[o]>x)
    {
        if(mx[o]==mn[o]) mx[o]=x;
        if(mxs[o]==mn[o]) mxs[o]=x;
        sum[o]+=1ll*(x-mn[o])*cmn[o];
        mn[o]=x;return;
    }
    pushdown(o,l,r);
    int mid=(l+r)/2;
    if(nl<=mid) upmax(o<<1,l,mid,nl,nr,x);
    if(nr>mid) upmax(o<<1|1,mid+1,r,nl,nr,x);
    maintain(o);
}

void upmin(int o,int l,int r,int nl,int nr,int x)
{
    if(mx[o]<=x) return;
    if(l>=nl&&r<=nr&&mxs[o]<x)
    {
        if(mn[o]==mx[o]) mn[o]=x;
        if(mns[o]==mx[o]) mns[o]=x;
        sum[o]+=1ll*(x-mx[o])*cmx[o];
        mx[o]=x;return;
    }
    pushdown(o,l,r);
    int mid=(l+r)/2;
    if(nl<=mid) upmin(o<<1,l,mid,nl,nr,x);
    if(nr>mid) upmin(o<<1|1,mid+1,r,nl,nr,x);
    maintain(o);
}

LL qsum(int o,int l,int r,int nl,int nr)
{
    if(l>=nl&&r<=nr) return sum[o];
    pushdown(o,l,r);
    int mid=(l+r)/2;LL res=0;
    if(nl<=mid) res+=qsum(o<<1,l,mid,nl,nr);
    if(nr>mid) res+=qsum(o<<1|1,mid+1,r,nl,nr);
    return res;
}

int qmax(int o,int l,int r,int nl,int nr)
{
    if(l>=nl&&r<=nr) return mx[o];
    pushdown(o,l,r);
    int mid=(l+r)/2,res=-INT_MAX;
    if(nl<=mid) res=max(res,qmax(o<<1,l,mid,nl,nr));
    if(nr>mid) res=max(res,qmax(o<<1|1,mid+1,r,nl,nr));
    return res;
}

int qmin(int o,int l,int r,int nl,int nr)
{
    if(l>=nl&&r<=nr) return mn[o];
    pushdown(o,l,r);
    int mid=(l+r)/2,res=INT_MAX;
    if(nl<=mid) res=min(res,qmin(o<<1,l,mid,nl,nr));
    if(nr>mid) res=min(res,qmin(o<<1|1,mid+1,r,nl,nr));
    return res;
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++) a[i]=read();
    build(1,1,n);
    for(int Q=read();Q;Q--)
    {
        int opt=read(),l=read(),r=read(),x;
        if(opt<=3) x=read();
        if(opt==1) add(1,1,n,l,r,x);
        if(opt==2) upmax(1,1,n,l,r,x);
        if(opt==3) upmin(1,1,n,l,r,x);
        if(opt==4) print(qsum(1,1,n,l,r));
        if(opt==5) print(qmax(1,1,n,l,r));
        if(opt==6) print(qmin(1,1,n,l,r));
    }
    flush();
    return 0;
}