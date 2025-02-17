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
    }
}

using namespace IO;
const int N=100010;
const int BS=350;

struct Query
{
    int l,r,a,b,id,block;
    Query(){l=r=a=b=id=0;}
    Query(int x)
    {
        id=x;
        l=read();r=read();
        a=read();b=read();
        block=l/BS;
    }
    bool operator < (const Query &b) const{return block==b.block?r<b.r:block<b.block;}
} q[N*10];
int n,m,col[N];
int cnt[N],num[BS],dif[BS];
int res1[N*10],res2[N*10];

void ins(int c){num[c/BS]++;if(++cnt[c]==1) dif[c/BS]++;}
void del(int c){num[c/BS]--;if(--cnt[c]==0) dif[c/BS]--;}

void getans(int l,int r,int id)
{
    int ans1=0,ans2=0;
    if(l/BS==r/BS)
    {
        for(int i=l;i<=r;i++) ans1+=cnt[i],ans2+=bool(cnt[i]);
        res1[id]=ans1;res2[id]=ans2;
        return;
    }
    int ld=(l/BS+1)*BS,rd=r/BS*BS;
    for(int i=l;i<ld;i++) ans1+=cnt[i],ans2+=bool(cnt[i]);
    for(int i=rd;i<=r;i++) ans1+=cnt[i],ans2+=bool(cnt[i]);
    for(int i=ld/BS;i<rd/BS;i++) ans1+=num[i],ans2+=dif[i];
    res1[id]=ans1;res2[id]=ans2;
}

int main()
{
    n=read();m=read();
    for(int i=1;i<=n;i++) col[i]=read();
    for(int i=1;i<=m;i++) q[i]=i;
    sort(q+1,q+1+m);
    int pl=0,pr=0;
    for(int i=1;i<=m;i++)
    {
        while(pl>q[i].l) ins(col[--pl]);
        while(pr<q[i].r) ins(col[++pr]);
        while(pl<q[i].l) del(col[pl++]);
        while(pr>q[i].r) del(col[pr--]);
        getans(q[i].a,q[i].b,q[i].id);
    }
    for(int i=1;i<=m;i++)
    {
        print(res1[i]);putc(' ');
        print(res2[i]);putc('\n');
    }
    flush();
    return 0;
}