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
const int N=100010;
int n,m,K,ha,deg[N];
int f[55][N];
int topo[N],head,tail;

struct Graph
{
    struct Edge{int to,capa,next;} e[N<<1];
    int h[N],sum,dis[N];bool vis[N];
    void init(){sum=0;memset(h,0,sizeof(h));}
    void add_edge(int u,int v,int w)
    {
        e[++sum].to=v;
        e[sum].capa=w;
        e[sum].next=h[u];
        h[u]=sum;
    }
    void dijkstra(int s)
    {
        priority_queue<pii> q;
        memset(vis,0,sizeof(vis));
        memset(dis,0x3f,sizeof(dis));
        q.push(pii(0,s));dis[s]=0;
        while(!q.empty())
        {
            pii tmp=q.top();q.pop();
            int u=tmp.second,w=-tmp.first;
            if(vis[u]) continue;vis[u]=1;
            for(int t=h[u];t;t=e[t].next)
                if(w+e[t].capa<dis[e[t].to])
                {
                    dis[e[t].to]=w+e[t].capa;
                    q.push(pii(-dis[e[t].to],e[t].to));
                }
        }
    }
} g1,g2;

void TopoSort()
{
    for(int u=1;u<=n;u++)
        for(int t=g1.h[u];t;t=g1.e[t].next)
        {
            int v=g1.e[t].to,w=g1.e[t].capa;
            if(g1.dis[u]+w==g1.dis[v]) deg[v]++;
        }
    head=tail=0;
    for(int u=1;u<=n;u++)
        if(!deg[u]) topo[tail++]=u;
    while(head<tail)
    {
        int u=topo[head++];
        for(int t=g1.h[u];t;t=g1.e[t].next)
        {
            int v=g1.e[t].to,w=g1.e[t].capa;
            if(g1.dis[u]+w!=g1.dis[v]) continue;
            if(!--deg[v]) topo[tail++]=v;
        }
    }
}

bool check()
{
    int mxlen=g1.dis[n]+K;
    for(int u=1;u<=n;u++)
    {
        if(!deg[u]) continue;
        int len=g1.dis[u]+g2.dis[u];
        if(len<=mxlen) return 0;
    }
    return 1;
}

inline void add(int &x,const int &y){x+=y;if(x>=ha) x-=ha;}

int dp()
{
    memset(f,0,sizeof(f));f[0][1]=1;
    for(int k=0;k<=K;k++)
    {
        for(int i=0;i<tail;i++)
        {
            int u=topo[i];
            for(int t=g1.h[u];t;t=g1.e[t].next)
            {
                int v=g1.e[t].to,w=g1.e[t].capa;
                if(g1.dis[u]+w!=g1.dis[v]) continue;
                add(f[k][v],f[k][u]);
            }
        }
        for(int u=1;u<=n;u++)
            for(int t=g1.h[u];t;t=g1.e[t].next)
            {
                int v=g1.e[t].to,w=g1.e[t].capa;
                if(g1.dis[u]+w==g1.dis[v]) continue;
                if(g1.dis[u]+k+w-g1.dis[v]<=K)
                    add(f[g1.dis[u]+k+w-g1.dis[v]][v],f[k][u]);
            }
    }
    int ans=0;
    for(int k=0;k<=K;k++) add(ans,f[k][n]);
    return ans;
}

int main()
{
    for(int T=read();T;T--)
    {
        g1.init();g2.init();
        n=read();m=read();K=read();ha=read();
        for(int i=1;i<=m;i++)
        {
            int u=read(),v=read(),w=read();
            g1.add_edge(u,v,w);
            g2.add_edge(v,u,w);
        }
        g1.dijkstra(1);g2.dijkstra(n);
        memset(deg,0,sizeof(deg));TopoSort();
        if(!check()) puts("-1");
        else printf("%d\n",dp());
    }
}