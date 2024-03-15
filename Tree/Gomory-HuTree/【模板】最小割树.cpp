// luogu-judger-enable-o2
#include<bits/stdc++.h>
using namespace std;

const int N=1010,M=30010;
struct Edge{int v,w,nxt;} e[M];
int h[N],sum=0,n,m;
int col[N],tot=0;
int cut[N][N];
int pdx[N],tdx[N];

namespace Flow
{
    struct Edge{int v,w,f,nxt;} e[M];
    int h[N],sum=-1,s,t;
    int dep[N],cur[N];
    bool vis[N];
    void add_edge(int u,int v,int w)
    {
        e[++sum]=(Edge){v,w,0,h[u]};h[u]=sum;
        e[++sum]=(Edge){u,w,0,h[v]};h[v]=sum;
    }
    bool bfs()
    {
        queue<int> q;
        memset(vis,0,sizeof(bool)*(n+1));
        q.push(s);dep[s]=0;vis[s]=1;
        while(!q.empty())
        {
            int u=q.front();q.pop();
            for(int i=h[u];~i;i=e[i].nxt)
            {
                int v=e[i].v;
                if(!vis[v]&&e[i].w>e[i].f)
                    dep[v]=dep[u]+1,vis[v]=1,q.push(v);
            }
        }
        return vis[t];
    }
    int dfs(int u,int a)
    {
        if(u==t||a==0) return a;
        int res=0;
        for(int &i=cur[u];~i;i=e[i].nxt)
        {
            int v=e[i].v;
            if(dep[v]!=dep[u]+1) continue;
            int w=dfs(v,min(a,e[i].w-e[i].f));
            if(w) e[i].f+=w,e[i^1].f-=w,res+=w,a-=w;
            if(a==0) break;
        }
        return res;
    }
    int work(int _s,int _t)
    {
        s=_s;t=_t;int res=0;
        for(int i=0;i<=sum;i++) e[i].f=0;
        while(bfs())
        {
            memcpy(cur,h,sizeof(h));
            res+=dfs(s,0x3f3f3f3f);
        }
        return res;
    }
    void dfs(int u)
    {
        col[u]=tot;
        for(int i=h[u];~i;i=e[i].nxt)
            if(e[i].w>e[i].f&&col[e[i].v]!=tot)
                dfs(e[i].v);
    }
}

void add_edge(int u,int v,int w)
{
    e[++sum]=(Edge){v,w,h[u]};h[u]=sum;
    e[++sum]=(Edge){u,w,h[v]};h[v]=sum;
}
void build(int l,int r)
{
    if(l>=r) return;
    int x=pdx[l],y=pdx[l+1];
    int w=Flow::work(x,y);
    add_edge(x,y,w);
    tot++;Flow::dfs(x);
    int pl=l,pr=r;
    for(int i=l;i<=r;i++)
        if(col[pdx[i]]==tot) tdx[pl++]=pdx[i];
        else tdx[pr--]=pdx[i];
    for(int i=l;i<=r;i++) pdx[i]=tdx[i];
    build(l,pl-1);build(pr+1,r);
}
void dfs(int u,int fa,int *cut)
{
    for(int i=h[u];i;i=e[i].nxt)
    {
        int v=e[i].v;
        if(v==fa) continue;
        cut[v]=min(cut[u],e[i].w);
        dfs(v,u,cut);
    }
}

int main()
{
    scanf("%d%d",&n,&m);
    memset(Flow::h,-1,sizeof(Flow::h));
    for(int i=1,u,v,w;i<=m;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        Flow::add_edge(u,v,w);
    }
    for(int i=1;i<=n;i++) pdx[i]=i;
    build(1,n);
    for(int i=1;i<=n;i++)
        cut[i][i]=2e9,dfs(i,0,cut[i]);
    int q,x,y;scanf("%d",&q);
    while(q--)
    {
        scanf("%d%d",&x,&y);
        printf("%d\n",cut[x][y]);
    }
    return 0;
}
