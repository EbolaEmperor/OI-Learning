#include<bits/stdc++.h>
#include "werewolf.h"
using namespace std;

typedef pair<int,int> pii;
const int N=400010;
struct E{int u,v;} e[N];
struct Event{int ty,a,b,c;};
int n,m,q,tot,bit[N];
vector<Event> g[N];
vector<int> ans;

inline int min(int x,int y){return x<y?x:y;}
inline int max(int x,int y){return x>y?x:y;}
inline bool leq(int x,int y){return x<=y;}
inline bool geq(int x,int y){return x>=y;}

struct Kruskal
{
    int fa[N],val[N],ch[N][2],go[20][N];
    int in[N],out[N],dfc;
    int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
    void dfs(int u)
    {
        in[u]=++dfc;
        if(u>n) dfs(ch[u][0]);
        if(u>n) dfs(ch[u][1]);
        out[u]=dfc;
    }
    void build(int(*cmp)(int,int))
    {
        dfc=0;tot=n;
        for(int i=1;i<=n;i++) val[i]=i;
        for(int i=1;i<=n<<1;i++) fa[i]=i;
        for(int i=1;i<=m;i++)
        {
            int u=e[i].u,v=e[i].v;
            u=find(u);v=find(v);
            if(u==v) continue;
            val[++tot]=cmp(val[u],val[v]);
            fa[u]=fa[v]=go[0][u]=go[0][v]=tot;
            ch[tot][0]=u;ch[tot][1]=v;
        }
        dfs(tot);
        go[0][tot]=tot;
        for(int k=1;k<=18;k++)
            for(int i=1;i<=tot;i++)
                go[k][i]=go[k-1][go[k-1][i]];
    }
    pii jump(int u,int x,bool(*cmp)(int,int))
    {
        for(int k=18;k>=0;k--)
            if(cmp(val[go[k][u]],x)) u=go[k][u];
        return pii(in[u],out[u]);
    }
} t1,t2;

inline int lowbit(const int &x){return x&-x;}
void add(int p){for(p++;p<=n<<1;p+=lowbit(p)) bit[p]++;}
int sum(int p){int res=0;for(p++;p;p-=lowbit(p)) res+=bit[p];return res;}

vector<int> check_validity(int N,vector<int> X,vector<int> Y,vector<int> S,vector<int> T,vector<int> L,vector<int> R)
{
    n=N;m=X.size();q=S.size();
    for(int i=1;i<=m;i++)
    {
        e[i].u=X[i-1];e[i].v=Y[i-1];
        if(e[i].u>e[i].v) swap(e[i].u,e[i].v);
        e[i].u++;e[i].v++;
    }
    sort(e+1,e+1+m,[](E a,E b){return a.u>b.u;});
    t1.build(min);
    sort(e+1,e+1+m,[](E a,E b){return a.v<b.v;});
    t2.build(max);
    for(int i=1;i<=n;i++)
        g[t1.in[i]].push_back({1,t2.in[i],0,0});
    for(int i=0,s,t,l,r,x1,x2,y1,y2;i<q;i++)
    {
        s=S[i]+1;t=T[i]+1;
        l=L[i]+1;r=R[i]+1;
        tie(x1,x2)=t1.jump(s,l,geq);
        tie(y1,y2)=t2.jump(t,r,leq);
        g[x1-1].push_back({2,y1-1,i,1});
        g[x1-1].push_back({2,y2,i,-1});
        g[x2].push_back({2,y1-1,i,-1});
        g[x2].push_back({2,y2,i,1});
    }
    ans.resize(q);
    for(int i=0;i<=n<<1;i++)
        for(Event ev : g[i])
        {
            if(ev.ty==1) add(ev.a);
            else ans[ev.b]+=ev.c*sum(ev.a);
        }
    for(int i=0;i<q;i++)
        if(ans[i]>0) ans[i]=1;
    return ans;
}