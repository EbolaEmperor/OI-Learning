#include<bits/stdc++.h>
#define INF 0x7fffffff
using namespace std;

const int N=1010,M=20010;
struct Type
{
    int v[5];
    Type(){memset(v,0,sizeof(v));}
    Type(int x){for(int i=0;i<5;i++) v[i]=x;}
    int& operator [] (const int &x){return v[x];}
    bool operator < (const Type &a) const
    {
        for(int i=0;i<5;i++)
            if(v[i]!=a.v[i]) return v[i]<a.v[i];
        return 0;
    }
    bool operator == (const Type &a) const
    {
        for(int i=0;i<5;i++)
            if(v[i]!=a.v[i]) return 0;
        return 1;
    }
    Type&  operator += (const Type &a)
    {
        for(int i=0;i<5;i++)
            v[i]+=a.v[i];
        return *this;
    }
    Type&  operator -= (const Type &a)
    {
        for(int i=0;i<5;i++)
            v[i]-=a.v[i];
        return *this;
    }
    Type operator - (){Type tmp;for(int i=0;i<5;i++) tmp.v[i]=-v[i];return tmp;}
    Type operator + (const Type &a){Type tmp=*this;tmp+=a;return tmp;}
    Type operator - (const Type &a){Type tmp=*this;tmp-=a;return tmp;}
} zero,inf=INF,val[N];

struct Edge{int to,next;Type capa,flow;} e[M];
int h[N],sum=-1,n,m,k,s,t;
bool vis[N];
int d[N],cur[N];

void add_edge(int u,int v,Type w)
{
    e[++sum]={v,h[u],w,zero};h[u]=sum;
    e[++sum]={u,h[v],zero,zero};h[v]=sum;
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
            if(!vis[v]&&e[t].flow<e[t].capa)
            {
                d[v]=d[u]+1;
                vis[v]=1;
                q.push(v);
            }
        }
    }
    return vis[t];
}

Type DFS(int u,Type a)
{
    if(u==t||a==zero) return a;
    Type res=zero,flow;
    for(int &t=cur[u];~t;t=e[t].next)
    {
        int v=e[t].to;
        if(d[v]!=d[u]+1) continue;
        flow=DFS(v,min(a,e[t].capa-e[t].flow));
        if(flow==zero) continue;
        e[t].flow+=flow;
        e[t^1].flow-=flow;
        res+=flow;a-=flow;
        if(a==zero) break;
    }
    return res;
}

void dfs(int u)
{
    vis[u]=1;
    for(int t=h[u];~t;t=e[t].next)
        if(!vis[e[t].to]&&e[t].flow<e[t].capa)
            dfs(e[t].to);
}

int main()
{
    static char ss[10];
    memset(h,-1,sizeof(h));
    scanf("%d%d%d",&n,&m,&k);
    s=0;t=n+1;
    for(int i=1;i<=n;i++)
    {
        scanf("%s",ss);
        for(int j=0;j<k;j++)
            if(ss[j]=='+') val[i][j]=1;
            else if(ss[j]=='-') val[i][j]=-1;
            else val[i][j]=0;
        if(zero<val[i]) add_edge(s,i,val[i]);
        else if(val[i]<zero) add_edge(i,t,-val[i]);
    }
    int u,v;
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d",&u,&v);
        add_edge(u,v,inf);
    }
    while(BFS()) memcpy(cur,h,sizeof(h)),DFS(s,inf);
    memset(vis,0,sizeof(vis));dfs(s);
    Type ans=1000;
    for(int i=1;i<=n;i++)
        if(vis[i]) ans+=val[i];
    for(int i=0;i<k;i++)
        printf("%d ",ans[i]);
    return 0;
}