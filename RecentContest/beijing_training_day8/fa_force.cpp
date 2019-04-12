#include<bits/stdc++.h>
using namespace std;

const int N=120010;
vector<int> g[N];
long long ans=0;
int dis[N],n,m,sz[N];
bool inq[N];

void spfa(int s)
{
    queue<int> q;
    memset(dis,0x3f,sizeof(int)*(n+1));
    memset(inq,0,sizeof(bool)*(n+1));
    q.push(s);dis[s]=0;inq[s]=1;
    while(!q.empty())
    {
        int u=q.front();
        for(int v : g[u])
            if(dis[u]+1<dis[v])
            {
                dis[v]=dis[u]+1;
                if(!inq[v]) q.push(v),inq[v]=1;
            }
        inq[u]=0;q.pop();
    }
}

void dfs(int u,int fa)
{
    sz[u]=1;
    for(int v : g[u])
        if(v!=fa)
        {
            dfs(v,u);
            sz[u]+=sz[v];
            ans+=1ll*sz[v]*(n-sz[v]);
        }
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1,u,v;i<=m;i++)
    {
        scanf("%d%d",&u,&v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    if(m==n-1) dfs(1,0);
    else
    {
        for(int i=1;i<=n;i++)
        {
            spfa(i);
            for(int j=1;j<i;j++)
                ans+=dis[j];
        }
    }
    printf("%lld\n",ans);
    return 0;
}
