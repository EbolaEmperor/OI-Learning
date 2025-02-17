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
typedef pair<int,int> pii;
const int N=100010,B=315;
struct Edge{int to,capa,next;} e[N<<1];
int h[N],sum=0,n,ans[N];
int fa[18][N],dis[N],dep[N];
int jump[18][N];

struct Query
{
    int s,t,p,id;
    Query(int _s=0,int _t=0,int _p=0,int _id=0):s(_s),t(_t),p(_p),id(_id){}
    bool operator < (const Query &b) const{return p<b.p;}
} qs[N];

void add_edge(int u,int v,int w)
{
    e[++sum].to=v;
    e[sum].capa=w;
    e[sum].next=h[u];
    h[u]=sum;
}

void dfs(int u,int la)
{
    for(int i=1;i<=16;i++)
        fa[i][u]=fa[i-1][fa[i-1][u]];
    for(int t=h[u];t;t=e[t].next)
    {
        int v=e[t].to;
        if(v==la) continue;
        dis[v]=dis[u]+e[t].capa;
        dep[v]=dep[u]+1;
        fa[0][v]=u;dfs(v,u);
    }
}

int LCA(int x,int y)
{
    if(dep[x]<dep[y]) swap(x,y);
    for(int i=16;i>=0;i--)
        if(dep[fa[i][x]]>=dep[y])
            x=fa[i][x];
    if(x==y) return x;
    for(int i=16;i>=0;i--)
        if(fa[i][x]!=fa[i][y])
            x=fa[i][x],y=fa[i][y];
    return fa[0][x];
}

int SingleJump(int x,int p)
{
    int tmp=dis[x];
    for(int i=16;i>=0;i--)
        if(tmp-dis[fa[i][x]]<=p)
            x=fa[i][x];
    return x;
}

pii LargeJump(int x,int aim,int p)
{
    int step=0,rest=0;
    while(x!=aim)
    {
        int y=SingleJump(x,p);
        if(dis[y]>dis[aim]) x=y,step++;
        else rest=dis[x]-dis[aim],x=aim;
    }
    return pii(step,rest);
}

int SolveLarge(int s,int t,int p)
{
    if(s==t) return 0;
    int lca=LCA(s,t);
    pii tmp1=LargeJump(s,lca,p);
    pii tmp2=LargeJump(t,lca,p);
    int ans=tmp1.FR+tmp2.FR;
    return (tmp1.SE+tmp2.SE<=p)?ans+1:ans+2;
}

void Rebuild(int p)
{
    for(int i=1;i<=n;i++)
        jump[0][i]=SingleJump(i,p);
    for(int k=1;k<=16;k++)
        for(int i=1;i<=n;i++)
            jump[k][i]=jump[k-1][jump[k-1][i]];
}

pii SmallJump(int x,int aim,int p)
{
    int step=0;
    for(int i=16;i>=0;i--)
        if(dis[jump[i][x]]>dis[aim])
            x=jump[i][x],step|=1<<i;
    return pii(step,dis[x]-dis[aim]);
}

int SolveSmall(int s,int t,int p)
{
    if(s==t) return 0;
    int lca=LCA(s,t);
    pii tmp1=SmallJump(s,lca,p);
    pii tmp2=SmallJump(t,lca,p);
    int ans=tmp1.FR+tmp2.FR;
    return tmp1.SE+tmp2.SE<=p?ans+1:ans+2;
}

int main()
{
    n=read();
    for(int i=1;i<n;i++)
    {
        int u=read(),v=read(),w=read();
        add_edge(u,v,w);
        add_edge(v,u,w);
    }
    dep[1]=1;dfs(1,0);
    int Q=read(),cnt=0;
    for(int i=1;i<=Q;i++)
    {
        int s=read(),t=read(),p=read();
        if(p<=B) qs[++cnt]=Query(s,t,p,i);
        else ans[i]=SolveLarge(s,t,p);
    }
    sort(qs+1,qs+1+cnt);
    for(int i=1;i<=cnt;i++)
    {
        if(qs[i].p!=qs[i-1].p) Rebuild(qs[i].p);
        ans[qs[i].id]=SolveSmall(qs[i].s,qs[i].t,qs[i].p);
    }
    for(int i=1;i<=Q;i++) print(ans[i]);
    flush();
    return 0;
}