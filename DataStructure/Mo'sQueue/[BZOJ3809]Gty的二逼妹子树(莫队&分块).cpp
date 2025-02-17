#include<bits/stdc++.h>
using namespace std;

namespace IO
{
    const int S=(1<<16)+5;
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
const int N=100010,B=100;
struct Qry{int l,r,a,b,id;} q[N*10];
int cnt[N],col[N],ans[N*10],num[1010],n,m;

bool operator < (const Qry &a,const Qry &b)
{
    if(a.l/B!=b.l/B) return a.l<b.l;
    if((a.l/B)&1) return a.r>b.r;
    else return a.r<b.r;
}

void ins(int p){if(++cnt[col[p]]==1)num[col[p]/B]++;}
void del(int p){if(!--cnt[col[p]])num[col[p]/B]--;}

int query(int l,int r)
{
    int ans=0;
    if(l/B==r/B)
    {
        for(int i=l;i<=r;i++)
            ans+=bool(cnt[i]);
        return ans;
    }
    for(int i=l;i<(l/B+1)*B;i++) ans+=bool(cnt[i]);
    for(int i=(l/B+1);i<r/B;i++) ans+=num[i];
    for(int i=r/B*B;i<=r;i++) ans+=bool(cnt[i]);
    return ans;
}

int main()
{
    n=read();m=read();
    for(int i=1;i<=n;i++) col[i]=read();
    for(int i=1;i<=m;i++)
    {
        q[i].id=i;
        q[i].l=read();q[i].r=read();
        q[i].a=read();q[i].b=read();
    }
    sort(q+1,q+1+m);
    int pl=0,pr=0;
    for(int i=1;i<=m;i++)
    {
        while(pl<q[i].l) del(pl++);
        while(pl>q[i].l) ins(--pl);
        while(pr<q[i].r) ins(++pr);
        while(pr>q[i].r) del(pr--);
        ans[q[i].id]=query(q[i].a,q[i].b);
    }
    for(int i=1;i<=m;i++) print(ans[i]);
    flush();
    return 0;
}