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
const int N=500010;
int fa[N],dep[N],n,m;
int val[N];
bool tag[N];

int find(int x){return fa[x]==x?x:find(fa[x]);}

void merge(int x,int y,int k)
{
    x=find(x);y=find(y);
    if(dep[x]>dep[y]) swap(x,y);
    fa[x]=y;val[x]=k;
    dep[y]=max(dep[y],dep[x]+1);
}

int query(int x,int y)
{
    int u=x,lca=y;
    if(find(x)!=find(y)) return 0;
    tag[u]=1;while(fa[u]!=u) u=fa[u],tag[u]=1;
    while(!tag[lca]) lca=fa[lca];
    int ans=0;u=x;
    while(x!=lca) ans=max(ans,val[x]),x=fa[x];
    while(y!=lca) ans=max(ans,val[y]),y=fa[y];
    tag[u]=0;while(fa[u]!=u) u=fa[u],tag[u]=0;
    return ans;
}

int main()
{
    int ans=0,opt,u,v,cnt=0;
    n=read();m=read();
    for(int i=1;i<=n;i++) fa[i]=i;
    for(int i=1;i<=m;i++)
    {
        opt=read();u=read()^ans;v=read()^ans;
        if(opt==0) merge(u,v,++cnt);
        else print(ans=query(u,v));
    }
    return flush(),0;
}