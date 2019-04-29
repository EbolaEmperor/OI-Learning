#include<bits/stdc++.h>
using namespace std;

const int N=170,M=5010;
struct Edge
{
    int v,w;
    Edge(int _v=0,int _w=0):v(_v),w(_w){}
    bool operator < (const Edge &b) const{return w<b.w;}
};
struct D
{
    int u,cnt,lst,len;
    D(int _u=0,int _cnt=0,int _lst=0,int _len=0):u(_u),cnt(_cnt),lst(_lst),len(_len){}
    bool operator < (const D &b) const{return len>b.len;}
};
struct Qry{int b,c,id;};
vector<Edge> g[N];
int n,m,q,deg[N];
int st[N][M],idx[N][M],ans[M];
vector<int> f[N][N],vis[N][N],vals[N];
vector<Qry> qry[N];

int dijkstra(int a)
{
    priority_queue<D> pq;
    for(int i=1;i<=n;i++)
        for(int j=0;j<=n;j++)
            for(int k=0;k<f[i][j].size();k++)
                f[i][j][k]=INT_MAX,vis[i][j][k]=0;
    pq.push(D(a,0,0,0));
    f[a][0][0]=0;
    while(!pq.empty())
    {
        D tmp=pq.top();pq.pop();
        if(vis[tmp.u][tmp.cnt][tmp.lst]||tmp.cnt>=n) continue;
        int u=tmp.u;vis[u][tmp.cnt][tmp.lst]=1;
        for(int i=st[u][vals[u][tmp.lst]];i<g[u].size();i++)
        {
            int v=g[u][i].v,w=g[u][i].w;
            if(f[v][tmp.cnt+1][idx[v][w]]>f[u][tmp.cnt][tmp.lst]+w)
            {
                f[v][tmp.cnt+1][idx[v][w]]=f[u][tmp.cnt][tmp.lst]+w;
                pq.push(D(v,tmp.cnt+1,idx[v][w],f[v][tmp.cnt+1][idx[v][w]]));
            }
        }
    }
}

int main()
{
    scanf("%d%d%d",&n,&m,&q);
    for(int i=1;i<=n;i++)
        vals[i].push_back(0),deg[i]=1;
    for(int i=1,u,v,w;i<=m;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        g[u].emplace_back(v,w);
        vals[v].push_back(w);
        deg[v]++;
    }
    memset(st,-1,sizeof(st));
    for(int i=1;i<=n;i++)
    {
        sort(vals[i].begin(),vals[i].end());
        sort(g[i].begin(),g[i].end());
        for(int j=0;j<=n;j++)
            f[i][j].resize(deg[i]),vis[i][j].resize(deg[i]);
        for(int j=0;j<g[i].size();j++)
            st[i][g[i][j].w-1]=j;
        for(int j=0;j<vals[i].size();j++)
            idx[i][vals[i][j]]=j;
        for(int j=5000;j>=0;j--)
            if(st[i][j]==-1) st[i][j]=st[i][j+1];
    }
    for(int i=1;i<=q;i++)
    {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        qry[a].push_back((Qry){b,c,i});
    }
    for(int i=1;i<=n;i++)
    {
        if(qry[i].empty()) continue;
        dijkstra(i);
        for(auto p : qry[i])
        {
            int res=INT_MAX;
            for(int j=0;j<=p.c;j++)
                for(int x : f[p.b][j])
                    res=min(res,x);
            if(res>1e9) res=-1;
            ans[p.id]=res;
        }
    }
    for(int i=1;i<=q;i++)
        printf("%d\n",ans[i]);
    return 0;
}