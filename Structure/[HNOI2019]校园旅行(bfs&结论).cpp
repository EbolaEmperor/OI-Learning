#include<bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
const int N=5010;
vector<pii> e1,e2;
vector<int> g[N][2],gg[N];
int n,m,q,col[N],fa[N],part[N];
bool can[N][N];

int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}

inline void add_edge(int u,int v)
{
    g[u][col[v]].push_back(v);
    g[v][col[u]].push_back(u);
}

void build_e1()
{
    for(int i=1;i<=n;i++) fa[i]=i;
    for(auto e : e1)
    {
        int u=find(e.first),v=find(e.second);
        if(u==v) continue;
        add_edge(e.first,e.second);
        fa[u]=v;
    }
}

bool check(int u)
{
    for(int v : gg[u])
        if(!part[v])
        {
            part[v]=3-part[u];
            if(!check(v)) return 0;
        }
        else if(part[v]==part[u]) return 0;
    return 1;
}

void build_e2()
{
    for(int i=1;i<=n;i++) fa[i]=i;
    for(auto e : e2)
    {
        gg[e.first].push_back(e.second);
        gg[e.second].push_back(e.first);
        int u=find(e.first),v=find(e.second);
        if(u==v) continue;
        add_edge(e.first,e.second);
        fa[u]=v;
    }
    for(int i=1;i<=n;i++)
    {
        if(fa[i]!=i) continue;
        part[i]=1;
        bool flag=check(i);
        if(!flag) g[i][col[i]].push_back(i); 
    }
}

void bfs()
{
    queue<pii> q;
    for(int i=1;i<=n;i++)
    {
        q.push(pii(i,i));
        can[i][i]=1;
        for(int v : g[i][col[i]])
            q.push(pii(i,v)),can[i][v]=1;
    }
    while(!q.empty())
    {
        pii tmp=q.front();q.pop();
        int x=tmp.first,y=tmp.second;
        for(int u : g[x][0])
            for(int v : g[y][0])
                if(!can[u][v]) can[u][v]=1,q.push(pii(u,v));
        for(int u : g[x][1])
            for(int v : g[y][1])
                if(!can[u][v]) can[u][v]=1,q.push(pii(u,v));
    }
}

int main()
{
    static char s[N];
    scanf("%d%d%d%s",&n,&m,&q,s+1);
    for(int i=1;i<=n;i++) col[i]=s[i]-'0';
    for(int i=1,u,v;i<=m;i++)
    {
        scanf("%d%d",&u,&v);
        if(col[u]!=col[v]) e1.emplace_back(u,v);
        else e2.emplace_back(u,v);
    }
    build_e1();
    build_e2();
    bfs();
    while(q--)
    {
        static int x,y;
        scanf("%d%d",&x,&y);
        puts(can[x][y]?"YES":"NO");
    }
    return 0;
}
