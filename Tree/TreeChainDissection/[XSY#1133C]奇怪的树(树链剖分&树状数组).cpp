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
    template <class __>inline void print(__ x)
    {
        if(!x) putc('0');
        while(x) qu[++qr]=x%10+'0',x/=10;
        while(qr) putc(qu[qr--]);
        putc('\n');
    }
}

using namespace IO;
const int N=200010;
typedef long long LL;
struct Edge{int to,next;} e[N<<1];
int h[N],sum=0,n,m;
int dep[N],sz[N];
int fa[N],top[N],hson[N];
int in[N],out[N],dfc=0;
bool blackpos[2],col[N];
int num[N][2][2];
template<typename __> struct BIT
{
    __ c[N];
    inline int lowbit(const int &x){return x&-x;}
    void add(int p,__ x){for(int i=p;i<=n;i+=lowbit(i)) c[i]+=x;}
    __ sum(int p){__ res=0;for(int i=p;i>0;i-=lowbit(i)) res+=c[i];return res;}
    __ sum(int l,int r){return sum(r)-sum(l-1);}
};
BIT<int> cnt[2][2];
BIT<LL> ans[2][2];

void add_edge(int u,int v)
{
    e[++sum].to=v;
    e[sum].next=h[u];
    h[u]=sum;
}

void dfs1(int u,int la)
{
    sz[u]=1;int mx=0;
    num[u][dep[u]&1][col[u]]++;
    for(int tmp=h[u];tmp;tmp=e[tmp].next)
    {
        int v=e[tmp].to;
        if(v==la) continue;
        dep[v]=dep[u]+1;
        dfs1(v,u);fa[v]=u;
        for(int i=0;i<2;i++)
            for(int j=0;j<2;j++)
                num[u][i][j]+=num[v][i][j];
        sz[u]+=sz[v];
        if(sz[v]>mx) mx=sz[v],hson[u]=v;
    }
}

void dfs2(int u,int tp)
{
    in[u]=++dfc;top[u]=tp;
    if(hson[u]) dfs2(hson[u],tp);
    for(int tmp=h[u];tmp;tmp=e[tmp].next)
        if(e[tmp].to!=fa[u]&&e[tmp].to!=hson[u])
            dfs2(e[tmp].to,e[tmp].to);
    out[u]=dfc;
    cnt[dep[u]&1][col[u]].add(in[u],1);
    for(int i=0;i<2;i++)
        for(int j=0;j<2;j++)
            ans[i][j].add(in[u],1ll*u*(num[u][i][j]-num[hson[u]][i][j]));
}

int main()
{
    n=read();m=read();
    for(int i=1;i<=n;i++) col[i]=read();
    for(int i=1;i<n;i++)
    {
        int u=read(),v=read();
        add_edge(u,v);
        add_edge(v,u);
    }
    dfs1(1,0);dfs2(1,1);
    blackpos[0]=blackpos[1]=1;
    while(m--)
    {
        int ty=read(),a=read();
        if(ty==1) blackpos[dep[a]&1^1]^=1;
        if(ty==2)
        {
            int odd=dep[a]&1,x=a;
            cnt[odd][col[a]].add(in[a],-1);
            cnt[odd][col[a]^1].add(in[a],1);
            while(a)
            {
                ans[odd][col[x]].add(in[a],-a);
                ans[odd][col[x]^1].add(in[a],a);
                a=fa[top[a]];
            }
            col[x]^=1;
        }
        if(ty==3)
        {
            LL res=1ll*a*(cnt[0][blackpos[0]].sum(in[a],out[a])+cnt[1][blackpos[1]].sum(in[a],out[a]));
            for(;a;a=fa[a])
            {
                if(top[a]!=a) res+=ans[0][blackpos[0]].sum(in[top[a]],in[a]-1)+ans[1][blackpos[1]].sum(in[top[a]],in[a]-1);
                a=top[a];if(fa[a]==0) break;
                res+=1ll*fa[a]*(cnt[0][blackpos[0]].sum(in[fa[a]],out[fa[a]])+cnt[1][blackpos[1]].sum(in[fa[a]],out[fa[a]]));
                res-=1ll*fa[a]*(cnt[0][blackpos[0]].sum(in[a],out[a])+cnt[1][blackpos[1]].sum(in[a],out[a]));
            }
            print(res);
        }
    }
    flush();
    return 0;
}