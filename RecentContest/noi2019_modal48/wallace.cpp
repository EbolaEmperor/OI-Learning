#include<bits/stdc++.h>
using namespace std;

const int N=55;
vector<int> g1[N],g2[N];
struct Edge{int to,next,capa,flow;} e[500];
int h[N],sum,s,t;
int dep[N],cur[N];
bool vis[N];
int n,val[N],vs=0;

void add_edge(int u,int v,int w)
{
    e[++sum]={v,h[u],w,0};h[u]=sum;
    e[++sum]={u,h[v],0,0};h[v]=sum;
}

bool bfs()
{
    queue<int> q;
    memset(vis,0,sizeof(vis));
    q.push(s);dep[s]=0;vis[s]=1;
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(int tmp=h[u];~tmp;tmp=e[tmp].next)
            if(e[tmp].capa>e[tmp].flow&&!vis[e[tmp].to])
            {
                dep[e[tmp].to]=dep[u]+1;
                vis[e[tmp].to]=1;
                q.push(e[tmp].to);
            }
    }
    return vis[t];
}

int dfs(int u,int a)
{
    if(u==t||a==0) return a;
    int flow=0;
    for(int &tmp=cur[u];~tmp;tmp=e[tmp].next)
        if(dep[e[tmp].to]==dep[u]+1)
        {
            int f=dfs(e[tmp].to,min(a,e[tmp].capa-e[tmp].flow));
            if(!f) continue;
            flow+=f;a-=f;
            e[tmp].flow+=f;
            e[tmp^1].flow-=f;
            if(a==0) break;
        }
    return flow;
}

int dinic()
{
    int res=0;
    while(bfs())
    {
        memcpy(cur,h,sizeof(h));
        res+=dfs(s,INT_MAX);
    }
    return res;
}

void dfs1(int u,int fa)
{
    for(int v : g1[u])
    {
        if(v==fa) continue;
        add_edge(v,u,INT_MAX);
        dfs1(v,u);
    }
}

void dfs2(int u,int fa)
{
    for(int v : g2[u])
    {
        if(v==fa) continue;
        add_edge(v,u,INT_MAX);
        dfs2(v,u);
    }
}

int gao(int rt)
{
    memset(h,-1,sizeof(h));
    sum=-1;s=0;t=n+1;
    for(int i=1;i<=n;i++)
        if(val[i]>=0) add_edge(s,i,val[i]);
        else add_edge(i,t,-val[i]);
    dfs1(rt,0);dfs2(rt,0);
    return vs-dinic();
}

int main()
{
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",val+i);
        if(val[i]>=0) vs+=val[i];
    }
    for(int i=1,u,v;i<n;i++)
    {
        scanf("%d%d",&u,&v);u++;v++;
        g1[u].emplace_back(v);
        g1[v].emplace_back(u);
    }
    for(int i=1,u,v;i<n;i++)
    {
        scanf("%d%d",&u,&v);u++;v++;
        g2[u].emplace_back(v);
        g2[v].emplace_back(u);
    }
    int ans=0;
    for(int i=1;i<=n;i++)
        ans=max(ans,gao(i));
    printf("%d\n",ans);
    return 0;
}