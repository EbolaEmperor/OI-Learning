#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
namespace IO
{
    const int S=(1<<20)+5;
    char buf[S],*H,*T;
    inline char Get()
    {
        if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
        if(H==T) return -1;return *H++;
    }
    inline LL read()
    {
        LL x=0;char c=Get();
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
const int N=2000010;
priority_queue<int> pq;
int n,a[N],k=0;
LL cnt;

int main()
{
    n=read();cnt=read();
    for(int i=1;i<=n;i++) a[i]=read();
    for(int i=1;i<=n;i++)
    {
        if(cnt<n-i) break;
        cnt-=n-i;k++;
    }
    for(int i=1;i<=k+1;i++) pq.push(a[i]);
    for(int i=k+1;i<=n;i++) a[i]=pq.top(),pq.pop(),pq.push(a[i+1]);
    for(int i=1;i<=k;i++) a[i]=i;
    for(int j=k+2;j<=n;j++)
    {
        if(a[j]<a[k+1]) swap(a[j],a[k+1]);
        if(!--cnt) break;
    }
    for(int i=1;i<=n;i++) print(a[i]),putc(' ');
    return flush(),0;
}