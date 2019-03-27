#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
typedef pair<int,int> pii;
const int N=100010,P=N*25;
int lc[P],rc[P],mn[P],rt[N],tot=0;
int n,m,s,online,f[N],fa[N],p[N];
int anc[20][N],dep[N];
vector<pii> org[N];
vector<int> g[N];
int vis[N],deg[N];
LL dis[N];

void dijkstra()
{
    memset(dis,0x3f,sizeof(dis));
    priority_queue<pii> pq;
    dis[s]=0;pq.push(pii(-dis[s],s));
    while(!pq.empty())
    {
        int u=pq.top().second;pq.pop();
        if(vis[u]) continue;vis[u]=1;
        for(auto e : org[u])
            if(dis[u]+e.second<dis[e.first])
            {
                dis[e.first]=dis[u]+e.second;
                pq.push(pii(-dis[e.first],e.first));
            }
    }
}

void build_graph()
{
    for(int u=1;u<=n;u++)
        for(auto e : org[u])
            if(dis[u]+e.second==dis[e.first])
                g[u].emplace_back(e.first),deg[e.first]++;
}

void build_tree(int u)
{
    static bool vis[N];
    vis[u]=1;
    for(int k=1;k<=17;k++)
        anc[k][u]=anc[k-1][anc[k-1][u]];
    sort(g[u].begin(),g[u].end(),[](int a,int b){return p[a]<p[b];});
    for(int v : g[u])
    {
        if(vis[v]) continue;
        dep[v]=dep[u]+1;
        fa[v]=anc[0][v]=u;
        build_tree(v);
    }
}

int lca(int u,int v)
{
    if(dep[u]<dep[v]) swap(u,v);
    for(int k=17;k>=0;k--)
        if(dep[anc[k][u]]>=dep[v])
            u=anc[k][u];
    if(u==v) return u;
    for(int k=17;k>=0;k--)
        if(anc[k][u]!=anc[k][v])
            u=anc[k][u],v=anc[k][v];
    return fa[u];
}

void insert(int &o,int p,int l,int r,int k,int x)
{
    mn[o=++tot]=min(mn[p],x);
    lc[o]=lc[p];rc[o]=rc[p];
    if(l==r) return;
    int mid=(l+r)/2;
    if(k<=mid) insert(lc[o],lc[p],l,mid,k,x);
    else insert(rc[o],rc[p],mid+1,r,k,x);
}

int qmin(int o,int l,int r,int nl,int nr)
{
    if(l>=nl&&r<=nr) return mn[o];
    int mid=(l+r)/2,res=INT_MAX;
    if(nl<=mid) res=min(res,qmin(lc[o],l,mid,nl,nr));
    if(nr>mid) res=min(res,qmin(rc[o],mid+1,r,nl,nr));
    return res;
}

int find(int o,int l,int r,int x)
{
    if(l==r) return l;
    int mid=(l+r)/2;
    if(mn[rc[o]]<=x) return find(rc[o],mid+1,r,x);
    else return find(lc[o],l,mid,x);
}

void build_chairman_tree()
{
    queue<int> q;q.push(s);mn[0]=INT_MAX;
    for(int i=1;i<=n;i++) f[i]=dep[i];
    while(!q.empty())
    {
        int u=q.front();q.pop();
        insert(rt[u],rt[fa[u]],1,n,dep[u],f[u]);
        for(int v : g[u])
        {
            if(!--deg[v]) q.push(v);
            if(fa[v]==u) continue;
            int x=lca(u,v);
            f[v]=min(f[v],qmin(rt[u],1,n,dep[x],dep[u]));
        }
    }
}

int main()
{
    scanf("%d%d%d%d",&n,&m,&s,&online);
    for(int i=1;i<=n;i++) scanf("%d",p+i);
    for(int i=1,u,v,w;i<=m;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        org[u].emplace_back(v,w);
        org[v].emplace_back(u,w);
    }
    dijkstra();
    build_graph();
    dep[s]=1;build_tree(s);
    build_chairman_tree();
    int q,lastans=0,u,v;
    scanf("%d",&q);
    while(q--)
    {
        scanf("%d%d",&u,&v);
        if(online) u^=lastans,v^=lastans;
        lastans=find(rt[v],1,n,dep[u])-dep[u];
        printf("%d\n",lastans);
    }
    return 0;
}