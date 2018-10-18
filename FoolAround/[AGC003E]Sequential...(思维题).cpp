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
        putc('\n');
    }
}

using namespace IO;
const int N=100010;
int n,m,top=0;
LL a[N],f[N];
LL delta[N];

void solve(LL x,LL y)
{
    if(!x) return;
    int t=upper_bound(a+1,a+1+top,x)-a-1;
    if(!t) delta[1]+=y,delta[x+1]-=y;
    else f[t]+=x/a[t]*y,solve(x%a[t],y);
}

int main()
{
    a[++top]=n=read();m=read();
    for(int i=1;i<=m;i++)
    {
        LL x=read();
        while(x<=a[top]) top--;
        a[++top]=x;
    }
    f[top]=1;
    for(int i=top;i>=2;i--) f[i-1]+=a[i]/a[i-1]*f[i],solve(a[i]%a[i-1],f[i]);
    delta[1]+=f[1];delta[a[1]+1]-=f[1];
    for(int i=1;i<=n;i++) print(delta[i]+=delta[i-1]);
    flush();
    return 0;
}