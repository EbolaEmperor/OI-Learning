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
    template<class I>inline void read(I &x)
    {
        x=0;int fg=1;char c=Get();
        while(!isdigit(c)&&c!='-') c=Get();
        if(c=='-') fg=-1,c=Get();
        while(isdigit(c)) x=x*10+c-'0',c=Get();
    }
    char obuf[S],*oS=obuf,*oT=oS+S-1,c,qu[55];int qr;
    inline void flush(){fwrite(obuf,1,oS-obuf,stdout);oS=obuf;}
    inline void putc(char x){*oS++ =x;if(oS==oT) flush();}
    template<class I>inline void print(I x)
    {
        if(!x) putc('0');
        if(x<0) putc('-'),x=-x;
        while(x) qu[++qr]=x%10+'0',x/=10;
        while(qr) putc(qu[qr--]);
    }
    template<class T1,class T2>inline void print(T1 x,T2 y)
    {
        print(x);putc(' ');
        print(y);putc('\n');
    }
}

using namespace IO;
typedef long long LL;
const int P=50000010;
const int MX=1000010;
const int N=200010;

int lc[P],rc[P],tot=0;LL sum[P];
int tree[N<<2],tag[N<<2],n,m;
int rts[155],tms[155],rt[155],cnt=0;

void insert(int &o,int l,int r,int k,int x)
{
    if(!o) o=++tot;
    sum[o]+=x;
    if(l==r) return;
    int mid=(l+r)/2;
    if(k<=mid) insert(lc[o],l,mid,k,x);
    else insert(rc[o],mid+1,r,k,x);
}

void Insert(int o,int l,int r,int nl,int nr,int x)
{
    if(l==nl&&r==nr)
    {
        insert(tree[o],0,MX,x,1);
        insert(tag[o],0,MX,x,1);
        return;
    }
    int mid=(l+r)/2;
    insert(tree[o],0,MX,x,nr-nl+1);
    if(nr<=mid) Insert(o<<1,l,mid,nl,nr,x);
    else if(nl>mid) Insert(o<<1|1,mid+1,r,nl,nr,x);
    else Insert(o<<1,l,mid,nl,mid,x),Insert(o<<1|1,mid+1,r,mid+1,nr,x);
}

void Query(int o,int l,int r,int nl,int nr)
{
    if(l==nl&&r==nr)
    {
        rts[++cnt]=tree[o];tms[cnt]=1;
        if(tag[o]&&r>l) rts[++cnt]=tag[o],tms[cnt]=nr-nl;
        return;
    }
    int mid=(l+r)/2;
    if(tag[o]) rts[++cnt]=tag[o],tms[cnt]=nr-nl+1;
    if(nr<=mid) Query(o<<1,l,mid,nl,nr);
    else if(nl>mid) Query(o<<1|1,mid+1,r,nl,nr);
    else Query(o<<1,l,mid,nl,mid),Query(o<<1|1,mid+1,r,mid+1,nr);
}

LL getsum(int o,int l,int r,int k)
{
    if(l==r) return sum[o];
    int mid=(l+r)/2;
    if(k<=mid) return getsum(lc[o],l,mid,k)+sum[rc[o]];
    else return getsum(rc[o],mid+1,r,k);
}

int gao(int l,int r,LL k)
{
    cnt=0;Query(1,1,n,l,r);
    for(int i=1;i<=cnt;i++) rt[i]=rts[i];
    LL s=0;int L=0,R=MX,M;k++;
    while(L<R)
    {
        M=L+R>>1;s=0;
        for(int i=1;i<=cnt;i++)
            s+=sum[rc[rts[i]]]*tms[i];
        if(k<=s) L=M+1;
        else R=M,k-=s;
        for(int i=1;i<=cnt;i++)
            rts[i]=(L==M+1)?rc[rts[i]]:lc[rts[i]];
    }
    s=0;
    for(int i=1;i<=cnt;i++)
        s+=getsum(rt[i],0,MX,L+1)*tms[i];
    print(L+1,s);return L+1;
}

int main()
{
    read(n);read(m);
    for(int i=1,x;i<=n;i++)
        read(x),Insert(1,1,n,i,i,0);
    int opt,l,r,lastp=0;LL x;
    while(m--)
    {
        read(opt);read(l);read(r);read(x);
        if(opt==0) Insert(1,1,n,l,r,x^lastp);
        else lastp=gao(l,r,x);
    }
    flush();
    return 0;
}