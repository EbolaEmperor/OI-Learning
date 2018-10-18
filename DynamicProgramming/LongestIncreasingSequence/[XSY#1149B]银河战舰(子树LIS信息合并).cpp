#include<bits/stdc++.h>
using namespace std;

const int S=(1<<20)+5;
char buf[S],*H,*T;
inline char Get()
{
    if(H==T) T=(H=buf)+fread(buf,1,S,stdin);
    if(H==T) return -1;return *H++;
}
inline int read()
{
    int x=0;char c=Get();
    while(!isdigit(c)) c=Get();
    while(isdigit(c)) x=x*10+c-'0',c=Get();
    return x;
}

const int N=200010;
struct Edge{int to,next;} e[N<<1];
int h[N],sum=0,n,val[N],ans=0;
vector<int> f[N],g[N];

void add_edge(int u,int v)
{
    e[++sum].to=v;
    e[sum].next=h[u];
    h[u]=sum;
}

inline bool cmp(const int &x,const int &y){return x>y;}

void cross(int u,int v)
{
    int pos;
    if(f[u].size()<g[v].size()) for(int i=0;i<f[u].size();i++)
    {
        pos=lower_bound(g[v].begin(),g[v].end(),f[u][i],cmp)-g[v].begin();
        ans=max(ans,pos+i+1);
    }
    else for(int i=0;i<g[v].size();i++)
    {
        pos=lower_bound(f[u].begin(),f[u].end(),g[v][i])-f[u].begin();
        ans=max(ans,pos+i+1);
    }
}

void gao(int u,int v)  //update ans with vertex u
{
    int l1=lower_bound(f[u].begin(),f[u].end(),val[u])-f[u].begin();
    int l2=lower_bound(g[v].begin(),g[v].end(),val[u],cmp)-g[v].begin();
    ans=max(ans,l1+l2+1);
    l1=lower_bound(f[v].begin(),f[v].end(),val[u])-f[v].begin();
    l2=lower_bound(g[u].begin(),g[u].end(),val[u],cmp)-g[u].begin();
    ans=max(ans,l1+l2+1);
    cross(u,v);cross(v,u);  //update ans cross vertex u
}

void merge(int u,int v)  //merge f[v],g[v] to f[u],g[u]
{
    if(f[u].size()>=f[v].size())
        for(int i=0;i<f[v].size();i++)
            f[u][i]=min(f[u][i],f[v][i]);
    else
    {
        for(int i=0;i<f[u].size();i++)
            f[v][i]=min(f[v][i],f[u][i]);
        swap(f[u],f[v]);
    }
    if(g[u].size()>=g[v].size())
        for(int i=0;i<g[v].size();i++)
            g[u][i]=max(g[u][i],g[v][i]);
    else
    {
        for(int i=0;i<g[u].size();i++)
            g[v][i]=max(g[v][i],g[u][i]);
        swap(g[u],g[v]);
    }
}

void join(int u)  //join val[u] to f[u],g[u]
{
    auto pos=upper_bound(f[u].begin(),f[u].end(),val[u]);
    if(f[u].empty()||pos==f[u].begin()||val[u]>*(pos-1))
    {
        if(pos==f[u].end())
            f[u].push_back(INT_MAX),
            pos=f[u].end()-1;
        *pos=val[u];
    }
    pos=upper_bound(g[u].begin(),g[u].end(),val[u],cmp);
    if(g[u].empty()||pos==g[u].begin()||val[u]<*(pos-1))
    {
        if(pos==g[u].end())
            g[u].push_back(-INT_MAX),
            pos=g[u].end()-1;
        *pos=val[u];
    }
}

void dfs(int u,int fa)
{
    for(int t=h[u];t;t=e[t].next)
    {
        int v=e[t].to;
        if(v==fa) continue;
        dfs(v,u);
        gao(u,v);
        merge(u,v);
    }
    join(u);
}

int main()
{
    n=read();
    for(int i=1;i<=n;i++) val[i]=read();
    for(int i=1;i<n;i++)
    {
        int u=read(),v=read();
        add_edge(u,v);
        add_edge(v,u);
    }
    dfs(1,0);
    cout<<ans<<endl;
    return 0;
}