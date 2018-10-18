#include<bits/stdc++.h>
#define INF 0x7fffffff
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
    inline void OK(){putc('O');putc('K');putc('\n');}
}

using namespace IO;
const int N=400010;
struct Edge{int to,next;} e[N];
int h[N],sum=0,n,m,Q;
int in[N],out[N],dfc=0;
int mxd[N<<2],cur[N<<2];
int fa[20][N],mxe[20][N];
int dep[N],val[N],f[N];
int tag[N],rt[N],rts=0;
int crl[N];

void add_edge(int u,int v)
{
    e[++sum].to=v;
    e[sum].next=h[u];
    h[u]=sum;
}

void build(int u)
{
    if(f[u]==0){rt[++rts]=u;tag[u]=2;return;}
    if(tag[f[u]]==1)
    {
        int x=u;
        for(int t=f[u];t!=u;t=f[t])
        {
            crl[t]=++n;
            val[n]=val[t];
            add_edge(n,x);
            f[x]=n;x=f[x];
        }
        crl[u]=++n;add_edge(n,x);f[x]=n;
        rt[++rts]=n;tag[u]=2;return;
    }
    tag[u]=1;
    if(!tag[f[u]]) build(f[u]);
    add_edge(f[u],u);
    tag[u]=2;
}

void dfs(int u)
{
    in[u]=++dfc;
    for(int i=1;i<=18;i++)
    {
        fa[i][u]=fa[i-1][fa[i-1][u]];
        mxe[i][u]=max(mxe[i-1][u],mxe[i-1][fa[i-1][u]]);
    }
    for(int t=h[u];t;t=e[t].next)
    {
        int v=e[t].to;
        dep[v]=dep[u]+1;
        mxe[0][v]=val[v];
        fa[0][v]=u;dfs(v);
    }
    out[u]=dfc;
}

void modify(int o,int l,int r,int nl,int nr,int d)
{
    if(l>=nl&&r<=nr)
    {
        if(Q<cur[o]||d>mxd[o])
            mxd[o]=d,cur[o]=Q;
        return;
    }
    int mid=(l+r)/2;
    if(nl<=mid) modify(o<<1,l,mid,nl,nr,d);
    if(nr>mid) modify(o<<1|1,mid+1,r,nl,nr,d);
}
 
int query(int o,int l,int r,int k)
{
    int res=0;
    if(cur[o]==Q) res=max(res,mxd[o]);
    if(l==r) return res;
    int mid=(l+r)/2;
    if(k<=mid) res=max(res,query(o<<1,l,mid,k));
    else res=max(res,query(o<<1|1,mid+1,r,k));
    return res;
}
 
int query(int x)
{
    int len=query(1,1,n,in[x]),res=-1;
    if(len==0) return INF;
    else len=dep[x]-len;
    for(int i=18;i>=0;i--)
        if(len&(1<<i))
        {
            res=max(res,mxe[i][x]);
            x=fa[i][x];
        }
    return res;
}

int main()
{
    int fk=n=read();m=read();
    for(int i=1;i<=m;i++)
    {
        int u=read(),v=read();
        if(u==v) continue;
        f[v]=u;val[v]=i;
    }
    for(int i=1;i<=fk;i++) if(!tag[i]) build(i);
    for(int i=1;i<=rts;i++) dep[rt[i]]=1,dfs(rt[i]);
    for(Q=read();Q;Q--)
    {
        int numt=read();
        for(int i=1;i<=numt;i++)
        {
            int u=read();
            modify(1,1,n,in[u],out[u],dep[u]);
            if(crl[u]) modify(1,1,n,in[crl[u]],out[crl[u]],dep[crl[u]]);
        }
        int numf=read(),ans=INF;
        for(int i=1;i<=numf;i++)
            ans=min(ans,query(read()));
        if(ans==INF) OK();
        else print(ans);
        flush();fflush(stdout);
    }
    flush();
    return 0;
}