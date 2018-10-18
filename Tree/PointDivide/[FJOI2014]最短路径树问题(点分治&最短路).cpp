#include<bits/stdc++.h>
#define FR first
#define SE second
#define MP make_pair
#define PB push_back
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
const int N=30010;
struct Edge{int to,capa,next;} e[N<<1];
int h[N],n,m,K,esum=0;
vector<pii> G[N];
priority_queue<pii> q;
bool vis[N];int dis[N];
int sum=0,root,mxsz[N];
pii ans,d[N],now[N],cross[N];
int sz[N],mxd,tot;

void add_edge(int u,int v,int w)
{
    e[++esum].to=v;
    e[esum].capa=w;
    e[esum].next=h[u];
    h[u]=esum;
}

void dijkstra()
{
    memset(dis,0x3f,sizeof(dis));
    q.push(MP(0,1));dis[1]=0;
    while(!q.empty())
    {
        pii tmp=q.top();q.pop();
        int u=tmp.SE,w=-tmp.FR;
        if(vis[u]) continue;
        vis[u]=1;
        for(pii pr : G[u])
            if(w+pr.SE<dis[pr.FR])
            {
                dis[pr.FR]=w+pr.SE;
                q.push(MP(-dis[pr.FR],pr.FR));
            }
    }
}

void find(int u,int fa)
{
    sz[u]=1;mxsz[u]=0;
    for(int t=h[u];t;t=e[t].next)
    {
        int v=e[t].to;
        if(v==fa||vis[v]) continue;
        find(v,u);sz[u]+=sz[v];
        mxsz[u]=max(mxsz[u],sz[v]);
    }
    mxsz[u]=max(mxsz[u],sum-sz[u]);
    if(mxsz[u]<mxsz[root]) root=u;
}

void dfs(int u,int fa)
{
    now[++tot]=d[u];
    for(int t=h[u];t;t=e[t].next)
    {
        int v=e[t].to;
        if(v==fa||vis[v]) continue;
        d[v].SE=d[u].SE+e[t].capa;
        d[v].FR=d[u].FR+1;dfs(v,u);
    }
}

void gao(int u,int w)
{
    d[u].FR=1;d[u].SE=w;
    tot=0;dfs(u,0);
    for(int i=1;i<=tot;i++)
    {
        int rest=K-now[i].FR-1,w=now[i].SE;
        if(now[i].FR<K-1)
        {
            int t1=cross[rest].FR,t2=cross[rest].SE;
            if(w+t2>ans.FR) ans=MP(w+t2,t1);
            else if(w+t2==ans.FR) ans.SE+=t1;
        }
        if(now[i].FR==K-1)
        {
            if(w>ans.FR) ans=MP(w,1);
            else if(w==ans.FR) ans.SE++;
        }
    }
    for(int i=1;i<=tot;i++)
        if(now[i].FR<=K-1)
        {
            int num=now[i].FR;
            if(now[i].SE>cross[num].SE) cross[num]=MP(1,now[i].SE);
            else if(now[i].SE==cross[num].SE) cross[num].FR++;
            mxd=max(mxd,num);
        }
}

void solve(int u)
{
    vis[u]=1;mxd=0;
    for(int t=h[u];t;t=e[t].next)
        if(!vis[e[t].to]) gao(e[t].to,e[t].capa);
    memset(cross,0,sizeof(pii)*(mxd+2));
    for(int t=h[u];t;t=e[t].next)
    {
        int v=e[t].to;
        if(vis[v]) continue;
        sum=sz[v];root=0;
        find(v,u);solve(root);
    }
}

void build(int u)
{
    vis[u]=1;
    for(pii pr : G[u])
    {
        int v=pr.FR,w=pr.SE;
        if(vis[v]||dis[u]+w!=dis[v]) continue;
        add_edge(u,v,w);add_edge(v,u,w);build(v);
    }
}

int main()
{
    int u,v,w;
    n=read();m=read();K=read();
    for(int i=1;i<=m;i++)
    {
        u=read();v=read();w=read();
        G[u].PB(MP(v,w));
        G[v].PB(MP(u,w));
    }
    for(int i=1;i<=n;i++) sort(G[i].begin(),G[i].end());
    dijkstra();memset(vis,0,sizeof(vis));build(1);
    memset(vis,0,sizeof(vis));
    sum=mxsz[0]=n;root=0;
    find(1,0);solve(root);
    printf("%d %d\n",ans.FR,ans.SE);
    return 0;
}