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
        while(c!='O'&&c!='q') c=Get();
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
    }
    inline void printd(int d,double x)
    {
        long long t=(long long)floor(x);
        print(t);putc('.');x-=t;
        while(d--)
        {
            double y=x*10;x*=10;
            int c=(int)floor(y);
            putc(c+'0');x-=floor(y);
        }
        putc('\n');
    }
}

using namespace IO;
typedef long long LL;
const int N=100010;
struct Edge{int to,next;} e[N<<1];
int h[N],esum=0,n,fa[N],dep[N];
int in[N],out[N],idx[N],dfc=0;
LL sum[N<<2];int tag[N<<2];
int ch[N][2];

void add_edge(int u,int v)
{
    e[++esum].to=v;
    e[esum].next=h[u];
    h[u]=esum;
}
void dfs(int u)
{
    in[u]=++dfc;idx[dfc]=u;
    for(int t=h[u];t;t=e[t].next)
    {
        int v=e[t].to;
        if(v==fa[u]) continue;
        dep[v]=dep[u]+1;
        fa[v]=u;dfs(v);
    }
    out[u]=dfc;
}

void Build(int o,int l,int r)
{
    if(l==r){sum[o]=dep[idx[l]];return;}
    int mid=(l+r)/2;
    Build(o<<1,l,mid);
    Build(o<<1|1,mid+1,r);
    sum[o]=sum[o<<1]+sum[o<<1|1];
}
void Add(int o,int l,int r,int nl,int nr,int k)
{
    sum[o]+=k*(nr-nl+1);
    if(l>=nl&&r<=nr){tag[o]+=k;return;}
    int mid=(l+r)/2;
    if(nr<=mid) Add(o<<1,l,mid,nl,nr,k);
    else if(nl>mid) Add(o<<1|1,mid+1,r,nl,nr,k);
    else Add(o<<1,l,mid,nl,mid,k),Add(o<<1|1,mid+1,r,mid+1,nr,k);
}
LL Query(int o,int l,int r,int nl,int nr)
{
    if(l>=nl&&r<=nr) return sum[o];
    int mid=(l+r)/2;
    LL res=1ll*tag[o]*(nr-nl+1);
    if(nr<=mid) return res+Query(o<<1,l,mid,nl,nr);
    else if(nl>mid) return res+Query(o<<1|1,mid+1,r,nl,nr);
    else return res+Query(o<<1,l,mid,nl,mid)+Query(o<<1|1,mid+1,r,mid+1,nr);
}

bool nrt(int x){return ch[fa[x]][0]==x||ch[fa[x]][1]==x;}
void rotate(int x)
{
    int y=fa[x],z=fa[y];
    int k=(ch[y][1]==x),w=ch[x][k^1];
    if(nrt(y)) ch[z][ch[z][1]==y]=x;
    ch[y][k]=w;ch[x][k^1]=y;
    if(w) fa[w]=y;
    fa[y]=x;fa[x]=z;
}
void splay(int x)
{
    int y,z;
    while(nrt(x))
    {
        y=fa[x],z=fa[y];
        if(nrt(y)) rotate((ch[y][0]==x)^(ch[z][0]==y)?x:y);
        rotate(x);
    }
}

#define rs ch[x][1]
void gao(int x,int k)
{
    for(;ch[x][0];x=ch[x][0]);
    Add(1,1,n,in[x],out[x],k);
}
void access(int x)
{
    for(int y=0;x;y=x,x=fa[x])
    {
        splay(x);
        if(rs) gao(rs,1);
        rs=y;if(rs) gao(rs,-1);
    }
}

int main()
{
    n=read();
    for(int i=1;i<n;i++)
    {
        int u=read()+1;
        int v=read()+1;
        add_edge(u,v);
        add_edge(v,u);
    }
    dfs(1);Build(1,1,n);
    for(int Q=read();Q;Q--)
    {
        char opt=readc();
        int u=read()+1;
        if(opt=='O') access(u);
        else printd(7,(double)Query(1,1,n,in[u],out[u])/(out[u]-in[u]+1));
    }
    flush();
    return 0;
}