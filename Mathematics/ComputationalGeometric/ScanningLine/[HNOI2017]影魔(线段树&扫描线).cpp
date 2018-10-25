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
const int N=200010;
LL sum[N<<2],tag[N<<2];
int n,m,p1,p2,val[N],bgr[N];
struct QRY{int l,r,id;} q[N];
vector<QRY> L[N];
stack<int> s;
LL ans[N];

void Add(int o,int l,int r,int nl,int nr,LL x)
{
    if(nl>nr) return;
    if(l>=nl&&r<=nr)
    {
        sum[o]+=x*(r-l+1);
        tag[o]+=x;
        return;
    }
    int mid=(l+r)/2;
    if(nl<=mid) Add(o<<1,l,mid,nl,nr,x);
    if(nr>mid) Add(o<<1|1,mid+1,r,nl,nr,x);
    sum[o]=sum[o<<1]+sum[o<<1|1]+tag[o]*(r-l+1);
}

LL Qsum(int o,int l,int r,int nl,int nr)
{
    if(l==nl&&r==nr) return sum[o];
    int mid=(l+r)/2;LL res=tag[o]*(nr-nl+1);
    if(nr<=mid) res+=Qsum(o<<1,l,mid,nl,nr);
    else if(nl>mid) res+=Qsum(o<<1|1,mid+1,r,nl,nr);
    else res+=Qsum(o<<1,l,mid,nl,mid)+Qsum(o<<1|1,mid+1,r,mid+1,nr);
    return res;
}

void solve()
{
    memset(sum,0,sizeof(sum));
    memset(tag,0,sizeof(tag));
    for(int i=1;i<=n;i++) L[i].clear();
    for(int i=1;i<=m;i++) L[q[i].l].push_back(q[i]);
    while(!s.empty()) s.pop();
    val[n+1]=n+1;s.push(n+1);
    for(int i=n;i>=1;i--)
    {
        while(val[s.top()]<val[i]) s.pop();
        bgr[i]=s.top();s.push(i);
    }
    for(int i=n;i>=1;i--)
    {
        Add(1,1,n,i+1,min(bgr[i],n),p2);
        if(bgr[i]<=n) Add(1,1,n,bgr[i],bgr[i],p1-2*p2);
        for(auto x : L[i]) ans[x.id]+=Qsum(1,1,n,x.l,x.r);
    }
}

int main()
{
    n=read();m=read();p1=read();p2=read();
    for(int i=1;i<=n;i++) val[i]=read();
    for(int i=1;i<=m;i++)
    {
        q[i].l=read();
        q[i].r=read();
        q[i].id=i;
    }
    solve();
    for(int i=1;i<=m;i++)
    {
        q[i].l=n-q[i].l+1;
        q[i].r=n-q[i].r+1;
        swap(q[i].l,q[i].r);
    }
    reverse(val+1,val+1+n);solve();
    for(int i=1;i<=m;i++) print(ans[i]);
    flush();
    return 0;
}