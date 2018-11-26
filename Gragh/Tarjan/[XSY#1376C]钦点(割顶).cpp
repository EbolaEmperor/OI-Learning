#include<bits/stdc++.h>
using namespace std;

const int N=100010;
const int V=10000010;
int head[V],tail[V],tp[V];
int val[V],vcnt=0;
vector<int> G[V];
int a[N],n,T,ans;
int ffa[N],fsz[N];
int dfn[N],low[N],dfc;
int siz[N],all;

int find(int x){return ffa[x]==x?x:ffa[x]=find(ffa[x]);}

void add_edge(int u,int v)
{
    G[u].push_back(v);
    G[v].push_back(u);
    u=find(u);v=find(v);
    if(u!=v) ffa[u]=v,fsz[v]+=fsz[u];
}

void link(int u,int x)
{
    static int p[100],cnt[100];
    int tt=0,num;
    for(int v=2;v*v<=x&&x>1;v++)
    {
        if(x%v) continue;
        cnt[++tt]=0;p[tt]=v;
        while(x%v==0) x/=v,cnt[tt]++;
    }
    if(x>1) cnt[++tt]=1,p[tt]=x;
    for(int i=1;i<=tt;i++)
        for(int j=1;j<=i;j++)
        {
            if(i==j&&cnt[i]<2) continue;
            int v=p[i]*p[j];
            if(tp[v]!=T) tp[v]=T,tail[v]=0;
            if(!tail[v]) head[v]=u,val[++vcnt]=v;
            else add_edge(u,tail[v]);
            tail[v]=u;
        }
}

void tarjan(int u,int fa)
{
    siz[u]=1;
    dfn[u]=low[u]=++dfc;
    int mxsz=0,ssz=1;
    for(int v : G[u])
    {
        if(v==fa) continue;
        if(!dfn[v])
        {
            tarjan(v,u);
            siz[u]+=siz[v];
            low[u]=min(low[u],low[v]);
            if(low[v]>=dfn[u]) mxsz=max(mxsz,siz[v]),ssz+=siz[v];
        }
        else low[u]=min(low[u],dfn[v]);
    }
    mxsz=max(mxsz,all-ssz);
    ans=min(ans,mxsz);
}

int main()
{
    for(scanf("%d",&T);T;T--)
    {
        scanf("%d",&n);vcnt=0;
        for(int i=1;i<=n;i++) G[i].clear(),ffa[i]=i,fsz[i]=1;
        for(int i=1;i<=n;i++) scanf("%d",a+i);
        for(int i=1;i<=n;i++) link(i,a[i]);
        for(int i=1;i<=vcnt;i++)
        {
            int x=val[i];
            if(head[x]==tail[x]) continue;
            add_edge(head[x],tail[x]);
        }
        int mx=0,mxs=0,rt;
        for(int i=1;i<=n;i++)
        {
            if(ffa[i]!=i) continue;
            if(fsz[i]>mx) mxs=mx,all=mx=fsz[i],rt=i;
            else if(fsz[i]>mxs) mxs=fsz[i];
        }
        memset(dfn,0,sizeof(dfn));
        ans=INT_MAX;dfc=0;tarjan(rt,0);
        printf("%d\n",max(ans,mxs));
    }
    return 0;
}