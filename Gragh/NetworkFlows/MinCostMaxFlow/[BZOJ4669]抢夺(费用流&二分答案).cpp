#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int INF=0x3f3f3f3f;
const int N=1010,M=10010;
struct Roads{int flow,len;};
struct Edge{int from,to,cost,capa,flow,next;} e[M];
int h[N],sum,n,m,K,s,t;
int pre[N],a[N],dis[N];
bool inq[N];
vector<Roads> road;

void add_edge(int u,int v,int w)
{
    e[++sum]={u,v,1,w,0,h[u]};h[u]=sum;
    e[++sum]={v,u,-1,0,0,h[v]};h[v]=sum;
}

bool spfa()
{
    queue<int> q;q.push(s);
    memset(dis,0x3f,sizeof(dis));
    inq[s]=1;dis[s]=0;a[s]=INF;
    while(!q.empty())
    {
        int u=q.front();
        for(int eg=h[u];~eg;eg=e[eg].next)
        {
            int v=e[eg].to;
            if(e[eg].capa>e[eg].flow&&dis[u]+e[eg].cost<dis[v])
            {
                dis[v]=dis[u]+e[eg].cost;pre[v]=eg;
                a[v]=min(a[u],e[eg].capa-e[eg].flow);
                if(inq[v]) continue;
                inq[v]=1;q.push(v);
            }
        }
        q.pop();inq[u]=0;
    }
    if(dis[t]==INF) return 0;
    Roads tmp;tmp.flow=a[t];tmp.len=dis[t];
    road.push_back(tmp);
    for(int u=t;u!=s;u=e[pre[u]].from)
        e[pre[u]].flow+=a[t],e[pre[u]^1].flow-=a[t];
    return 1;
}

bool check(int x)
{
    long long rest=K;
    for(int i=0;i<road.size();i++)
    {
        if(road[i].len>x) continue;
        rest-=1ll*road[i].flow*(x-road[i].len+1);
        if(rest<=0) return 1;
    }
    return 0;
}

int getans()
{
    int l=0,r=0x3f3f3f3f;
    while(l<=r)
    {
        int mid=(l+r)/2;
        if(check(mid)) r=mid-1;
        else l=mid+1;
    }
    return check(r)?r:r+1;
}

int main()
{
    while(~scanf("%d%d%d",&n,&m,&K))
    {
        memset(h,-1,sizeof(h));sum=-1;
        for(int i=1,u,v,w;i<=m;i++)
        {
            scanf("%d%d%d",&u,&v,&w);
            add_edge(u,v,w);
        }
        road.clear();
        s=0;t=n-1;while(spfa());
        if(K==0) puts("0");
        else if(road.empty()) puts("No solution");
        else printf("%d\n",getans());
    }
    return 0;
}