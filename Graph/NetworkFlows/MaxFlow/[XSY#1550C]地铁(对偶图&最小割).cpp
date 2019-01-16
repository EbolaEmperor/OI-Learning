#include<bits/stdc++.h>
using namespace std;

const int INF=0x3f3f3f3f;
const int N=2010,M=50010;
struct E{int u,v,w;} eg[N];
struct Edge{int to,next,capa,flow;} e[M];
int h[N],sum=-1,n,m,k,s,t;
int dep[N],cur[N],col[N],blk[N];
bool vis[N],cf[N],cc[N];

void add_edge(int u,int v,int a,int b)
{
    e[++sum]={v,h[u],a,0};h[u]=sum;
    e[++sum]={u,h[v],b,0};h[v]=sum;
}

bool bfs()
{
    memset(vis,0,sizeof(vis));
    queue<int> q;q.push(s);
    dep[s]=1;vis[s]=1;
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(int t=h[u];~t;t=e[t].next)
        {
            int v=e[t].to;
            if(!vis[v]&&e[t].capa>e[t].flow)
            {
                dep[v]=dep[u]+1;
                vis[v]=1;
                q.push(v);
            }
        }
    }
    return vis[t];
}

int dfs(int u,int a)
{
    if(u==t||a==0) return a;
    int flow=0;
    for(int &t=cur[u];~t;t=e[t].next)
    {
        int v=e[t].to;
        if(dep[v]!=dep[u]+1) continue;
        int f=dfs(v,min(a,e[t].capa-e[t].flow));
        if(f>0)
        {
            flow+=f;a-=f;
            e[t].flow+=f;
            e[t^1].flow-=f;
            if(!a) break;
        }
    }
    return flow;
}

int dinic()
{
    int flow=0;
    while(bfs())
    {
        memcpy(cur,h,sizeof(h));
        flow+=dfs(s,INF);
        if(flow>=INF) return -1;
    }
    return flow;
}

int find(int x){return col[x]==x?x:col[x]=find(col[x]);}

int main()
{
    scanf("%d%d%d",&n,&m,&k);
    s=m+1;t=n+m+2;
    memset(h,-1,sizeof(h));
    for(int i=1,u,v,w;i<=m;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        eg[i]=(E){u,v,w};
    }
    eg[m+1]=(E){0,n+1,INF};
    sort(eg+1,eg+2+m,[](E a,E b){return a.v-a.u<b.v-b.u;});
    for(int i=1;i<=n;i++) col[i]=i;
    for(int i=1,u,v;i<=k;i++)
    {
        scanf("%d%d",&u,&v);
        u=find(u);v=find(v);
        if(u==v) continue;
        col[u]=v;
    }
    for(int i=1;i<=m+1;i++)
    {
        int u=eg[i].u,v=eg[i].v;
        bool bottom=0;
        for(int j=u;j<v;j++)
        {
            if(blk[j]&&!cf[blk[j]])
            {
                int tmp=blk[j];
                add_edge(i,tmp,eg[tmp].w,INF);
                cf[tmp]=1;
            }
            else if(!blk[j]) bottom|=(i<=m||j>0&&j<n);
            blk[j]=i;
            if(j>u&&!cc[j])
            {
                add_edge(i,m+1+col[j],INF,INF);
                cc[j]=1;
            }
        }
        if(bottom) add_edge(i,t,INF,INF);
    }
    printf("%d\n",dinic());
    return 0;
}