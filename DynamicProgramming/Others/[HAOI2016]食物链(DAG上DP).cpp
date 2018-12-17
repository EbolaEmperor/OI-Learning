#include<bits/stdc++.h>
using namespace std;

const int N=100010;
vector<int> G[N];
int n,m,ideg[N],odeg[N];
int deg[N],f[N];

void TopoSort()
{
    queue<int> q;
    for(int i=1;i<=n;i++)
        if(!deg[i]) q.push(i),f[i]=1;
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(int v : G[u])
        {
            f[v]+=f[u];
            if(!--deg[v]) q.push(v);
        }
    }
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1,u,v;i<=m;i++)
    {
        scanf("%d%d",&u,&v);
        G[u].push_back(v);
        G[v].push_back(u);
        ideg[v]++;deg[v]++;odeg[u]++;
    }
    TopoSort();
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        if(!ideg[i]&&!odeg[i]) continue;
        if(!odeg[i]) ans+=f[i];
    }
    printf("%d\n",ans);
    return 0;
}