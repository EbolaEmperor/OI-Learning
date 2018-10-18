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
int mx[N<<2];
LL sum[N<<2];
set<int> pos[N];
int pre[N],col[N],n;

LL gao(int o,int l,int r,int x)
{
    if(l==r) return max(x,mx[o]);
    int mid=(l+r)/2;
    if(mx[o]<=x) return 1ll*x*(r-l+1);
    if(mx[o<<1]<=x) return 1ll*x*(mid-l+1)+gao(o<<1|1,mid+1,r,x);
    return gao(o<<1,l,mid,x)+sum[o]-sum[o<<1];
}

void Maintain(int o,int m,int r)
{
    mx[o]=max(mx[o<<1],mx[o<<1|1]);
    sum[o]=sum[o<<1]+gao(o<<1|1,m+1,r,mx[o<<1]);
}

void Build(int o,int l,int r)
{
    if(l==r)
    {
        sum[o]=mx[o]=pre[l];
        return;
    }
    int mid=(l+r)/2;
    Build(o<<1,l,mid);
    Build(o<<1|1,mid+1,r);
    Maintain(o,mid,r);
}

void Modify(int o,int l,int r,int k,int x)
{
    if(l==r)
    {
        sum[o]=mx[o]=x;
        return;
    }
    int mid=(l+r)/2;
    if(k<=mid) Modify(o<<1,l,mid,k,x);
    else Modify(o<<1|1,mid+1,r,k,x);
    Maintain(o,mid,r);
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++) pos[i].insert(0);
    for(int i=1;i<=n;i++)
    {
        int x=read();
        pre[i]=*(--pos[x].end());
        pos[x].insert(i);
        col[i]=x;
    }
    Build(1,1,n);
    for(int Q=read();Q;Q--)
    {
        int opt=read();
        if(opt==1)
        {
            int p=read(),c=read();
            auto q=pos[col[p]].find(p);
            auto t1=q,t2=q;t1--;t2++;
            if(t2!=pos[col[p]].end())
            {
                pre[*t2]=*t1;
                Modify(1,1,n,*t2,*t1);
            }
            pos[col[p]].erase(q);
            col[p]=c;pos[c].insert(p);
            q=pos[c].find(p);
            t1=q;t2=q;t1--;t2++;
            if(t2!=pos[c].end())
            {
                pre[*t2]=p;
                Modify(1,1,n,*t2,p);
            }
            pre[p]=*t1;
            Modify(1,1,n,p,*t1);
        }
        else print(1ll*n*(n+1)/2-sum[1]);
    }
    flush();
    return 0;
}