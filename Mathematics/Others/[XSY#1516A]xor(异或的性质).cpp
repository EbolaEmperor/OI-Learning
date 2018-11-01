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
const int N=2000010;
struct Edge{int to,capa;};
vector<Edge> G[N];
int n,m,K,fa[N],val[N];
int ffa[N],ans[N];
bool vis[N];

int find(int x){return ffa[x]==x?x:ffa[x]=find(ffa[x]);}

void buildTree(int u)
{
    vis[u]=1;
    for(Edge e : G[u])
    {
        if(vis[e.to]) continue;
        fa[e.to]=u;
        val[e.to]=val[u]^e.capa;
        buildTree(e.to);
    }
}

bool check(int u)
{
    for(Edge e : G[u])
    {
        if(fa[e.to]==u||fa[u]==e.to) continue;
        if((val[u]^e.capa)!=val[e.to]) return 0;
    }
    for(Edge e : G[u])
    {
        if(fa[e.to]!=u) continue;
        if(!check(e.to)) return 0;
    }
    return 1;
}

void getans(int u)
{
    vis[u]=1;
    for(Edge e : G[u])
    {
        if(vis[e.to]) continue;
        ans[e.to]=ans[u]^e.capa;
        getans(e.to);
    }
}

int main()
{
    n=read();m=read();K=read();
    for(int i=1;i<=n;i++) ffa[i]=i;
    for(int i=1,u,v,w;i<=m;i++)
    {
        u=read();v=read();w=read();
        G[u].push_back({v,w});
        G[v].push_back({u,w});
        u=find(u);v=find(v);
        if(u==v) continue;
        if(u>v) swap(u,v);
        ffa[v]=u;
    }
    for(int i=1;i<=n;i++)
    {
        if(ffa[i]!=i) continue;
        buildTree(i);
        if(!check(i)) return puts("-1"),0;
    }
    memset(vis,0,sizeof(vis));
    for(int i=n;i>=1;i--)
    {
        if(ffa[i]!=i) continue;
        ans[i]=K-1;
        getans(i);
        break;
    }
    for(int i=1;i<=n;i++)
    {
        if(ffa[i]!=i||vis[i]) continue;
        ans[i]=0;
        getans(i);
    }
    for(int i=1;i<=n;i++)
        print(ans[i]),putc(' ');
    return flush(),0;
}