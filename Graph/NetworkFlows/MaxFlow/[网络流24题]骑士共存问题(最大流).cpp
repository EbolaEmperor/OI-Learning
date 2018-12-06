#include<bits/stdc++.h>
using namespace std;

int mov[8][2]{ {-2,-1},{-1,-2},{1,-2},{2,-1},{2,1},{1,2},{-1,2},{-2,1} };
const int N=40010,M=210;
struct Edge{int to,flow,next;} e[2000010];
int idx[M][M],h[N],sum=-1,n,m,s,t;
bool vis[N];int dep[N],cur[N];
bool cant[M][M];

void add_edge(int u,int v)
{
    e[++sum]={v,1,h[u]};h[u]=sum;
    e[++sum]={u,0,h[v]};h[v]=sum;
}

bool BFS()
{
    queue<int> q;q.push(s);
    memset(vis,0,sizeof(vis));
    vis[s]=1;dep[s]=0;
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(int t=h[u];~t;t=e[t].next)
        {
            if(e[t].flow<=0) continue;
            int v=e[t].to;
            if(vis[v]) continue;
            dep[v]=dep[u]+1;
            vis[v]=1;q.push(v);
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
        if(dep[v]!=dep[u]+1) continue;
        flow=DFS(v,min(a,e[t].flow));
        if(!flow) continue;
        e[t].flow-=flow;
        e[t^1].flow+=flow;
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
        flow+=DFS(s,INT_MAX);
    }
    return flow;
}

int main()
{
    int x,y,cnt=0;
    memset(h,-1,sizeof(h));
    scanf("%d%d",&n,&m);
    s=0;t=n*n+1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            idx[i][j]=++cnt;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&x,&y);
        cant[x][y]=1;
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        {
            if(cant[i][j]) continue;
            if((i+j)&1)
            {
                add_edge(s,idx[i][j]);
                for(int k=0;k<8;k++)
                {
                    int x=i+mov[k][0],y=j+mov[k][1];
                    if(x<1||x>n||y<1||y>n||cant[x][y]) continue;
                    add_edge(idx[i][j],idx[x][y]);
                }
            }
            else add_edge(idx[i][j],t);
        }
    printf("%d\n",n*n-m-Dinic());
    return 0;
}