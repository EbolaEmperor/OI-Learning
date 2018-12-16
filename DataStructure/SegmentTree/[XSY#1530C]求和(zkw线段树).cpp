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
    inline void print(int x)
    {
        if(!x) putc('0');
        while(x) qu[++qr]=x%10+'0',x/=10;
        while(qr) putc(qu[qr--]);
        putc('\n');
    }
}

using namespace IO;
const int N=1000010;
int tr1[N<<2],tr2[N<<2],leaf;
int n,k,q,op,a[N];

inline int cmp(int x,int y){return a[x]==a[y]?x<y:a[x]<a[y];}
inline int maxp(int x,int y){return cmp(x,y)?y:x;}

void build()
{
    for(leaf=1;leaf<=n+3;leaf<<=1);
    for(int i=1;i<=n;i++) tr1[i+leaf]=i;
    for(int i=leaf;i;i--) tr1[i]=maxp(tr1[i<<1],tr1[i<<1|1]);
}

void modify1(int p){for(p=(p+leaf)>>1;p;p>>=1) tr1[p]=maxp(tr1[p<<1],tr1[p<<1|1]);}

int query(int l,int r)
{
    int res=0;
    for(l=leaf+l-1,r=leaf+r+1;l^r^1;l>>=1,r>>=1)
    {
        if(~l&1) res=maxp(res,tr1[l^1]);
        if(r&1) res=maxp(res,tr1[r^1]);
    }
    return res;
}

void modify2(int p)
{
    int L=p>1?query(max(p-k,1),p-1):0;
    int R=p<n?query(p+1,min(p+k,n)):0;
    int ans=maxp(L,R);
    tr2[leaf+p]=cmp(ans,p)?a[p]+a[ans]:0;
    for(p=(p+leaf)>>1;p;p>>=1)
        tr2[p]=max(tr2[p<<1],tr2[p<<1|1]);
}

int main()
{
    n=read();k=read();q=read();op=read();
    for(int i=1;i<=n;i++) a[i]=read();
    build();for(int i=1;i<=n;i++) modify2(i);
    print(tr2[1]);
    while(q--)
    {
        int x=read(),y=read();
        if(op) x^=tr2[1],y^=tr2[1];
        a[x]=y;modify1(x);modify2(x);
        if(x>1) modify2(query(max(1,x-k),x-1));
        if(x<n) modify2(query(x+1,min(n,x+k)));
        print(tr2[1]);
    }
    flush();
    return 0;
}