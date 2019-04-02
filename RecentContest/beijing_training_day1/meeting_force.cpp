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
const int N=300010,P=N*60;
struct Seg
{
    int l,r;
    Seg(int _l=0,int _r=0):l(_l),r(_r){}
    Seg operator + (const Seg &b){return Seg(max(l,b.l),min(r,b.r));}
} seg[N];
struct Line
{
    int k;LL b;
    Line(int _k=0,LL _b=0):k(_k),b(_b){}
    LL operator () (const int &x){return (LL)x*k+b;}
} line[P];
LL f[N];
int n,tr[N<<2],lc[P],rc[P],tot=0;
int mx[N<<2],mn[N<<2];

void ins(int &o,int l,int r,Line t)
{
    if(!o){o=++tot;line[o]=t;return;}
    int mid=(l+r)/2;
    if(t(mid)>line[o](mid)) swap(line[o],t);
    if(l==r) return;
    if(t(l)>line[o](l)) ins(lc[o],l,mid,t);
    if(t(l)>line[o](r)) ins(rc[o],mid+1,r,t);
}

LL qmax(int o,int l,int r,int x)
{
    if(!o) return -1e18;
    LL res=line[o](x);
    if(l==r) return res;
    int mid=(l+r)/2;
    if(x<=mid) res=max(res,qmax(lc[o],l,mid,x));
    else res=max(res,qmax(rc[o],mid+1,r,x));
    return res;
}

void insert(int o,int l,int r,int k,const Line &t)
{
    ins(tr[o],1,n,t);
    if(l==r) return;
    int mid=(l+r)/2;
    if(k<=mid) insert(o<<1,l,mid,k,t);
    else insert(o<<1|1,mid+1,r,k,t);
}

LL query(int o,int l,int r,int nl,int nr,int x)
{
    if(l>=nl&&r<=nr) return qmax(tr[o],1,n,x);
    int mid=(l+r)/2;LL res=-1e18;
    if(nl<=mid) res=max(res,query(o<<1,l,mid,nl,nr,x));
    if(nr>mid) res=max(res,query(o<<1|1,mid+1,r,nl,nr,x));
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
    insert(1,0,n-1,0,Line(0,0));
    for(int i=1,l=1;i<=n;i++)
    {
        Seg tmp=qseg(1,1,n,l,i);
        while(tmp.r-tmp.l<1) l++,tmp=qseg(1,1,n,l,i);
        f[i]=query(1,0,n-1,l-1,i-1,i)+(LL)i*(i-1);
        insert(1,0,n-1,i,Line(-2*i,f[i]+(LL)i*(i+1)));
    }
    printf("%lld\n",f[n]/2);
    return 0;
}