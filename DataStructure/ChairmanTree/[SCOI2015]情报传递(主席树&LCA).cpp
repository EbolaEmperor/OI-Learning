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
const int N=200010;
struct Edge{int to,next;} e[N];
struct Query{int op,x,y,c;} q[N];
int h[N],esum=0,n,val[N],root,Q;
int fa[N],hson[N];
int top[N],sz[N],dep[N];
int rt[N],sum[N*20],tot=0;
int lc[N*20],rc[N*20];

void add_edge(int u,int v)
{
    e[++esum].to=v;
    e[esum].next=h[u];
    h[u]=esum;
}

void dfs1(int u)
{
    sz[u]=1;
    for(int t=h[u];t;t=e[t].next)
    {
        int v=e[t].to;
        dep[v]=dep[u]+1;
        dfs1(v);sz[u]+=sz[v];
        if(sz[v]>sz[hson[u]]) hson[u]=v;
    }
}

void dfs2(int u,int tp)
{
    top[u]=tp;
    if(hson[u]) dfs2(hson[u],tp);
    for(int t=h[u];t;t=e[t].next)
        if(e[t].to!=fa[u]&&e[t].to!=hson[u])
            dfs2(e[t].to,e[t].to);
}

int getlca(int x,int y)
{
    while(top[x]!=top[y])
    {
        if(dep[top[x]]<dep[top[y]]) swap(x,y);
        x=fa[top[x]];
    }
    return dep[x]<dep[y]?x:y;
}

void insert(int &o,int p,int l,int r,int x)
{
    sum[o=++tot]=sum[p]+1;
    lc[o]=lc[p];rc[o]=rc[p];
    if(l==r) return;
    int mid=(l+r)/2;
    if(x<=mid) insert(lc[o],lc[p],l,mid,x);
    else insert(rc[o],rc[p],mid+1,r,x);
}

int query(int L,int R,int l,int r,int x)
{
    if(l==r) return sum[R]-sum[L];
    int mid=(l+r)/2;
    if(x<=mid) return query(lc[L],lc[R],l,mid,x);
    return sum[lc[R]]-sum[lc[L]]+query(rc[L],rc[R],mid+1,r,x);
}

void build(int u)
{
    insert(rt[u],rt[fa[u]],1,Q,val[u]);
    for(int t=h[u];t;t=e[t].next) build(e[t].to);
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++)
    {
        fa[i]=read();
        if(!fa[i]) root=i;
        else add_edge(fa[i],i);
    }
    Q=read();
    for(int i=1;i<=n;i++) val[i]=Q;
    for(int i=1;i<=Q;i++)
    {
        q[i].op=read();q[i].x=read();
        if(q[i].op==2) val[q[i].x]=i;
        else q[i].y=read(),q[i].c=read();
    }
    dep[root]=1;dfs1(root);
    dfs2(root,root);
    build(root);
    for(int i=1;i<=Q;i++)
    {
        if(q[i].op==2) continue;
        int x=q[i].x,y=q[i].y,c=q[i].c,lca=getlca(x,y);
        print(dep[x]+dep[y]-2*dep[lca]+1);putc(' ');
        if(i-c-1<=0){putc('0');putc('\n');continue;}
        int ans=query(rt[lca],rt[x],1,Q,i-c-1);
        ans+=query(rt[lca],rt[y],1,Q,i-c-1);
        ans+=(val[lca]<i-c);
        print(ans);putc('\n');
    }
    flush();
    return 0;
}