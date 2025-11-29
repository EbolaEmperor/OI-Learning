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
const int N=120010;
int minv[N<<2],tmn[N<<2];
LL ans[N<<2],cnt[N<<2],tans[N<<2];
struct QRY{int l,r,id;} qry[N];
int n,q,p[N];
LL qans[N];

inline void maintain(int o)
{
    minv[o]=min(minv[o<<1],minv[o<<1|1]);cnt[o]=0;
    if(minv[o]==minv[o<<1]) cnt[o]+=cnt[o<<1];
    if(minv[o]==minv[o<<1|1]) cnt[o]+=cnt[o<<1|1];
    ans[o]=ans[o<<1]+ans[o<<1|1];
}

inline void upmin(int o,int x){minv[o]+=x;tmn[o]+=x;}
inline void upans(int o,int x){ans[o]+=cnt[o]*x;tans[o]+=x;}

inline void pushdown(int o)
{
    if(tmn[o])
    {
        upmin(o<<1,tmn[o]);
        upmin(o<<1|1,tmn[o]);
        tmn[o]=0;
    }
    if(tans[o])
    {
        if(minv[o]==minv[o<<1]) upans(o<<1,tans[o]);
        if(minv[o]==minv[o<<1|1]) upans(o<<1|1,tans[o]);
        tans[o]=0;
    }
}

void build(int o,int l,int r)
{
    minv[o]=l;cnt[o]=1;
    if(l==r) return;
    int mid=(l+r)/2;
    build(o<<1,l,mid);
    build(o<<1|1,mid+1,r);
}

void addmn(int o,int l,int r,int nl,int nr,int x)
{
    if(l>=nl&&r<=nr){upmin(o,x);return;}
    int mid=(l+r)/2;pushdown(o);
    if(nl<=mid) addmn(o<<1,l,mid,nl,nr,x);
    if(nr>mid) addmn(o<<1|1,mid+1,r,nl,nr,x);
    maintain(o);
}

LL query(int o,int l,int r,int nl,int nr)
{
    if(l>=nl&&r<=nr) return ans[o];
    int mid=(l+r)/2;LL res=0;pushdown(o);
    if(nl<=mid) res+=query(o<<1,l,mid,nl,nr);
    if(nr>mid) res+=query(o<<1|1,mid+1,r,nl,nr);
    return res;
}

void falun_dafa_is_good()
{
    static int stk1[N],stk2[N],top1=0,top2=0;
    for(int i=1,pp=1;i<=n;i++)
    {
        while(top1&&p[i]>p[stk1[top1]])
            addmn(1,1,n,stk1[top1-1]+1,stk1[top1],p[i]-p[stk1[top1]]),top1--;
        stk1[++top1]=i;
        while(top2&&p[i]<p[stk2[top2]])
            addmn(1,1,n,stk2[top2-1]+1,stk2[top2],p[stk2[top2]]-p[i]),top2--;
        stk2[++top2]=i;
        upans(1,1);
        for(;qry[pp].r==i;pp++)
            qans[qry[pp].id]=query(1,1,n,qry[pp].l,i);
    }
    for(int i=1;i<=q;i++) print(qans[i]);
}

int main()
{
    n=read();build(1,1,n);
    for(int i=1;i<=n;i++) p[i]=read();
    q=read();
    for(int i=1;i<=q;i++)
        qry[i].l=read(),qry[i].r=read(),qry[i].id=i;
    sort(qry+1,qry+1+q,[](QRY a,QRY b){return a.r<b.r;});
    falun_dafa_is_good();flush();
    return 0;
}