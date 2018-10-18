#include<bits/stdc++.h>
#define INF 0x7fffffff
using namespace std;

const int S=(1<<20)+5;
char buf[S],*H,*T;
inline char Get()
{
    if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
    return H==T?-1:*H++;
}
inline int read()
{
    int x=0,fg=1;char c=Get();
    while(!isdigit(c)&&c!='-') c=Get();
    if(c=='-') fg=-1,c=Get();
    while(isdigit(c)) x=x*10+c-'0',c=Get();
    return x*fg;
}

const int N=610,M=1000010;
struct Edge{int to,capa,flow,next;} e[M];
int h[N],sum=-1,n,m,s,t,ans=0;
int cur[N],d[N];bool vis[N];
int idx[25][35],w[25][35],good[N];
int frs[M],tos[M],cc=0;

namespace prework
{
    struct Edge{int to,capa,flow,next;} e[M];
    int h[N],sum=0,deg[N];

    void add_edge(int u,int v)
    {
        e[++sum].to=v;
        e[sum].next=h[u];
        h[u]=sum;deg[v]++;
    }

    void Topo()
    {
        for(int i=1;i<=cc;i++)
            add_edge(tos[i],frs[i]);
        queue<int> q;
        for(int i=1;i<=n*m;i++)
            if(!deg[i]) q.push(i);
        while(!q.empty())
        {
            int u=q.front();q.pop();good[u]=1;
            for(int t=h[u];t;t=e[t].next)
                if(!--deg[e[t].to]) q.push(e[t].to);
        }
    }
}

void add_edge(int u,int v,int w)
{
    if(!good[u]||!good[v]) return;
    e[++sum]={v,w,0,h[u]};h[u]=sum;
    e[++sum]={u,0,0,h[v]};h[v]=sum;
}

bool BFS()
{
    queue<int> q;q.push(s);
    memset(vis,0,sizeof(vis));
    vis[s]=1;d[s]=0;
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(int t=h[u];~t;t=e[t].next)
        {
            int v=e[t].to;
            if(!vis[v]&&e[t].capa>e[t].flow)
            {
                d[v]=d[u]+1;
                vis[v]=1;
                q.push(v);
            }
        }
    }
    return vis[t];
}

int DFS(int u,int a)
{
    if(u==t||a==0) return a;
    int res=0,flow;
    for(int &t=cur[u];~t;t=e[t].next)
    {
        int v=e[t].to;
        if(d[v]!=d[u]+1) continue;
        flow=DFS(v,min(a,e[t].capa-e[t].flow));
        if(!flow) continue;
        e[t].flow+=flow;
        e[t^1].flow-=flow;
        res+=flow;a-=flow;
        if(a==0) break;
    }
    return res;
}

int Dinic()
{
    int flow=0;
    while(BFS())
    {
        memcpy(cur,h,sizeof(h));
        flow+=DFS(s,INF);
    }
    return flow;
}

void Build()
{
    memset(h,-1,sizeof(h));
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            if(!good[idx[i][j]]) continue;
            if(w[i][j]>0) add_edge(s,idx[i][j],w[i][j]),ans+=w[i][j];
            else if(w[i][j]<0) add_edge(idx[i][j],t,-w[i][j]);
            if(good[idx[i][j+1]]) continue;
            for(int k=j+1;k<=m;k++)
            {
                if(!good[idx[i][k]]) continue;
                add_edge(idx[i][j],idx[i][k],INF);
                break;
            }
        }
    for(int i=1;i<=cc;i++)
        add_edge(frs[i],tos[i],INF);
}

int main()
{
    int cnt=0,num,x,y;
    n=read();m=read();
    good[s=0]=good[t=n*m+1]=1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            idx[i][j]=++cnt;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            w[i][j]=read();
            num=read();
            for(int k=1;k<=num;k++)
            {
                x=read()+1;y=read()+1;
                frs[++cc]=idx[x][y];
                tos[cc]=idx[i][j];
            }
            if(j<m)
            {
                frs[++cc]=idx[i][j];
                tos[cc]=idx[i][j+1];
            }
        }
    prework::Topo();
    Build();
    ans-=Dinic();
    cout<<ans<<endl;
    return 0;
}