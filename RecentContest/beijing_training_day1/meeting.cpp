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
const int N=300010;
struct Seg
{
    int l,r;
    Seg(int _l=0,int _r=0):l(_l),r(_r){}
    Seg operator + (const Seg &b){return Seg(max(l,b.l),min(r,b.r));}
} seg[N];
struct Line
{
    int k;LL b;
    Line(int _k=0,LL _b=-1e18):k(_k),b(_b){}
    LL operator () (const int &x){return (LL)x*k+b;}
} line[N<<2];
int mx[N<<2],mn[N<<2];
LL f[N];
int n;

void insert(int o,int l,int r,int nl,int nr,Line t)
{
    int mid=(l+r)/2;
    if(l>=nl&&r<=nr)
    {
        if(t(mid)>line[o](mid)) swap(t,line[o]);
        if(t(l)>line[o](l)) insert(o<<1,l,mid,nl,nr,t);
        if(t(r)>line[o](r)) insert(o<<1|1,mid+1,r,nl,nr,t);
        return;
    }
    if(nl<=mid) insert(o<<1,l,mid,nl,nr,t);
    if(nr>mid) insert(o<<1|1,mid+1,r,nl,nr,t);
}

LL query(int o,int l,int r,int x)
{
    LL res=line[o](x);
    if(l==r) return res;
    int mid=(l+r)/2;
    if(x<=mid) res=max(res,query(o<<1,l,mid,x));
    else res=max(res,query(o<<1|1,mid+1,r,x));
    return res;
}

void build(int o,int l,int r)
{
    if(l==r){mx[o]=seg[l].l;mn[o]=seg[l].r;return;}
    int mid=(l+r)/2;
    build(o<<1,l,mid);
    build(o<<1|1,mid+1,r);
    mx[o]=max(mx[o<<1],mx[o<<1|1]);
    mn[o]=min(mn[o<<1],mn[o<<1|1]);
}

Seg qseg(int o,int l,int r,int nl,int nr)
{
    if(l>=nl&&r<=nr) return Seg(mx[o],mn[o]);
    int mid=(l+r)/2;Seg res(1,1e6);
    if(nl<=mid) res=res+qseg(o<<1,l,mid,nl,nr);
    if(nr>mid) res=res+qseg(o<<1|1,mid+1,r,nl,nr);
    return res;
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++)
        seg[i].l=read(),seg[i].r=read();
    build(1,1,n);
    for(int i=0,r=0;i<=n;i++)
    {
        f[i]=i?query(1,1,n,i)+(LL)i*(i-1):0;
        Seg tmp=qseg(1,1,n,i+1,r+1);
        while(r<n&&tmp.r-tmp.l>=1) r++,tmp=qseg(1,1,n,i+1,r+1);
        if(r>i) insert(1,1,n,i+1,r,Line(-2*i,f[i]+(LL)i*(i+1)));
    }
    printf("%lld\n",f[n]/2);
    return 0;
}