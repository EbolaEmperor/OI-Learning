#include<bits/stdc++.h>
using namespace std;

const int N=1000010;
struct Edge{int from,to,next;} e[N];
vector<int> G[N],rG[N],ans;
int h[N],n,m,esum=0;
int dfn[N],low[N],dfc=0;
int scc[N],sccn=0;
stack<int> stk;
bool cant[N];
int deg[N],rdeg[N];
int sum[N],topos[N];

void add_edge(int u,int v)
{
    e[++esum].to=v;
    e[esum].from=u;
    e[esum].next=h[u];
    h[u]=esum;
}

void tarjan(int u)
{
    stk.push(u);
    dfn[u]=low[u]=++dfc;
    for(int t=h[u];t;t=e[t].next)
    {
        int v=e[t].to;
        if(!dfn[v]) tarjan(v),low[u]=min(low[u],low[v]);
        else if(!scc[v]) low[u]=min(low[u],dfn[v]);
    }
    if(dfn[u]==low[u])
    {
        int o;sccn++;
        do{
            o=stk.top();
            scc[o]=sccn;
            stk.pop();
        }while(o!=u);
    }
}

void TopoSort(vector<int> *G,int *deg)
{
    static int que[N];
    int head=1,tail=0;
    memset(sum,0,sizeof(sum));
    for(int i=1;i<=sccn;i++)
    {
        if(deg[i]) continue;
        que[++tail]=i;
        sum[0]++;sum[tail]--;
    }
    while(head<=tail)
    {
        int u=que[head];
        topos[u]+=head++;
        for(int v : G[u])
        {
            if(--deg[v]) continue;
            que[++tail]=v;
            sum[head]++;sum[tail]--;
        }
    }
    for(int i=1;i<=sccn;i++)
    {
        sum[i]+=sum[i-1];
        if(sum[i]) cant[que[i]]=1;
    }
}

int main()
{
    scanf("%d%d",&n,&m);
    for(int i=1,u,v;i<=m;i++)
    {
        scanf("%d%d",&u,&v);
        add_edge(u,v);
    }
    for(int i=1;i<=n;i++)
        if(!dfn[i]) tarjan(i);
    for(int i=1;i<=esum;i++)
    {
        int u=e[i].from,v=e[i].to;
        u=scc[u];v=scc[v];
        if(u==v) continue;
        G[u].push_back(v);
        rG[v].push_back(u);
        deg[v]++;rdeg[u]++;
    }
    TopoSort(G,deg);
    TopoSort(rG,rdeg);
    for(int i=1;i<=sccn;i++)
        if(topos[i]!=sccn+1) cant[i]=1;
    for(int i=1;i<=n;i++)
        if(!cant[scc[i]]) ans.push_back(i);
    printf("%d\n",ans.size());
    for(int x : ans) printf("%d ",x);
    return 0;
}