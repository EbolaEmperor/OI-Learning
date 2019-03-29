#include<bits/stdc++.h>
#define INF 0x7fffffff
using namespace std;

const int N=3010,M=30010;
struct Edge{int to,capa,next;} e[N<<1];
int h[N],sum=0,n,m,now=0;
int pdx[N],tdx[N],col[N];
int cut[N][N],cur;

void add_edge(int u,int v,int w)
{
    e[++sum].to=v;
    e[sum].capa=w;
    e[sum].next=h[u];
    h[u]=sum;
}

namespace GHT
{
    struct Edge{int to,capa,flow,next;} e[M];
    int h[N],sum=-1,s,t;
    int d[N],cur[N];
    bool vis[N];

    void add_edge(int u,int v,int w)
    {
        e[++sum]={v,w,0,h[u]};h[u]=sum;
        e[++sum]={u,w,0,h[v]};h[v]=sum;
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

    int Dinic(int x,int y)
    {
        int flow=0;s=x;t=y;
        for(int i=0;i<=sum;i++) e[i].flow=0;
        while(BFS())
        {
            memcpy(cur,h,sizeof(h));
            flow+=DFS(s,INF);
        }
        return flow;
    }

    void dfs(int u)
    {
        col[u]=now;
        for(int t=h[u];~t;t=e[t].next)
            if(e[t].capa>e[t].flow&&col[e[t].to]!=now)
                dfs(e[t].to);
    }

    void build(int l,int r)
    {
        if(l>=r) return;
        int x=pdx[l],y=pdx[l+1];
        int cut=Dinic(x,y);
        now++;dfs(x);int p=l,q=r;
        for(int i=l;i<=r;i++)
            if(col[pdx[i]]==now) tdx[p++]=pdx[i];
            else tdx[q--]=pdx[i];
        for(int i=l;i<=r;i++) pdx[i]=tdx[i];
        ::add_edge(x,y,cut);
        ::add_edge(y,x,cut);
        build(l,p-1);build(q+1,r);
    }
}

void dfs(int u,int la)
{
    for(int t=h[u];t;t=e[t].next)
    {
        int v=e[t].to;
        if(v==la) continue;
        cut[cur][v]=min(cut[cur][u],e[t].capa);
        dfs(v,u);
    }
}

int main()
{
    int u,v,w,q;
    scanf("%d%d",&n,&m);
    memset(GHT::h,-1,sizeof(GHT::h));
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&u,&v);
        GHT::add_edge(u,v,1);
    }
    for(int i=1;i<=n;i++) pdx[i]=i;
    GHT::build(1,n);
    for(int i=1;i<=n;i++) cur=i,cut[i][i]=4,dfs(i,i);
    int ans=0;
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)
            ans+=cut[i][j];
    printf("%d\n",ans);
    return 0;
}