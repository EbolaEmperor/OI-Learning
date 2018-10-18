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
    }
}

using namespace IO;
const int N=1000010;
int a[N],n,k,leaf;
int mn[N],mx[N];
int tmx[N<<2],tmn[N<<2];

void maintain(int o)
{
    tmn[o]=min(tmn[o<<1],tmn[o<<1|1]);
    tmx[o]=max(tmx[o<<1],tmx[o<<1|1]);
}

void Build()
{
    for(leaf=1;leaf<=n+2;leaf<<=1);
    for(int i=0;i<=leaf+n;i++)
        tmn[i]=INT_MAX,tmx[i]=-INT_MAX;
    for(int i=1;i<=n;i++)
        tmx[leaf+i]=tmn[leaf+i]=a[i];
    for(int i=leaf-1;i;i--) maintain(i);
}

int qmin(int l,int r)
{
    int res=INT_MAX;
    for(l=leaf+l-1,r=leaf+r+1;l^r^1;l>>=1,r>>=1)
    {
        if(~l&1) res=min(res,tmn[l^1]);
        if(r&1) res=min(res,tmn[r^1]);
    }
    return res;
}

int qmax(int l,int r)
{
    int res=-INT_MAX;
    for(l=leaf+l-1,r=leaf+r+1;l^r^1;l>>=1,r>>=1)
    {
        if(~l&1) res=max(res,tmx[l^1]);
        if(r&1) res=max(res,tmx[r^1]);
    }
    return res;
}

int main()
{
    n=read();k=read();
    for(int i=1;i<=n;i++) a[i]=read();
    Build();
    for(int i=0;i<=n-k;i++)
    {
        mn[i]=qmin(i+1,i+k);
        mx[i]=qmax(i+1,i+k);
    }
    for(int i=0;i<=n-k;i++) print(mn[i]),putc(' ');putc('\n');
    for(int i=0;i<=n-k;i++) print(mx[i]),putc(' ');putc('\n');
    flush();
    return 0;
}