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
const int N=100010;
struct Edge{int to,next;} e[N<<1];
int h[N],esum=0,n,m;
int fa[N],val[N],sz[N];
int root,sum=0,msz[N],ffa[N];
int top[N],hson[N],dep[N];
bool done[N];

int upmax(int &x,const int &y){if(y>x) x=y;}

int* newnode(int len)
{
    static int mmp[N*30],*pos=mmp;
    int* res=pos;pos=pos+len;
    return res;
}

struct BIT
{
    int *b,len;
    void creat(int x){len=x+2;b=newnode(x+3);}
    inline int lowbit(const int &x){return x&-x;}
    void add(int p,int x){for(p++;p<=len;p+=lowbit(p)) b[p]+=x;}
    int sum(int p){int res=0;for(p=min(p+1,len);p;p-=lowbit(p)) res+=b[p];return res;}
} bit[N][2];

void add_edge(int u,int v)
{
    e[++esum].to=v;
    e[esum].next=h[u];
    h[u]=esum;
}

void dfs(int u,int la)
{
    sz[u]=1;
    for(int t=h[u];t;t=e[t].next)
    {
        int v=e[t].to;
        if(v==la) continue;
        dep[v]=dep[u]+1;
        fa[v]=u;dfs(v,u);
        sz[u]+=sz[v];
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

int lca(int u,int v)
{
    while(top[u]!=top[v])
    {
        if(dep[top[u]]<dep[top[v]]) swap(u,v);
        u=fa[top[u]];
    }
    return dep[u]<dep[v]?u:v;
}

int dis(int x,int y){return dep[x]+dep[y]-2*dep[lca(x,y)];}

void find(int u,int la)
{
    sz[u]=1;msz[u]=0;
    for(int t=h[u];t;t=e[t].next)
    {
        int v=e[t].to;
        if(v==la||done[v]) continue;
        find(v,u);sz[u]+=sz[v];
        upmax(msz[u],sz[v]);
    }
    upmax(msz[u],sum-sz[u]);
    if(msz[u]<msz[root]) root=u;
}

void build(int rt,int d,int u,int la,int dis)
{
    bit[rt][d].add(dis,val[u]);
    for(int t=h[u];t;t=e[t].next)
    {
        int v=e[t].to;
        if(done[v]||v==la) continue;
        build(rt,d,v,u,dis+1);
    }
}

void solve(int u)
{
    bit[u][0].creat(msz[u]);
    done[u]=1;build(u,0,u,0,0);
    for(int t=h[u];t;t=e[t].next)
    {
        int v=e[t].to;
        if(done[v]) continue;
        sum=sz[v];root=0;find(v,u);
        bit[root][1].creat(msz[root]<<1);
        build(root,1,v,u,1);
        ffa[root]=u;solve(root);
    }
}

int query(int x,int k)
{
    int ans=bit[x][0].sum(k);
    for(int u=x;ffa[u];u=ffa[u])
    {
        int dist=dis(x,ffa[u]);
        if(dist>k) continue;
        ans+=bit[ffa[u]][0].sum(k-dist);
        ans-=bit[u][1].sum(k-dist);
    }
    return ans;
}

void modify(int x,int k)
{
    int delta=k-val[x];val[x]=k;
    bit[x][0].add(0,delta);
    for(int u=x;ffa[u];u=ffa[u])
    {
        int dist=dis(x,ffa[u]);
        if(dist<0) continue;
        bit[ffa[u]][0].add(dist,delta);
        bit[u][1].add(dist,delta);
    }
}

int main()
{
    int opt,u,v,ans=0;
    n=read();m=read();
    for(int i=1;i<=n;i++) val[i]=read();
    for(int i=1;i<n;i++)
    {
        u=read();v=read();
        add_edge(u,v);
        add_edge(v,u);
    }
    dep[1]=1;dfs(1,0);dfs2(1,1);
    msz[0]=n+1;sum=n;find(1,0);solve(root);
    while(m--)
    {
        opt=read();u=read()^ans;v=read()^ans;
        if(opt==0) print(ans=query(u,v));
        else modify(u,v);
    }
    flush();
    return 0;
}