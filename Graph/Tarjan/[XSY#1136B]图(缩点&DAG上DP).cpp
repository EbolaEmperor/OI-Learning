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

inline void upmin(int &x,const int &y){if(y<x) x=y;}
inline void upmax(int &x,const int &y){if(y>x) x=y;}

const int N=100010,M=1000010;
struct Edge{int to,next;} e[M];
int h[N],sum=0,n,m;
int dfn[N],low[N],clk=0;
int scc[N],val[N],tot=0;
int froms[M],tos[M],deg[N];
int nc[N],mc[N];
stack<int> stk;
int dp[N];

void add_edge(int u,int v)
{
    e[++sum].to=v;
    e[sum].next=h[u];
    h[u]=sum;
}

void Tarjan(int u)
{
    dfn[u]=low[u]=++clk;stk.push(u);
    for(int tmp=h[u];tmp;tmp=e[tmp].next)
        if(!dfn[e[tmp].to])
        {
            Tarjan(e[tmp].to);
            upmin(low[u],low[e[tmp].to]);
        }
        else if(!scc[e[tmp].to]) upmin(low[u],dfn[e[tmp].to]);
    if(dfn[u]==low[u])
    {
        int o;tot++;
        do{
            o=stk.top();
            scc[o]=tot;
            stk.pop();
        }while(o!=u);
    }
}

void TopoSort()
{
    queue<int> q;
    for(int i=1;i<=tot;i++)
        if(!deg[i]) q.push(i);
    while(!q.empty())
    {
        int u=q.front();q.pop();dp[u]+=val[u];
        for(int tmp=h[u];tmp;tmp=e[tmp].next)
        {
            int v=e[tmp].to;
            upmax(dp[v],dp[u]);
            if(!--deg[v]) q.push(v);
        }
    }
}

int main()
{
    int u,v;
    n=read();m=read();
    for(int i=1;i<=m;i++)
    {
        froms[i]=u=read();
        tos[i]=v=read();
        add_edge(u,v);
    }
    for(int i=1;i<=n;i++)
        if(!dfn[i]) Tarjan(i);
    for(int u=1;u<=n;nc[scc[u]]++,u++)
        for(int tmp=h[u];tmp;tmp=e[tmp].next)
            if(scc[u]==scc[e[tmp].to]) mc[scc[u]]++;
    bool falun=0;
    for(int i=1;i<=tot;i++)
        if(nc[i]>1&&mc[i]>nc[i]){puts("-1");return 0;}
        else if(nc[i]==mc[i]) val[i]=1,falun=1;
    if(!falun){puts("0");return 0;}
    sum=0;memset(h,0,sizeof(h));
    for(int i=1;i<=m;i++)
        if(scc[froms[i]]!=scc[tos[i]])
        {
            add_edge(scc[froms[i]],scc[tos[i]]);
            deg[scc[tos[i]]]++;
        }
    TopoSort();
    int ans=0;
    for(int i=1;i<=tot;i++)
        upmax(ans,dp[i]);
    printf("%d\n",ans-1);
    return 0;
}