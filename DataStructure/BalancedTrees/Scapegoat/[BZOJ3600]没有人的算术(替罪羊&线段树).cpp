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
    inline char readc()
    {
        char c=Get();
        while(c<'A'||c>'Z') c=Get();
        return c;
    }
    char obuf[S],*oS=obuf,*oT=oS+S-1,c,qu[55];int qr;
    inline void flush(){fwrite(obuf,1,oS-obuf,stdout);oS=obuf;}
    inline void putc(char x){*oS++ =x;if(oS==oT) flush();}
    template <class I>inline void print(I x)
    {
        if(!x) putc('0');
        while(x) qu[++qr]=x%10+'0',x/=10;
        while(qr) putc(qu[qr--]);
        putc('\n');
    }
}

using namespace IO;
const int N=500010;
const double alpha=0.75;
int lc[N],rc[N],sz[N],tot=0;
double f[N];
vector<int> A;

struct node
{
    int x,y;
    node(int _x=0,int _y=0):x(_x),y(_y){}
    bool operator == (const node &a){return x==a.x&&y==a.y;}
    bool operator < (const node &a){return x!=a.x?f[x]<f[a.x]:f[y]<f[a.y];}
} num[N];

inline bool isbad(int o){return sz[lc[o]]>alpha*sz[o]+5||sz[rc[o]]>alpha*sz[o]+5;}
inline void maintain(int o){sz[o]=sz[lc[o]]+sz[rc[o]]+1;}

void flatten(int o)
{
    if(!o) return;
    flatten(lc[o]);
    A.push_back(o);
    flatten(rc[o]);
}

void rebuild(int &o,int l,int r,double L,double R)
{
    int mid=(l+r)/2;double M=(L+R)/2;
    o=A[mid-1];f[o]=M;lc[o]=rc[o]=0;
    if(l<mid) rebuild(lc[o],l,mid-1,L,M);
    if(r>mid) rebuild(rc[o],mid+1,r,M,R);
    maintain(o);
}

int insert(int &o,double L,double R,node x)
{
    double M=(L+R)/2;
    if(!o)
    {
        num[o=++tot]=x;
        lc[o]=rc[o]=0;
        sz[o]=1;
        f[o]=M;
        return o;
    }
    sz[o]++;
    if(isbad(o))
    {
        A.clear();flatten(o);
        rebuild(o,1,A.size(),L,R);
    }
    if(x==num[o]) return o;
    else if(x<num[o]) return insert(lc[o],L,M,x);
    else return insert(rc[o],M,R,x);
}

int mx[N],mxp[N],a[N];

void Build(int o,int l,int r)
{
    mxp[o]=l;mx[o]=1;
    if(l==r) return;
    int mid=(l+r)/2;
    Build(o<<1,l,mid);
    Build(o<<1|1,mid+1,r);
}

void Modify(int o,int l,int r,int k)
{
    if(l==r){mx[o]=a[l];mxp[o]=l;return;}
    int mid=(l+r)/2;
    if(k<=mid) Modify(o<<1,l,mid,k);
    else Modify(o<<1|1,mid+1,r,k);
    if(mx[o<<1]==mx[o<<1|1]) mx[o]=mx[o<<1],mxp[o]=mxp[o<<1];
    else if(f[mx[o<<1]]>f[mx[o<<1|1]]) mx[o]=mx[o<<1],mxp[o]=mxp[o<<1];
    else mx[o]=mx[o<<1|1],mxp[o]=mxp[o<<1|1];
}

node Query(int o,int l,int r,int nl,int nr)
{
    if(l>=nl&&r<=nr) return node(mxp[o],mx[o]);
    int mid=(l+r)/2;node res(0,0);
    if(nl<=mid)
    {
        node tmp=Query(o<<1,l,mid,nl,nr);
        if(tmp.y==res.y&&tmp.x<res.x) res=tmp;
        else if(f[tmp.y]>f[res.y]) res=tmp;
    }
    if(nr>mid)
    {
        node tmp=Query(o<<1|1,mid+1,r,nl,nr);
        if(tmp.y==res.y&&tmp.x<res.x) res=tmp;
        else if(f[tmp.y]>f[res.y]) res=tmp;
    }
    return res;
}

int main()
{
    int rt=0,n=read(),m=read();
    int t=insert(rt,0,1,node(1,0));
    for(int i=1;i<=n;i++) a[i]=t;
    Build(1,1,n);
    char opt;int l,r,k;
    while(m--)
    {
        opt=readc();l=read();r=read();
        if(opt=='C')
        {
            k=read();
            a[k]=insert(rt,0,1,node(a[l],a[r]));
            Modify(1,1,n,k);
        }
        else print(Query(1,1,n,l,r).x);
    }
    flush();
    return 0;
}