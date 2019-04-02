#include<bits/stdc++.h>
using namespace std;

const int INF=0x3f3f3f3f;
const int N=800010;
vector<int> g[N];
int idx[N],n,val[N];
int dfn[N],low[N],dfc=0;
int scc[N],sccv[N],deg[N],sccn=0;
stack<int> st;

void build(int o,int l,int r)
{
    if(l==r){idx[l]=o;return;}
    int mid=(l+r)/2;
    build(o<<1,l,mid);
    build(o<<1|1,mid+1,r);
    g[o<<1].emplace_back(o);
    g[o<<1|1].emplace_back(o);
}

void link(int o,int l,int r,int nl,int nr,int x)
{
    if(l>=nl&&r<=nr){g[o].emplace_back(x);return;}
    int mid=(l+r)/2;
    if(nl<=mid) link(o<<1,l,mid,nl,nr,x);
    if(nr>mid) link(o<<1|1,mid+1,r,nl,nr,x);
}

void Tarjan(int u)
{
    st.push(u);
    low[u]=dfn[u]=++dfc;
    for(int v : g[u])
        if(!dfn[v]) Tarjan(v),low[u]=min(low[u],low[v]);
        else if(!scc[v]) low[u]=min(low[u],dfn[v]);
    if(dfn[u]==low[u])
    {
        int o;
        sccv[++sccn]=INF;
        do{
            o=st.top();
            scc[o]=sccn;
            sccv[sccn]=min(sccv[sccn],val[o]);
            st.pop();
        }while(o!=u);
    }
}

int main()
{
    scanf("%d",&n);
    build(1,1,n);
    memset(val,0x3f,sizeof(val));
    int ans=0;
    for(int i=1,l,r;i<=n;i++)
    {
        scanf("%d%d%d",&l,&r,val+idx[i]);
        link(1,1,n,l,r,idx[i]);
        ans+=val[idx[i]];
    }
    for(int i=1;i<=n;i++)
        if(!dfn[i]) Tarjan(i);
    for(int u=1;u<=idx[n];u++)
        for(int v : g[u])
            if(scc[u]!=scc[v]) deg[scc[v]]++;
    for(int i=1;i<=sccn;i++)
        if(!deg[i]&&sccv[i]<=10000) ans-=sccv[i];
    printf("%d\n",ans);
    return 0;
}
