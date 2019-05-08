#pragma GCC optimize(3)
#include<bits/stdc++.h>
using namespace std;

const int P=300010,N=50010;
struct Node
{
    int x,t,d;
    Node(int _x=0,int _t=0,int _d=0):x(_x),t(_t),d(_d){}
    bool operator < (const Node &b) const
    {
        if(x!=b.x) return x<b.x;
        if(t!=b.t) return t<b.t;
        return d<b.d;
    }
};
struct Qry{int c,t,x,y;} qry[N<<1];
map<Node,int> idx;
map<int,int> e[P];
vector<int> g[P],gg[P],tme[N];
int dfn[P],low[P],dfc=0;
int scc[P],sccn=0;
int T,n,m,tot=0,ans[N];
stack<int> stk;
int cnt[65536];

struct Bitset
{
    unsigned v[521];
    void init(){for(int i=1;i<65536;i++) cnt[i]=cnt[i-(i&-i)]+1;}
    void reset(){memset(v,0,sizeof(v));}
    void set(const int &x){v[x/32]|=1<<(x&31);}
    bool operator [] (const int &x){return (v[x/32]>>(x&31))&1;}
    Bitset operator |= (const Bitset &b){for(int i=0;i<521;i++) v[i]|=b.v[i];return *this;}
    int count()
    {
        int ans=0;
        for(int i=0;i<521;i++)
            ans+=cnt[v[i]&65535]+cnt[v[i]>>16];
        return ans;
    }
} bag[P],bad;

void Tarjan(int u)
{
    dfn[u]=low[u]=++dfc;
    stk.push(u);
    for(int v : g[u])
        if(!dfn[v]) Tarjan(v),low[u]=min(low[u],low[v]);
        else if(!scc[v]) low[u]=min(low[u],dfn[v]);
    if(low[u]==dfn[u])
    {
        int o;sccn++;
        do{
            o=stk.top();
            scc[o]=sccn;
            stk.pop();
        }while(o!=u);
    }
}

void build()
{
    scanf("%d%d%d",&T,&n,&m);
    for(int i=1;i<=n;i++) tme[i].push_back(T+1);
    for(int i=1;i<=m;i++)
    {
        scanf("%d%d%d%d",&qry[i].c,&qry[i].t,&qry[i].x,&qry[i].y);
        tme[qry[i].x].push_back(qry[i].t);
    }
    for(int i=1;i<=n;i++)
    {
        sort(tme[i].begin(),tme[i].end());
        int cnt=unique(tme[i].begin(),tme[i].end())-tme[i].begin();
        tme[i].resize(cnt);
        for(int t : tme[i]) idx[Node(i,t,1)]=++tot,idx[Node(i,t,0)]=++tot;
        for(int j=1;j<cnt;j++)
        {
            g[idx[Node(i,tme[i][j-1],0)]].push_back(idx[Node(i,tme[i][j],0)]);
            g[idx[Node(i,tme[i][j],1)]].push_back(idx[Node(i,tme[i][j-1],1)]);
        }
    }
    for(int i=1;i<=m;i++)
    {
        int c=qry[i].c,t=qry[i].t,x=qry[i].x,y=qry[i].y;
        if(c==0)
        {
            int t2=*lower_bound(tme[y].begin(),tme[y].end(),t+1);
            Node a1(x,t,1),a0(x,t,0);
            Node b1(y,t2,1),b0(y,t2,0);
            g[idx[a0]].push_back(idx[b0]);
            g[idx[b1]].push_back(idx[a1]);
        }
        else
        {
            int t2=*lower_bound(tme[y].begin(),tme[y].end(),t);
            Node a1(x,t,1),a0(x,t,0);
            Node b1(y,t2,1),b0(y,t2,0);
            g[idx[a1]].push_back(idx[b0]);
            g[idx[b1]].push_back(idx[a0]);
        }
    }
    for(int i=1;i<=tot;i++)
        if(!dfn[i]) Tarjan(i);
    for(int u=1;u<=tot;u++)for(int v : g[u])
        if(scc[u]!=scc[v]&&!e[scc[u]].count(scc[v]))
            gg[scc[u]].push_back(scc[v]),e[scc[u]][scc[v]]=1;
}

void gao(int l,int r)
{
    for(int i=1;i<=sccn;i++) bag[i].reset();
    bad.reset();
    for(int i=l;i<=r;i++)
        bag[scc[idx[Node(i,T+1,0)]]].set(i-l);
    for(int u=1;u<=sccn;u++)
        for(int v : gg[u]) bag[u]|=bag[v];
    for(int i=l;i<=r;i++)
        if(bag[scc[idx[Node(i,T+1,1)]]][i-l]) bad.set(i-l),ans[i]=0;
    for(int i=1;i<=n;i++)
        if(ans[i]) ans[i]-=(bag[scc[idx[Node(i,T+1,1)]]]|=bad).count();
}

int main()
{
    bad.init();build();
    for(int i=1;i<=n;i++) ans[i]=n-1;
    for(int i=1;i<=n;i+=16672) gao(i,min(n,i+16671));
    for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
    return cout<<endl,0;
}