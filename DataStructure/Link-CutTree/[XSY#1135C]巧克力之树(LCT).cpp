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

typedef pair<int,int> pii;
typedef long long LL;
const int N=100010;
int ch[N][2],fa[N];
bool rev[N];
int sz[N],isz[N];
int stk[N],top=0;
struct Edge{int u,v,w;} edge[N];
LL ans=0;

inline bool operator < (const Edge &a,const Edge &b){return a.w<b.w;}

inline bool nroot(int x){return ch[fa[x]][0]==x||ch[fa[x]][1]==x;}
inline void maintain(int x){sz[x]=sz[ch[x][0]]+sz[ch[x][1]]+isz[x]+1;}
inline void pushr(int x){swap(ch[x][0],ch[x][1]);rev[x]^=1;}
inline void pushdown(int x)
{
    if(!rev[x]) return;
    if(ch[x][0]) pushr(ch[x][0]);
    if(ch[x][1]) pushr(ch[x][1]);
    rev[x]=0;
}

void rotate(int x)
{
    int y=fa[x],z=fa[y];
    int k=(ch[y][1]==x),w=ch[x][k^1];
    if(nroot(y)) ch[z][ch[z][1]==y]=x;
    ch[x][k^1]=y;ch[y][k]=w;
    if(w) fa[w]=y;
    fa[x]=z;fa[y]=x;
    maintain(y);
    maintain(x);
}

void splay(int x)
{
    int y=x,z;
    stk[top=0]=x;
    while(nroot(y)) y=fa[y],stk[++top]=y;
    while(top>=0) pushdown(stk[top--]);
    while(nroot(x))
    {
        y=fa[x];z=fa[y];
        if(nroot(y)) rotate((ch[y][0]==x)^(ch[z][0]==y)?x:y);
        rotate(x);
    }
}

void access(int x)
{
    int y=0;
    while(x)
    {
        splay(x);
        isz[x]-=sz[y];
        isz[x]+=sz[ch[x][1]];
        ch[x][1]=y;
        maintain(x);
        y=x;x=fa[x];
    }
}

inline void makeroot(int x){access(x);splay(x);pushr(x);}
inline void link(int x,int y)
{
    makeroot(x);access(y);splay(y);
    ans+=1ll*sz[x]*sz[y];
    isz[y]+=sz[x];fa[x]=y;
    maintain(y);
}
inline void cut(int x,int y)
{
    makeroot(x);access(y);splay(y);
    ch[y][0]=0;fa[x]=0;
    maintain(y);
}
inline void cut(Edge &e){cut(e.u,e.v);}

int main()
{
    int n=read(),K=read();
    for(int i=1;i<n;i++)
    {
        edge[i].u=read();
        edge[i].v=read();
        edge[i].w=read();
    }
    sort(edge+1,edge+n);
    int pl=1;
    for(int pr=1;pr<n;pr++)
    {
        while(edge[pr].w-edge[pl].w>K) cut(edge[pl++]);
        link(edge[pr].u,edge[pr].v);
    }
    printf("%lld\n",ans);
    return 0;
}