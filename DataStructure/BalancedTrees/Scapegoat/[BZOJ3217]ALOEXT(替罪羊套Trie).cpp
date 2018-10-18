#include<bits/stdc++.h>
#define FR first
#define SE second
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
const int P=32000010;
const int N=200010;
const int MX=1048576;
int triemem[P],cnt1=0;
int ch[P][2],sz[P],tot=0;

int newtrie()
{
    int o=cnt1?triemem[cnt1--]:++tot;
    ch[o][0]=ch[o][1]=0;sz[o]=0;
    return o;
}
void deltrie(int &o){triemem[++cnt1]=o;o=0;}

void insert(int &o,int x,int d=19)
{
    if(!o) o=newtrie();
    sz[o]++;
    if(d<0) return;
    int p=(x>>d)&1;
    insert(ch[o][p],x,d-1);
}

void erase(int &o,int x,int d=19)
{
    if(d<0)
    {
        if(!--sz[o]) deltrie(o);
        return;
    }
    int p=(x>>d)&1;
    erase(ch[o][p],x,d-1);
    if(!--sz[o]) deltrie(o);
}

void clear(int &o)
{
    if(!o) return;
    clear(ch[o][0]);
    clear(ch[o][1]);
    deltrie(o);
}

int query(int o,int x,int d=19)
{
    if(d<0) return 0;int p=(x>>d)&1;
    if(ch[o][p^1]) return (1<<d)|query(ch[o][p^1],x,d-1);
    else return query(ch[o][p],x,d-1);
}

typedef pair<int,int> pii;
const double alpha=0.8;
int lc[N],rc[N],tot2=0;
int a[N],root[N];
int szt[N],sze[N],val[N];
bool deled[N];
int sgtmem[N],cnt2=0;
vector<int> A;
pii mx[N];

pii pairmax(pii a,pii b)
{
    if(b.FR>a.FR) a.SE=a.FR,a.FR=b.FR;
    else if(b.FR>a.SE) a.SE=b.FR;
    if(b.SE>a.FR) a.SE=a.FR,a.FR=b.SE;
    else if(b.SE>a.SE) a.SE=b.SE;
    return a;
}

int Newsgt(int x)
{
    int o=cnt2?sgtmem[cnt2--]:++tot2;
    mx[o]=pii(x,0);
    lc[o]=rc[o]=0;
    szt[o]=sze[o]=1;
    deled[o]=0;val[o]=x;
    insert(root[o],x);
    return o;
}
void Delsgt(int &o){sgtmem[++cnt2]=o;o=0;}

int Maintain(int o)
{
    szt[o]=szt[lc[o]]+szt[rc[o]]+1;
    sze[o]=sze[lc[o]]+sze[rc[o]]+(!deled[o]);
    mx[o]=pairmax(mx[lc[o]],mx[rc[o]]);
    mx[o]=pairmax(mx[o],pii(val[o],0));
}

bool Isbad(int o){return szt[lc[o]]>alpha*szt[o]+5||szt[rc[o]]>alpha*szt[o]+5;}

void build(int &o,int l,int r)
{
    int mid=(l+r)/2;
    o=Newsgt(a[mid]);
    if(l<mid) build(lc[o],l,mid-1);
    if(r>mid) build(rc[o],mid+1,r);
    for(int i=l;i<=r;i++)
        if(i!=mid) insert(root[o],a[i]);
    Maintain(o);
}

void Flatten(int &o)
{
    if(!o) return;
    Flatten(lc[o]);
    if(!deled[o]) A.push_back(o);
    Flatten(rc[o]);
    clear(root[o]);
    if(deled[o]) Delsgt(o);
}

void Rebuild(int &o,int l,int r)
{
    int mid=(l+r)/2;
    o=A[mid-1];lc[o]=rc[o]=0;
    if(l<mid) Rebuild(lc[o],l,mid-1);
    if(r>mid) Rebuild(rc[o],mid+1,r);
    for(int i=l;i<=r;i++) insert(root[o],val[A[i-1]]);
    Maintain(o);
}

void Insert(int &o,int k,int x)
{
    if(!o){o=Newsgt(x);return;}
    if(Isbad(o))
    {
        A.clear();Flatten(o);
        Rebuild(o,1,A.size());
    }
    insert(root[o],x);
    int szl=sze[lc[o]];
    if(k<=szl) Insert(lc[o],k,x);
    else Insert(rc[o],k-szl-(!deled[o]),x);
    Maintain(o);
}

int Find(int o,int k)
{
    int szl=sze[lc[o]];
    if(k==szl&&!deled[o]) return val[o];
    if(k<szl) return Find(lc[o],k);
    else return Find(rc[o],k-szl-(!deled[o]));
}

void Remove(int &o,int k,int x)
{
    erase(root[o],x);
    int szl=sze[lc[o]];
    if(k==szl&&!deled[o])
    {
        deled[o]=1;val[o]=0;
        Maintain(o);
        return;
    }
    if(k<szl) Remove(lc[o],k,x);
    else Remove(rc[o],k-szl-(!deled[o]),x);
    Maintain(o);
}

pii Second(int o,int l,int r,int nl,int nr)
{
    if(l>=nl&&r<=nr) return mx[o];
    pii res(0,0);int szl=sze[lc[o]],M=l+szl+(!deled[o]);
    if(nl<l+szl&&szl) res=pairmax(res,Second(lc[o],l,l+szl-1,nl,nr));
    if(nr>=M&&r>=M) res=pairmax(res,Second(rc[o],M,r,nl,nr));
    if(!deled[o]&&nl<=l+szl&&nr>=l+szl) res=pairmax(res,pii(val[o],0));
    return res;
}

int Query(int o,int l,int r,int nl,int nr,int x)
{
    if(l>=nl&&r<=nr) return query(root[o],x);
    int res=0,szl=sze[lc[o]],M=l+szl+(!deled[o]);
    if(nl<l+szl&&szl) res=max(res,Query(lc[o],l,l+szl-1,nl,nr,x));
    if(nr>=M&&r>=M) res=max(res,Query(rc[o],M,r,nl,nr,x));
    if(!deled[o]&&nl<=l+szl&&nr>=l+szl) res=max(res,x^val[o]);
    return res;
}

int main()
{
    int n=read(),m=read(),rt=0;
    for(int i=1;i<=n;i++) a[i]=read();
    build(rt,1,n);
    int x,y,z,lastans=0;char opt;
    while(m--)
    {
        opt=readc();
        if(opt=='I')
        {
            x=(read()+lastans)%n;
            y=(read()+lastans)%MX;
            Insert(rt,x,y);n++;
        }
        if(opt=='D')
        {
            x=(read()+lastans)%n;
            y=Find(rt,x);
            Remove(rt,x,y);n--;
        }
        if(opt=='C')
        {
            x=(read()+lastans)%n;
            y=(read()+lastans)%MX;
            z=Find(rt,x);
            Remove(rt,x,z);
            Insert(rt,x,y);
        }
        if(opt=='F')
        {
            x=(read()+lastans)%n+1;
            y=(read()+lastans)%n+1;
            z=Second(rt,1,n,x,y).SE;
            lastans=Query(rt,1,n,x,y,z);
            print(lastans);
        }
    }
    flush();
    return 0;
}