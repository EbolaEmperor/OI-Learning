#include<bits/stdc++.h>
using namespace std;

const int N=60;
struct Seg{int l,r;} seg[N];
int a[N],n,cnt[N],tot,num,sf[N];
vector<int> side[N][2],sg;

bool cross(Seg x,Seg y)
{
    if(x.l>y.l) swap(x,y);
    return x.r>y.l&&y.r>x.r;
}

namespace Graph1
{
    struct Edge{int to,next;} e[610];
    int h[N],sum=0,pos[N];
    void clear(){sum=0;memset(h,0,sizeof(h));}
    void add_edge(int u,int v)
    {
        e[++sum].to=v;
        e[sum].next=h[u];
        h[u]=sum;
    }
    void add(int u,int v)
    {
        add_edge(u,v);
        add_edge(v,u);
    }
    bool dfs(int u,int d)
    {
        if(~pos[u]) return pos[u]==d;
        side[num][d].push_back(u);pos[u]=d;
        for(int t=h[u];t;t=e[t].next)
            if(!dfs(e[t].to,d^1)) return 0;
        return 1;
    }
    bool check()
    {
        num=0;sg.clear();
        memset(pos,-1,sizeof(pos));
        for(int i=1;i<=tot;i++)
        {
            if(~pos[i]) continue;
            if(h[i])
            {
                side[++num][0].clear();
                side[num][1].clear();
                if(!dfs(i,0)) return 0;
            }
            else sg.push_back(i);
        }
        return 1;
    }
}

namespace Graph2
{
    struct Edge{int to,capa,next;} e[N*N];
    int h[N],sum=0,pos[N];
    void clear(){sum=-1;memset(h,-1,sizeof(h));}
    void add_edge(int u,int v,int w)
    {
        e[++sum].to=v;
        e[sum].capa=w;
        e[sum].next=h[u];
        h[u]=sum;
    }
    void add(int u,int v,int w)
    {
        add_edge(u,v,w);
        add_edge(v,u,w);
    }
    bool dfs(int u,int d)
    {
        if(~pos[u]) return pos[u]==d;
        pos[u]=d;
        for(int t=h[u];~t;t=e[t].next)
            if(!dfs(e[t].to,d^e[t].capa)) return 0;
        return 1;
    }
    bool check()
    {
        memset(pos,-1,sizeof(pos));
        for(int i=0;i<=n;i++)
        {
            if(~pos[i]) continue;
            if(!dfs(i,0)) return 0;
        }
        return 1;
    }
}

bool gao()
{
    tot=0;
    memset(cnt,0,sizeof(cnt));
    for(int i=1,j;i<=n;i++)
    {
        scanf("%d",a+i);
        sf[i]=sf[i-1]+(a[i]==-1);
        if(a[i]==-1) continue;
        if(++cnt[a[i]]>1)
        {
            for(j=i-1;j;j--)
                if(a[i]==a[j]) break;
            seg[++tot]={j,i};
        }
    }
    Graph1::clear();
    for(int i=1;i<=tot;i++)
        for(int j=i+1;j<=tot;j++)
            if(cross(seg[i],seg[j]))
                Graph1::add(i,j);
    if(!Graph1::check()) return 0;
    for(int s=0;s<(1<<num);s++)
    {
        Graph2::clear();
        for(int x : sg)
            if((seg[x].r-seg[x].l)&1)
                Graph2::add(seg[x].l-1,seg[x].r,0);
        for(int i=1;i<=num;i++)
        {
            for(int x : side[i][(s>>i-1)&1]) Graph2::add(seg[x].l-1,seg[x].r,0);
            for(int x : side[i][~(s>>i-1)&1]) Graph2::add(seg[x].l-1,seg[x].r,(sf[seg[x].r]-sf[seg[x].l-1])&1);
        }
        for(int i=1;i<=n;i++)
            if(~a[i]) Graph2::add(i-1,i,0);
        Graph2::add(0,n,0);
        if(Graph2::check()) return 1;
    }
    return 0;
}

int main()
{
    int T;
    for(scanf("%d",&T);T;T--)
    {
        scanf("%d",&n);
        if(gao()) puts("POSSIBLE");
        else puts("IMPOSSIBLE");
    }
    return 0;
}