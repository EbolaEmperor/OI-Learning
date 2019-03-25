#include<bits/stdc++.h>
using namespace std;

const int N=100010;
struct Edge{int u,v,del,next;} e[N<<1];
int h[N],sum=-1,pre[N];
bool vis[N];
int n,m,deg[N];

void add_edge(int u,int v)
{
    e[++sum]={u,v,0,h[u]};h[u]=sum;
    e[++sum]={v,u,0,h[v]};h[v]=sum;
}

void dfs(int u)
{
    vis[u]=1;
    for(int t=h[u];~t;t=e[t].next)
    {
        if(e[t].del) continue;
        int v=e[t].v;
        if(vis[v]) continue;
        pre[v]=t;dfs(v);
    }
}

int main()
{
    scanf("%d%d",&n,&m);
    memset(h,-1,sizeof(h));
    for(int i=1,u,v;i<=m;i++)
    {
        scanf("%d%d",&u,&v);
        add_edge(u,v);
        deg[u]++;deg[v]++;
    }
    int four=0,six=0;
    for(int i=1;i<=n;i++)
    {
        if(deg[i]&1) return puts("No"),0;
        if(deg[i]==4) four++;
        if(deg[i]==6) six++;
    }
    if(six>=1) return puts("Yes"),0;
    if(four>=3) return puts("Yes"),0;
    if(four<2) return puts("No"),0;
    int A=0,B=0,cnt=0;
    for(int i=1;i<=n;i++)
        if(deg[i]==4) (!A)?(A=i):(B=i);
    while(1)
    {
        memset(vis,0,sizeof(vis));
        dfs(A);
        if(!vis[B]) break;
        for(int u=B;u!=A;u=e[pre[u]].u)
            e[pre[u]].del=e[pre[u]^1].del=1;
        cnt++;
    }
    puts(cnt==2?"Yes":"No");
    return 0;
}