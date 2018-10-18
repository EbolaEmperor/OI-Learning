#include<bits/stdc++.h>
#define INF 0x7fffffff
using namespace std;

const int N=160,M=6010;
struct Edge{int to,capa,next;} e[N<<1];
int h[N],sum=0,n,m;
int fa[N],dep[N],val[N];
int pdx[N],tdx[N],cnt;
int now=0,col[N];
unsigned cut[N][N];
bool vis[N];

namespace MF
{
    struct Edge{int to,capa,flow,next;} e[M];
    int h[N],sum=-1,s,t;
    int d[N],cur[N];
    bool vis[N];
    int fa[N];

    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}

    void add_edge(int u,int v,int w)
    {
        e[++sum]={v,w,0,h[u]};h[u]=sum;
        e[++sum]={u,w,0,h[v]};h[v]=sum;
        if(find(u)!=find(v)) fa[find(u)]=find(v);
    }

    bool BFS()
    {
        queue<int> q;q.push(s);
        memset(vis,0,sizeof(vis));
        d[s]=0;vis[s]=1;
        while(!q.empty())
        {
            int u=q.front();q.pop();
            for(int t=h[u];~t;t=e[t].next)
            {
                int v=e[t].to;
                if(vis[v]||e[t].capa<=e[t].flow) continue;
                d[v]=d[u]+1;vis[v]=1;q.push(v);
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
            res+=flow;a-=flow;
            e[t].flow+=flow;
            e[t^1].flow-=flow;
            if(a==0) break;
        }
        return res;
    }

    int Dinic(int x,int y)
    {
        int res=0;s=x;t=y;
        for(int i=0;i<=sum;i++) e[i].flow=0;
        while(BFS()) memcpy(cur,h,sizeof(h)),res+=DFS(s,INF);
        return res;
    }

    void dfs(int u)
    {
        col[u]=now;
        for(int t=h[u];~t;t=e[t].next)
            if(col[e[t].to]!=now&&e[t].capa>e[t].flow)
                dfs(e[t].to);
    }

    void get(int u)
    {
        for(int i=1;i<=n;i++)
            if(find(i)==find(u))
                ::vis[i]=1,pdx[++cnt]=i;
    }
}

void add_edge(int u,int v,int w)
{
    e[++sum].to=v;
    e[sum].capa=w;
    e[sum].next=h[u];
    h[u]=sum;
}

void dfs(int u)
{
    for(int t=h[u];t;t=e[t].next)
    {
        int v=e[t].to;
        if(v==fa[u]) continue;
        dep[v]=dep[u]+1;
        val[v]=e[t].capa;
        fa[v]=u;dfs(v);
    }
}

int getcut(int x,int y)
{
    int ans=INF;
    if(MF::find(x)!=MF::find(y)) return 0;
    if(dep[x]<dep[y]) swap(x,y);
    while(dep[fa[x]]>=dep[y])
        ans=min(ans,val[x]),x=fa[x];
    while(x!=y)
    {
        ans=min(ans,val[x]);
        ans=min(ans,val[y]);
        x=fa[x];y=fa[y];
    }
    if(x!=y) ans=min(ans,min(val[x],val[y]));
    return ans;
}

void Build(int l,int r)
{
    if(l>=r) return;
    int cut=MF::Dinic(pdx[l],pdx[l+1]);
    now++;MF::dfs(MF::s);int p=l,q=r;
    for(int i=l;i<=r;i++)
        if(col[pdx[i]]==now) tdx[p++]=pdx[i];
        else tdx[q--]=pdx[i];
    for(int i=l;i<=r;i++) pdx[i]=tdx[i];
    add_edge(MF::s,MF::t,cut);
    add_edge(MF::t,MF::s,cut);
    Build(l,p-1);Build(q+1,r);
}

void Init()
{
    now=sum=0;MF::sum=-1;
    memset(h,0,sizeof(h));
    memset(dep,0,sizeof(dep));
    memset(fa,0,sizeof(fa));
    memset(vis,0,sizeof(vis));
    memset(col,0,sizeof(col));
    memset(MF::h,-1,sizeof(MF::h));
    for(int i=1;i<=n;i++) MF::fa[i]=i;
}

int main()
{
    int T,u,v,w,q;unsigned x;
    for(scanf("%d",&T);T;T--)
    {
        scanf("%d%d",&n,&m);Init();
        for(int i=1;i<=m;i++)
        {
            scanf("%d%d%d",&u,&v,&w);
            MF::add_edge(u,v,w);
        }
        for(int i=1;i<=n;i++)
        {
            if(vis[i]) continue;
            cnt=0;MF::get(i);
            Build(1,cnt);
            dep[i]=1;dfs(i);
        }
        for(int i=1;i<=n;i++)
            for(int j=i+1;j<=n;j++)
                cut[i][j]=getcut(i,j);
        for(scanf("%d",&q);q;q--)
        {
            int ans=0;
            scanf("%u",&x);
            for(int i=1;i<=n;i++)
                for(int j=i+1;j<=n;j++)
                    ans+=(cut[i][j]<=x);
            printf("%d\n",ans);
        }
        putchar('\n');
    }
    return 0;
}