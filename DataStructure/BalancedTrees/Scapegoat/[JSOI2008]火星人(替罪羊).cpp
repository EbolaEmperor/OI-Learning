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
        while((c<'A'||c>'Z')&&(c<'a'||c>'z')) c=Get();
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
typedef unsigned long long ull;
const int N=150010;
const double alpha=0.75;
int lc[N],rc[N],sz[N],tot=0,rt=0;
ull val[N],sum[N],pw[N];
vector<int> A;

bool isbad(int o){return sz[lc[o]]>alpha*sz[o]+5||sz[rc[o]]>alpha*sz[o]+5;}
void maintain(int o)
{
    sum[o]=sum[rc[o]]+val[o]*pw[sz[rc[o]]]+sum[lc[o]]*pw[sz[rc[o]]+1];
    sz[o]=sz[lc[o]]+sz[rc[o]]+1;
}

void flatten(int o)
{
    if(!o) return;
    flatten(lc[o]);
    A.push_back(o);
    flatten(rc[o]);
}

void rebuild(int &o,int l,int r)
{
    int mid=(l+r)/2;
    o=A[mid-1];
    lc[o]=rc[o]=0;
    if(l<mid) rebuild(lc[o],l,mid-1);
    if(r>mid) rebuild(rc[o],mid+1,r);
    maintain(o);
}

void insert(int &o,int k,int x)
{
    if(!o)
    {
        o=++tot;
        lc[o]=rc[o]=0;
        val[o]=sum[o]=x;
        sz[o]=1;
        return;
    }
    if(isbad(o))
    {
        A.clear();flatten(o);
        rebuild(o,1,A.size());
    }
    int szl=sz[lc[o]];
    if(k<=szl) insert(lc[o],k,x);
    else insert(rc[o],k-szl-1,x);
    maintain(o);
}

void modify(int o,int k,int x)
{
    int szl=sz[lc[o]];
    if(k==szl+1) val[o]=x;
    else if(k<=szl) modify(lc[o],k,x);
    else modify(rc[o],k-szl-1,x);
    maintain(o);
}

ull find(int o,int l,int r,int nl,int nr)
{
    if(l==nl&&r==nr) return sum[o];
    int szl=sz[lc[o]];ull res=0;
    if(nr<l+szl) return find(lc[o],l,l+szl-1,nl,nr);
    if(nl>l+szl) return find(rc[o],l+szl+1,r,nl,nr);
    if(nl<l+szl) res=find(lc[o],l,l+szl-1,nl,l+szl-1);
    if(nl<=l+szl&&nr>=l+szl) res=res*pw[1]+val[o];
    if(nr>l+szl) res=res*pw[nr-l-szl]+find(rc[o],l+szl+1,r,l+szl+1,nr);
    return res;
}

int lcp(int x,int y)
{
    int res=0;
    for(int i=17;i>=0;i--)
    {
        if(x+(1<<i)-1>tot) continue;
        if(y+(1<<i)-1>tot) continue;
        ull s1=find(rt,1,tot,x,x+(1<<i)-1);
        ull s2=find(rt,1,tot,y,y+(1<<i)-1);
        if(s1!=s2) continue;
        res|=1<<i;x+=1<<i;y+=1<<i;
    }
    return res;
}

int main()
{
    pw[0]=1;
    for(int i=1;i<N;i++)
        pw[i]=pw[i-1]*131;
    static char ss[N];
    scanf("%s",ss+1);
    tot=strlen(ss+1);
    for(int i=1;i<=tot;i++)
        A.push_back(i),val[i]=ss[i]-'a'+1;
    rebuild(rt,1,tot);
    for(int m=read();m;m--)
    {
        char opt=readc();
        if(opt=='I')
        {
            int x=read();
            char d=readc();
            insert(rt,x,d-'a'+1);
        }
        if(opt=='R')
        {
            int x=read();
            char d=readc();
            modify(rt,x,d-'a'+1);
        }
        if(opt=='Q') print(lcp(read(),read()));
    }
    flush();
    return 0;
}