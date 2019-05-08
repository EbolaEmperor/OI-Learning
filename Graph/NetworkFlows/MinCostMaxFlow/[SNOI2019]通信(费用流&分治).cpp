#include<bits/stdc++.h>
using namespace std;

typedef long long LL;
const int INF=0x3f3f3f3f;
const int N=100010,M=5000010;
struct Edge{int to,capa,flow,cost,next;} e[M];
int h[N],esum=-1,tot,s,t;
int dis[N],cur[N];
bool inq[N];
LL ans=0;
int n,w,a[N];

void add_edge(int u,int v,int w,int c)
{
    e[++esum]={v,w,0,c,h[u]};h[u]=esum;
    e[++esum]={u,0,0,-c,h[v]};h[v]=esum;
}

bool spfa()
{
    queue<int> q;
    memset(dis,0x3f,sizeof(int)*(tot+1));
    q.push(s);inq[s]=1;dis[s]=0;
    while(!q.empty())
    {
        int u=q.front();
        for(int i=h[u];~i;i=e[i].next)
        {
            int v=e[i].to;
            if(e[i].capa>e[i].flow&&dis[u]+e[i].cost<dis[v])
            {
                dis[v]=dis[u]+e[i].cost;
                if(!inq[v]) inq[v]=1,q.push(v);
            }
        }
        q.pop();inq[u]=0;
    }
    return dis[t]<INF;
}

int dfs(int u,int a)
{
    if(u==t||a==0) return a;
    int flow=0;inq[u]=1;
    for(int &i=cur[u];~i;i=e[i].next)
    {
        int v=e[i].to;
        if(inq[v]) continue;
        if(dis[u]+e[i].cost==dis[v])
        {
            int f=dfs(v,min(a,e[i].capa-e[i].flow));
            if(!f) continue;
            e[i].flow+=f;
            e[i^1].flow-=f;
            a-=f;flow+=f;
            ans+=(LL)f*e[i].cost;
            if(a==0) break;
        }
    }
    inq[u]=0;
    return flow;
}

void mcmf(){while(spfa()) memcpy(cur,h,sizeof(int)*(tot+1)),dfs(s,INF);}

void gao(int l,int r)
{
    if(l==r) return;
    int mid=(l+r)/2;
    gao(l,mid);gao(mid+1,r);
    static int b[N];int m=0;
    for(int i=l;i<=r;i++) b[++m]=a[i];
    sort(b+1,b+m+1);
    m=unique(b+1,b+1+m)-(b+1);
    for(int i=1;i<m;i++)
    {
        add_edge(tot+i,tot+i+1,INF,b[i+1]-b[i]);
        add_edge(tot+i+1,tot+i,INF,b[i+1]-b[i]);
    }
    for(int i=l;i<=r;i++)
    {
        int pos=lower_bound(b+1,b+1+m,a[i])-b;
        if(i<=mid) add_edge(i,tot+pos,INF,0);
        else add_edge(tot+pos,i+n,INF,0);
    }
    tot+=m;
}

int main()
{
    memset(h,-1,sizeof(h));
    scanf("%d%d",&n,&w);
    for(int i=1;i<=n;i++)
        scanf("%d",a+i);
    t=tot=2*n+1;s=0;
    for(int i=1;i<=n;i++)
    {
        add_edge(s,i,1,0);
        add_edge(i,t,1,w);
        add_edge(n+i,t,1,0);
    }
    gao(1,n);mcmf();
    cout<<ans<<endl;
    return 0;
}