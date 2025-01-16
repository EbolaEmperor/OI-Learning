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

using IO::read;
using IO::print;
using IO::putc;
const int N=50010;
struct Edge{int to,next;} e[N<<1];
int h[N],sum=0,n,m,tot;
int dep[N],fa[N],fuck[N];
int ffa[N],sz[N];
bool spd[N];

int find(int x){return ffa[x]==x?x:ffa[x]=find(ffa[x]);}

void add_edge(int u,int v)
{
    e[++sum].to=v;
    e[sum].next=h[u];
    h[u]=sum;
}

void getpath(int x,int y)
{
    static int path1[N],path2[N];
    int tot1=0,tot2=0;
    while(x!=y)
    {
        if(dep[x]>dep[y]) path1[++tot1]=x,x=fa[x];
        else path2[++tot2]=y,y=fa[y];
    }
    path1[++tot1]=x;
    print(tot1+tot2-1);putc(' ');
    for(int i=1;i<=tot1;i++) print(path1[i]),putc(' ');
    for(int i=tot2;i>=1;i--) print(path2[i]),putc(' ');
    putc('\n');
}

void dfs(int u,int la)
{
    fuck[u]=spd[u]?u:0;
    for(int t=h[u];t;t=e[t].next)
    {
        int v=e[t].to;
        if(v==la) continue;
        dep[v]=dep[u]+1;
        fa[v]=u;dfs(v,u);
        if(!fuck[v]) continue;
        if(!fuck[u]) fuck[u]=fuck[v];
        else getpath(fuck[u],fuck[v]),fuck[u]=0;
    }
}

int main()
{
    n=read();m=read();tot=read();
    for(int i=1;i<=n;i++) ffa[i]=i;
    for(int i=1,u,v;i<=m;i++)
    {
        u=read();v=read();
        if(find(u)==find(v)) continue;
        ffa[find(u)]=find(v);
        add_edge(u,v);
        add_edge(v,u);
    }
    for(int i=1,x;i<=tot;i++)
        x=read(),spd[x]=1,sz[find(x)]++;
    int ans=0;
    for(int i=1;i<=n;i++)
        if(ffa[i]==i) ans+=sz[i]/2;
    print(ans);putc('\n');
    for(int i=1;i<=n;i++)
        if(ffa[i]==i) dfs(i,0);
    IO::flush();
    return 0;
}