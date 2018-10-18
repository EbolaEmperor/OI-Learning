#include<bits/stdc++.h>
using namespace std;

const int N=1010,M=20010;
struct Edge{int to,capa,flow,next;} e[M];
int h[N],sum,n,m,s,t;
int froms[M],tos[M];
int capa[M],capb[M];
int degin[N],degout[M];
int cur[N],d[N];
bool vis[N];
int fa[N];

int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}

void add_edge(int u,int v,int w)
{
    e[++sum]={v,w,0,h[u]};h[u]=sum;
    e[++sum]={u,0,0,h[v]};h[v]=sum;
}

bool BFS()
{
    queue<int> q;q.push(s);
    memset(vis,0,sizeof(vis));
    vis[s]=1;d[s]=0;
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(int t=h[u];~t;t=e[t].next)
        {
            int v=e[t].to;
            if(!vis[v]&&e[t].capa>e[t].flow)
            {
                d[v]=d[u]+1;
                vis[v]=1;
                q.push(v);
            }
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
        e[t].flow+=flow;
        e[t^1].flow-=flow;
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

bool check(int lim)
{
    sum=-1;memset(h,-1,sizeof(h));
    memset(degin,0,sizeof(degin));
    memset(degout,0,sizeof(degout));
    for(int i=1;i<=n;i++) fa[i]=i;
    for(int i=1;i<=m;i++)
    {
        if(capa[i]<=lim)
        {
            degout[froms[i]]++;
            degin[tos[i]]++;
            if(find(froms[i])!=find(tos[i]))
                fa[find(froms[i])]=find(tos[i]);
        }
        if(capb[i]<=lim) add_edge(tos[i],froms[i],1);
    }
    int fullflow=0,cnt=0;
    for(int i=1;i<=n;i++) cnt+=(fa[i]==i);
    if(cnt>1) return 0;
    for(int i=1;i<=n;i++)
    {
        int delta=abs(degin[i]-degout[i]);
        if(delta&1) return 0;
        if(degin[i]<degout[i]) add_edge(i,t,delta/2);
        if(degin[i]>degout[i]) add_edge(s,i,delta/2);
    }
    for(int i=h[s];~i;i=e[i].next) fullflow+=e[i].capa;
    return Dinic()==fullflow;
}

int main()
{
    scanf("%d%d",&n,&m);
    int u,v,a,b;s=0;t=n+1;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d%d",&u,&v,&a,&b);
        froms[i]=u;tos[i]=v;
        capa[i]=a;capb[i]=b;
        if(capa[i]>capb[i])
        {
            swap(capa[i],capb[i]);
            swap(froms[i],tos[i]);
        }
    }
    int l=0,r=1000,mid;
    while(l<=r)
    {
        mid=(l+r)/2;
        if(check(mid)) r=mid-1;
        else l=mid+1;
    }
    if(l>1000) puts("NIE");
    else printf("%d\n",check(r)?r:r+1);
    return 0;
}