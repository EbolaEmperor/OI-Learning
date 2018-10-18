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
        putc('\n');
    }
}

using namespace IO;
typedef long long LL;
const int N=100010;
int a[N],rt[N],n;
int lc[N<<6],rc[N<<6],sz=0;
LL sum[N<<6];

void insert(int &o,int p,int l,int r,int k)
{
    o=++sz;sum[o]=sum[p]+k;
    if(l==r) return;
    int mid=(l+r)/2;
    lc[o]=lc[p];rc[o]=rc[p];
    if(k<=mid) insert(lc[o],lc[p],l,mid,k);
    else insert(rc[o],rc[p],mid+1,r,k);
}

LL query(int L,int R,int l,int r,int k)
{
    if(l==r) return sum[R]-sum[L];
    int mid=(l+r)/2;
    if(k<=mid) return query(lc[L],lc[R],l,mid,k);
    else return sum[lc[R]]-sum[lc[L]]+query(rc[L],rc[R],mid+1,r,k);
}

LL gao(int l,int r)
{
    LL res=0;
    while(true)
    {
        LL tmp=query(rt[l-1],rt[r],1,1e9,res+1);
        if(res==tmp) return res+1;
        else res=tmp;
    }
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++)
        insert(rt[i],rt[i-1],1,1e9,read());
    for(int Q=read();Q;Q--)
    {
        int l=read(),r=read();
        print(gao(l,r));
    }
    flush();
    return 0;
}