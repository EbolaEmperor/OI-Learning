#include<bits/stdc++.h>
using namespace std;

const int N=20010;
const int INF=0x3f3f3f3f;
struct Edge{int from,to,capa,flow,cost,next;} e[N];
int h[N],sum=-1,n,k,l,r,s,t;
int dis[N],pre[N],able[N];
int v1[N],v2[N],ans=0;
bool inq[N];

void add_edge(int u,int v,int w,int c)
{
    e[++sum]={u,v,w,0,c,h[u]};h[u]=sum;
    e[++sum]={v,u,0,0,-c,h[v]};h[v]=sum;
}

bool spfa(int &cost)
{
    memset(inq,0,sizeof(inq));
    for(int i=0;i<=n+5;i++) dis[i]=-INF;
    queue<int> q;q.push(s);
    dis[s]=0;inq[s]=1;able[s]=INF;
    while(!q.empty())
    {
        int u=q.front();
        for(int tmp=h[u];~tmp;tmp=e[tmp].next)
        {
            int v=e[tmp].to;
            if(dis[u]+e[tmp].cost>dis[v]&&e[tmp].capa>e[tmp].flow)
            {
                dis[v]=dis[u]+e[tmp].cost;
                able[v]=min(able[u],e[tmp].capa-e[tmp].flow);
                pre[v]=tmp;
                if(inq[v]) continue;
                q.push(v);inq[v]=1;
            }
        }
        q.pop();inq[u]=0;
    }
    if(dis[t]==-INF) return 0;
    cost+=able[t]*dis[t];
    for(int u=t;u!=s;u=e[pre[u]].from)
    {
        e[pre[u]].flow+=able[t];
        e[pre[u]^1].flow-=able[t];
    }
    return 1;
}

int main()
{
    memset(h,-1,sizeof(h));
    scanf("%d%d%d%d",&n,&k,&l,&r);
    for(int i=1;i<=n;i++)
        scanf("%d%d",v1+i,v2+i),ans+=v2[i];
    s=0;t=n+1;r=k-r;
    add_edge(s,n+2,r,0);
    for(int i=1;i<=k;i++)
        add_edge(n+2,i,1,0);
    for(int i=1;i<=n;i++)
    {
        add_edge(i,i+1,r-l,0);
        add_edge(i,i+k<t?i+k:t,1,v1[i]-v2[i]);
    }
    while(spfa(ans));
    printf("%d\n",ans);
    return 0;
}