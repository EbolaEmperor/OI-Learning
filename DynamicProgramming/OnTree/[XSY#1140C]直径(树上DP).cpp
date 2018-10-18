#include<bits/stdc++.h>
#define PB push_back
#define MP make_pair
#define FR first
#define SE second
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

typedef long long LL;
const LL INF=1ll<<60;
const int N=300010;
struct Edge{int to,next;} e[N<<1];
struct edge
{
    int u,y,v;
    edge(int a=0,int b=0,int c=0):u(a),y(b),v(c){}
};
int h[N],sum=0,n,m;
vector<edge> out[N];
int rt[N],dep[N],sz[N];
int top[N],fa[N],hson[N];
int diam[N],endp[N][2];
pair<int,int> mxlen[N];
pair<int,int> cur;
LL curdis;

void add_edge(int u,int v)
{
    e[++sum].to=v;
    e[sum].next=h[u];
    h[u]=sum;
}

void dfs(int u,int last)
{
    int mx=0;
    dep[u]=dep[last]+1;
    diam[u]=0;sz[u]=1;
    endp[u][0]=endp[u][1]=u;
    mxlen[u]=MP(0,u);
    for(int tmp=h[u];tmp;tmp=e[tmp].next)
    {
        int v=e[tmp].to;
        if(v==last) continue;
        dfs(v,u);sz[u]+=sz[v];fa[v]=u;
        if(sz[v]>mx) mx=sz[v],hson[u]=v;
        if(mxlen[u].FR+mxlen[v].FR+1>diam[u])
        {
            diam[u]=mxlen[u].FR+mxlen[v].FR+1;
            endp[u][0]=mxlen[u].SE;
            endp[u][1]=mxlen[v].SE;
        }
        if(diam[v]>diam[u])
        {
            diam[u]=diam[v];
            endp[u][0]=endp[v][0];
            endp[u][1]=endp[v][1];
        }
        if(mxlen[v].FR+1>mxlen[u].FR)
            mxlen[u]=MP(mxlen[v].FR+1,mxlen[v].SE);
    }
}

void dfs2(int u,int tp)
{
    top[u]=tp;
    if(hson[u]) dfs2(hson[u],tp);
    for(int tmp=h[u];tmp;tmp=e[tmp].next)
        if(e[tmp].to!=fa[u]&&e[tmp].to!=hson[u])
            dfs2(e[tmp].to,e[tmp].to);
}

int LCA(int u,int v)
{
    while(top[u]!=top[v])
    {
        if(dep[top[u]]<dep[top[v]]) swap(u,v);
        u=fa[top[u]];
    }
    if(dep[u]>dep[v]) swap(u,v);
    return u;
}

int getdis(int u,int v){return dep[u]+dep[v]-2*dep[LCA(u,v)];}

void update(int x,int u,LL dis)
{
    if(dis<=curdis) return;
    curdis=dis;
    cur=MP(x,u);
}

void gao(int x,int u,int last,LL dis)
{
    update(x,endp[rt[x]][0],dis+getdis(u,endp[rt[x]][0]));
    update(x,endp[rt[x]][1],dis+getdis(u,endp[rt[x]][1]));
    for(edge e : out[x])
    {
        int o=e.u,y=e.y,v=e.v;
        if(y==last) continue;
        gao(y,v,x,dis+getdis(u,o)+1);
    }
}

int main()
{
    int u,v,x,y;
    n=read();m=read();
    for(int i=1;i<n;i++)
    {
        u=read();v=read();
        add_edge(u,v);
        add_edge(v,u);
    }
    dfs(1,0);dfs2(1,1);
    for(int i=1;i<=m;i++) rt[i]=read();
    for(int i=1;i<m;i++)
    {
        x=read();u=read();
        y=read();v=read();
        out[x].PB(edge(u,y,v));
        out[y].PB(edge(v,x,u));
    }
    curdis=-INF;
    gao(1,rt[1],0,0);
    curdis=-INF;
    gao(cur.FR,cur.SE,0,0);
    printf("%lld\n",curdis+1);
    return 0;
}