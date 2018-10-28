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
const int N=300010;
int n,cost[N];
LL pre[N],suf[N],s[N],h[N];

struct Line
{
    LL k,b;
    Line(LL _k=0,LL _b=0):k(_k),b(_b){}
    LL get(int x){return k*x+b;}
    double intersec(const Line &a){return (double)(a.b-b)/(k-a.k);}
} stk[N];

void prework(LL* f)
{
    for(int i=1;i<=n;i++) s[i]=s[i-1]+cost[i];
    for(int i=1,top=0;i<=n;i++)
    {
        while(top&&stk[top].get(i)<=stk[top-1].get(i)) top--;
        f[i]=max(f[i-1],stk[top].get(i)-s[i]+1ll*i*(i+1)/2);
        Line tmp=Line(-i,f[i]+1ll*i*(i-1)/2+s[i]);
        while(top&&stk[top-1].intersec(stk[top])<=stk[top-1].intersec(tmp)) top--;
        stk[++top]=tmp;
    }
}

void divide(int L,int R)
{
    if(L==R){h[L]=1-cost[L];return;}
    int M=(L+R)/2,top=0;
    divide(L,M);divide(M+1,R);
    for(int i=L-1;i<M;i++)
    {
        Line tmp=Line(-i,pre[i]+1ll*i*(i-1)/2+s[i]);
        while(top>1&&stk[top-1].intersec(tmp)>=stk[top-1].intersec(stk[top])) top--;
        stk[++top]=tmp;
    }
    LL mx=-INT64_MAX;int now=1;
    for(int i=R;i>M;i--)
    {
        while(now<top&&stk[now].intersec(stk[now+1])>=i) now++;
        mx=max(mx,stk[now].get(i)+1ll*i*(i+1)/2-s[i]+suf[i+1]);
        h[i]=max(h[i],mx);
    }
    top=0;
    for(int i=M+1;i<=R;i++)
    {
        Line tmp=Line(-i,suf[i+1]+1ll*i*(i+1)/2-s[i]);
        while(top>1&&stk[top-1].intersec(tmp)>=stk[top-1].intersec(stk[top])) top--;
        stk[++top]=tmp;
    }
    now=top;mx=-INT64_MAX;
    for(int i=L-1;i<M;i++)
    {
        while(now>1&&stk[now].intersec(stk[now-1])<=i) now--;
        mx=max(mx,stk[now].get(i)+1ll*i*(i-1)/2+s[i]+pre[i]);
        h[i+1]=max(h[i+1],mx);
    }
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++) cost[i]=read();
    prework(pre);
    reverse(cost+1,cost+1+n);
    prework(suf);
    reverse(cost+1,cost+1+n);
    reverse(suf+1,suf+1+n);
    for(int i=1;i<=n;i++) s[i]=s[i-1]+cost[i];
    divide(1,n);
    for(int m=read(),p,x;m;m--)
    {
        p=read();x=read();
        print(max(pre[p-1]+suf[p+1],h[p]+cost[p]-x));
    }
    flush();
    return 0;
}