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
    inline char readc()
    {
        char c=Get();
        while(c<'A'||c>'Z') c=Get();
        return c;
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
const double alpha=0.75;
const int N=70010,MX=70000,P=10000010;
int sum[P],ls[P],rs[P],sz=0;
int mempool[P],tot=0;

int newnode(){return tot?mempool[tot--]:++sz;}

void rubbish(int &o)
{
    if(!o) return;
    mempool[++tot]=o;
    rubbish(ls[o]);
    rubbish(rs[o]);
    sum[o]=0;o=0;
}

void add(int &o,int l,int r,int k,int x)
{
    if(!o) o=newnode();
    sum[o]+=x;
    if(l==r) return;
    int mid=(l+r)/2;
    if(k<=mid) add(ls[o],l,mid,k,x);
    else add(rs[o],mid+1,r,k,x);
    if(!sum[o]) rubbish(o);
}

int root=0,n,*goat;
int rt[N],val[N],lc[N],rc[N];
int dfn[N],clk=0;
vector<int> rts,pts;

bool isbad(int o){return sum[rt[lc[o]]]>alpha*sum[rt[o]]||sum[rt[rc[o]]]>alpha*sum[rt[o]];}

void flatten(int &o)
{
    if(!o) return;
    rubbish(rt[o]);
    flatten(lc[o]);
    dfn[++clk]=o;
    flatten(rc[o]);
    o=0;
}

void build(int &o,int l,int r)
{
    int mid=(l+r)/2;o=dfn[mid];
    for(int i=l;i<=r;i++) add(rt[o],0,MX,val[dfn[i]],1);
    if(l<mid) build(lc[o],l,mid-1);
    if(r>mid) build(rc[o],mid+1,r);
}

void rebuild(int &o){clk=0;flatten(o);build(o,1,clk);}

void insert(int &o,int k,int x)
{
    if(!o){val[o=++n]=x;add(rt[o],0,MX,x,1);return;}
    add(rt[o],0,MX,x,1);
    int szl=sum[rt[lc[o]]];
    if(k<=szl+1) insert(lc[o],k,x);
    else insert(rc[o],k-szl-1,x);
    if(isbad(o)) goat=&o;
}

void insert(int k,int x)
{
    goat=NULL;insert(root,k,x);
    if(goat) rebuild(*goat);
}

int modify(int o,int k,int x)
{
    add(rt[o],0,MX,x,1);
    int szl=sum[rt[lc[o]]],t;
    if(k==szl+1) t=val[o],val[o]=x;
    else if(k<=szl) t=modify(lc[o],k,x);
    else t=modify(rc[o],k-szl-1,x);
    add(rt[o],0,MX,t,-1);
    return t;
}

void getnode(int o,int l,int r)
{
    int szl=sum[rt[lc[o]]];
    if(l==1&&r==sum[rt[o]]){rts.push_back(rt[o]);return;}
    if(r<=szl){getnode(lc[o],l,r);return;}
    if(l>szl+1){getnode(rc[o],l-szl-1,r-szl-1);return;}
    pts.push_back(val[o]);
    if(l<=szl) getnode(lc[o],l,szl);
    if(r>szl+1) getnode(rc[o],1,r-szl-1);
}

int query(int x,int y,int k)
{
    rts.clear();pts.clear();
    getnode(root,x,y);
    int l=0,r=MX,mid,ord;
    while(l<=r)
    {
        if(l==r) break;
        mid=(l+r)/2;ord=0;
        for(int i=0;i<rts.size();i++) ord+=sum[ls[rts[i]]];
        for(int i=0;i<pts.size();i++) ord+=(pts[i]>=l&&pts[i]<=mid);
        if(k<=ord){for(int i=0;i<rts.size();i++) rts[i]=ls[rts[i]];r=mid;}
        else{for(int i=0;i<rts.size();i++) rts[i]=rs[rts[i]];l=mid+1;k-=ord;}
    }
    return l;
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++) val[i]=read(),dfn[i]=i;
    build(root,1,n);
    int q,x,y,z,lastans=0;char opt;
    for(q=read();q;q--)
    {
        opt=readc();x=read();y=read();
        x^=lastans;y^=lastans;
        if(opt=='M') modify(root,x,y);
        if(opt=='I') insert(x,y);
        if(opt=='Q')
        {
            z=read()^lastans;
            lastans=query(x,y,z);
            print(lastans);
        }
    }
    flush();
    return 0;
}