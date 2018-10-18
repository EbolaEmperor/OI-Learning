#include<bits/stdc++.h>
using namespace std;

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

const int N=50010;
struct Edge{int to,next;} e[N<<1];
int h[N],sum=0,n;
int dep[N],mxdep[N];
int lson[N],top[N],fa[N];
int stf[N],pf,stg[N],pg;
long long F[N],G[N<<1],ans;

inline int getlen(int x){return mxdep[x]-dep[x]+1;}
inline long long &f(int x,int y){return F[stf[top[x]]+dep[x]-dep[top[x]]+y];}
inline long long &g(int x,int y){return G[stg[top[x]]-dep[x]+dep[top[x]]+y];}

void add_edge(int u,int v)
{
    e[++sum].to=v;
    e[sum].next=h[u];
    h[u]=sum;
}

void dfs1(int u,int la)
{
    mxdep[u]=dep[u];
    for(int tmp=h[u];tmp;tmp=e[tmp].next)
    {
        int v=e[tmp].to;
        if(v==la) continue;
        dep[v]=dep[u]+1;
        fa[v]=u;dfs1(v,u);
        if(mxdep[v]>mxdep[u])
        {
            mxdep[u]=mxdep[v];
            lson[u]=v;
        }
    }
}

void dfs2(int u,int tp)
{
    top[u]=tp;
    if(u==tp)
    {
        int len=getlen(u);
        stf[u]=pf;
        stg[u]=pg+len;
        pf+=len;
        pg+=len<<1;
    }
    if(lson[u]) dfs2(lson[u],tp);
    for(int tmp=h[u];tmp;tmp=e[tmp].next)
        if(e[tmp].to!=fa[u]&&e[tmp].to!=lson[u])
            dfs2(e[tmp].to,e[tmp].to);
}

void dp(int u)
{
    f(u,0)=1;
    if(lson[u]) dp(lson[u]),ans+=g(u,0);
    for(int tmp=h[u];tmp;tmp=e[tmp].next)
    {
        int v=e[tmp].to;
        if(v==fa[u]||v==lson[u]) continue;
        dp(v);int len=getlen(v);
        for(int i=1;i<=len;i++) ans+=g(u,i)*f(v,i-1);
        for(int i=1;i<len;i++) ans+=g(v,i)*f(u,i-1);
        for(int i=1;i<=len;i++) g(u,i)+=f(u,i)*f(v,i-1);
        for(int i=1;i<=len-2;i++) g(u,i)+=g(v,i+1);
        for(int i=1;i<=len;i++) f(u,i)+=f(v,i-1);
    }
}

void clear()
{
    sum=pf=pg=0;ans=0;
    memset(h,0,sizeof(h));
    memset(F,0,sizeof(F));
    memset(G,0,sizeof(G));
    memset(lson,0,sizeof(lson));
}

int main()
{
    int u,v;
    while(n=read())
    {
        clear();
        for(int i=1;i<n;i++)
        {
            u=read();v=read();
            add_edge(u,v);
            add_edge(v,u);
        }
        dfs1(1,0);dfs2(1,1);dp(1);
        printf("%lld\n",ans);
    }
    return 0;
}