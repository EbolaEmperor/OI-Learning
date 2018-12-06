#include<bits/stdc++.h>
#define INF 0x7fffffff
using namespace std;

const int N=25010;
struct Edge{int to,capa,flow,next;} e[2000010];
int h[N],sum=-1,s=0,t=1,n,m,tot=1;
bool vis[N];
int d[N],cur[N];
int id[55][55][11];

void AddEdge(int u,int v,int w)
{
    e[++sum].to=v;
    e[sum].capa=w;
    e[sum].flow=0;
    e[sum].next=h[u];
    h[u]=sum;
}
void add_edge(int u,int v,int w)
{
    AddEdge(u,v,w);
    AddEdge(v,u,0);
}

bool BFS()
{
    memset(vis,0,sizeof(vis));
    queue<int> q;q.push(s);
    vis[s]=1;d[s]=0;
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(int tmp=h[u];~tmp;tmp=e[tmp].next)   
            if(!vis[e[tmp].to]&&e[tmp].capa>e[tmp].flow)
            {
                d[e[tmp].to]=d[u]+1;
                vis[e[tmp].to]=1;
                q.push(e[tmp].to);
            }
    }
    return vis[t];
}

int DFS(int u,int a)
{
    if(u==t||a==0) return a;
    int flow=0,f;
    for(int &tmp=cur[u];~tmp;tmp=e[tmp].next)
        if(d[e[tmp].to]==d[u]+1)
        {
            f=DFS(e[tmp].to,min(a,e[tmp].capa-e[tmp].flow));
            if(f>0)
            {
                flow+=f;a-=f;
                e[tmp].flow+=f;
                e[tmp^1].flow-=f;
                if(a==0) break;
            }
        }
    return flow;
}

int Dinic()
{
    int flow=0;
    while(BFS())
    {
        for(int i=0;i<=tot;i++) cur[i]=h[i];
        flow+=DFS(s,INF);
    }
    return flow;
}

void Build()
{
    scanf("%d%d",&n,&m);
    memset(h,-1,sizeof(h));
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        {
            id[i][j][0]=++tot;
            if(i+j&1) add_edge(id[i][j][0],t,INF);
            else add_edge(s,id[i][j][0],INF);
            for(int k=1;k<=8;k++)
            {
                id[i][j][k]=++tot;
                if(i+j&1) add_edge(id[i][j][k],id[i][j][k-1],9-k);
                else add_edge(id[i][j][k-1],id[i][j][k],9-k);
            }
        }
    int lim,x,y;
    for(int i=1;i<n;i++)
        for(int j=1;j<=m;j++)
        {
            x=i;y=i+1;
            if(i+j&1) swap(x,y);
            scanf("%d",&lim);
            for(int k=1;k<=9;k++)
            {
                int z=lim-k;
                if(z<1){add_edge(id[x][j][k-1],t,INF);break;}
                if(z<9) add_edge(id[x][j][k-1],id[y][j][z],INF);
            }
        }
    for(int i=1;i<=n;i++)
        for(int j=1;j<m;j++)
        {
            x=j;y=j+1;
            if(i+j&1) swap(x,y);
            scanf("%d",&lim);
            for(int k=1;k<=9;k++)
            {
                int z=lim-k;
                if(z<1){add_edge(id[i][x][k-1],t,INF);break;}
                if(z<9) add_edge(id[i][x][k-1],id[i][y][z],INF);
            }
        }
}

int main()
{
    Build();
    printf("%d\n",9*n*m-Dinic());
    return 0;
}