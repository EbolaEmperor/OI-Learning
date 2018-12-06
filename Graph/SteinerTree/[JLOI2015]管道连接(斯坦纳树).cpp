#include<bits/stdc++.h>
using namespace std;

const int N=1050;
const int INF=0x3f3f3f3f;
struct Edge{int to,capa,next;} e[N*6];
int h[N],sum=0,n,m,tot;
int f[N][N],stu[15],g[N];
bool inq[N],can[N];
queue<int> q;

void add_edge(int u,int v,int w)
{
    e[++sum].to=v;
    e[sum].capa=w;
    e[sum].next=h[u];
    h[u]=sum;
}

void spfa(int s)
{
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(int t=h[u];t;t=e[t].next)
        {
            int v=e[t].to;
            if(f[s][u]+e[t].capa<f[s][v])
            {
                f[s][v]=f[s][u]+e[t].capa;
                if(inq[v]) continue;
                q.push(v);inq[v]=1;
            }
        }
        inq[u]=0;
    }
}

int main()
{
    int u,v,w;
    scanf("%d%d%d",&n,&m,&tot);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d",&u,&v,&w);
        add_edge(u,v,w);
        add_edge(v,u,w);
    }
    memset(f,0x3f,sizeof(f));
    for(int i=0;i<tot;i++)
    {
        scanf("%d%d",&w,&u);
        stu[w]|=1<<i;
        f[1<<i][u]=0;
    }
    for(int i=0;i<=tot;i++) can[stu[i]]=1;
    for(int s=1;s<(1<<tot);s++)
    {
        for(int i=1;i<=n;i++)
        {
            for(int t=(s-1)&s;t;t=(t-1)&s)
                f[s][i]=min(f[s][i],f[t][i]+f[s^t][i]);
            if(f[s][i]<INF) q.push(i),inq[i]=1;
        }
        spfa(s);g[s]=INF;
        for(int i=1;i<=n;i++)
            g[s]=min(g[s],f[s][i]);
    }
    for(int s=0;s<(1<<tot);s++)
        for(int t=(s-1)&s;t;t=(t-1)&s)
            if(can[t]&&can[s^t])
            {
                g[s]=min(g[s],g[t]+g[s^t]);
                can[s]=1;
            }
    printf("%d\n",g[(1<<tot)-1]);
    return 0;
}