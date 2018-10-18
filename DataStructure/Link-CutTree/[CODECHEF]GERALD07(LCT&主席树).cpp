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
const int N=400010;
int fa[N],ch[N][2];
int val[N],mn[N];
bool rev[N];
int stk[N],top;
int e[N][2],n,m;

inline void maintain(int x){mn[x]=min(min(mn[ch[x][0]],mn[ch[x][1]]),val[x]);}
inline void pushr(int x){swap(ch[x][0],ch[x][1]);rev[x]^=1;}
inline bool nrt(int x){return ch[fa[x]][0]==x||ch[fa[x]][1]==x;}
inline void pushdown(int x)
{
    if(!rev[x]) return;
    if(ch[x][0]) pushr(ch[x][0]);
    if(ch[x][1]) pushr(ch[x][1]);
    rev[x]^=1;
}

void rotate(int x)
{
    int y=fa[x],z=fa[y];
    int k=(ch[y][1]==x),w=ch[x][k^1];
    if(nrt(y)) ch[z][ch[z][1]==y]=x;
    ch[y][k]=w;ch[x][k^1]=y;
    if(w) fa[w]=y;
    fa[y]=x;fa[x]=z;
    maintain(y);
    maintain(x);
}
void splay(int x)
{
    int y=x,z;
    stk[top=1]=x;
    while(nrt(y)) stk[++top]=fa[y],y=fa[y];
    while(top) pushdown(stk[top--]);
    while(nrt(x))
    {
        y=fa[x];z=fa[y];
        if(nrt(y)) rotate((ch[y][0]==x)^(ch[z][0]==y)?x:y);
        rotate(x);
    }
    maintain(x);
}

void access(int x)
{
    for(int y=0;x;y=x,x=fa[x])
    {
        splay(x);
        ch[x][1]=y;
        maintain(x);
    }
}
int find(int x)
{
    access(x);splay(x);
    while(ch[x][0]) x=ch[x][0];
    return x;
}
void makeroot(int x){access(x);splay(x);pushr(x);}
void link(int x,int y){makeroot(x);fa[x]=y;}
void link(int eid)
{
    int x=e[eid][0],y=e[eid][1];
    link(x,eid+n);link(eid+n,y);
}
void cut(int x,int y)
{
    makeroot(x);access(y);splay(y);
    fa[x]=0;ch[y][0]=0;
    maintain(y);
}
void cut(int eid)
{
    int x=e[eid][0],y=e[eid][1];
    cut(x,eid+n);cut(y,eid+n);
}
int Link(int eid)
{
    int x=e[eid][0],y=e[eid][1];
    if(x==y) return eid;
    makeroot(x);
    if(find(y)!=x)
        return link(eid),0;
    int a=mn[y];
    cut(a);link(eid);
    return a;
}

const int P=N<<4;
int rt[N],lc[P],rc[P],sum[P],tot=0;

void insert(int &o,int p,int l,int r,int k)
{
    sum[o=++tot]=sum[p]+1;
    if(l==r) return;
    int mid=(l+r)/2;
    lc[o]=lc[p];rc[o]=rc[p];
    if(k<=mid) insert(lc[o],lc[p],l,mid,k);
    else insert(rc[o],rc[p],mid+1,r,k);
}
int query(int L,int R,int l,int r,int k)
{
    if(l==r) return sum[R]-sum[L];
    int mid=(l+r)/2;
    if(k<=mid) return query(lc[L],lc[R],l,mid,k);
    return sum[lc[R]]-sum[lc[L]]+query(rc[L],rc[R],mid+1,r,k);
}

void Init()
{
    tot=0;
    memset(fa,0,sizeof(fa));
    memset(ch,0,sizeof(ch));
    memset(lc,0,sizeof(lc));
    memset(rc,0,sizeof(rc));
    memset(rt,0,sizeof(rt));
    memset(sum,0,sizeof(sum));
    memset(rev,0,sizeof(rev));
    for(int i=0;i<=n;i++) val[i]=mn[i]=INT_MAX;
    for(int i=n+1;i<=n+m;i++) val[i]=mn[i]=i-n;
}

int main()
{
    int T,Q,tmp;
    for(T=read();T;T--)
    {
        n=read();m=read();Q=read();Init();
        for(int i=1;i<=m;i++) e[i][0]=read(),e[i][1]=read();
        for(int i=1;i<=m;i++) insert(rt[i],rt[i-1],0,m,Link(i));
        while(Q--)
        {
            int l=read(),r=read();
            int t=query(rt[l-1],rt[r],0,m,l-1);
            print(n-t);flush();
        }
    }
    flush();
    return 0;
}